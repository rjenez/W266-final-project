#
# read MOSS output and generate unique examples for comparison
# heavily modifified from mossum.py
#


import re
import sys
import os
import datetime
import pydot
import argparse
import requests
import shutil
import numpy as np
import pandas as pd
import json
from itertools import combinations,permutations
from itertools import chain
import random

from bs4 import BeautifulSoup
from faker import Faker
from collections import defaultdict, Counter
from itertools import chain

from sklearn.model_selection import train_test_split

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('urls', metavar='URL', nargs='*',
                    help='URLs to Moss result pages.')
parser.add_argument('--min-percent', '-p', dest='min_percent', metavar='P', type=int, default=90,
                    help='All matches where less than P%% of both files are matched are ignored. (Default: %(default)s)')
parser.add_argument('--min-lines', '-l', dest='min_lines', metavar='L', type=int, default=1,
                    help='All matches where fewer than L lines are matched are ignored. (Default: %(default)s)')
parser.add_argument('--format', '-f', default='png',
                    help='Format of output files. See Graphviz documentation.')
parser.add_argument('--transformer', '-t', default='.*',
                    help='A regular expression that is used to transform the name of them matched files.')
parser.add_argument('--anonymize', '-a', default=False, action='store_true',
                    help='Substitute names of matched files for random names')
parser.add_argument('--merge', '-m', default=False, action='store_true',
                    help='Merge all reports into one image')
parser.add_argument('--report', '-r', default=False, action='store_true',
                    help='Generates a report showing how many submissions each pair has in common.')
parser.add_argument('--hide-labels', default=False, action='store_true',
                    help='Hide edge labels, which otherwise show the percentage and lines of code matches have in common')
parser.add_argument('--show-links', default=False, action='store_true',
                    help='DEPRECATED: Labels with links are shown by default, use --hide-labels to hide them')
parser.add_argument('--output', '-o', default=None,
                    help='Name of output file.')
parser.add_argument('--show-loops', default=False, action='store_true',
                    help='Include loops in the output graph')
parser.add_argument('--filter', metavar='N', nargs='+', default=None,
                    help='Include only matches between these names.')
parser.add_argument('--filteri', metavar='N', nargs='+', default=None,
                    help='Include only matches involving these names.')
parser.add_argument('--filterx', metavar='N', nargs='+', default=None,
                    help='Exclude matches between these names.')
parser.add_argument('--filterxi', metavar='N', nargs='+', default=None,
                    help='Exclude matches involving any of these names.')
parser.add_argument('--min-matches', metavar='N', default=1, type=int,
                    help='Show only files with N or more matces between each other. This is only applicable to merged results. (Default: %(default)s).')
parser.add_argument('--title', dest='title', type=str, default='',
                    help='Title to be inserted in the final image')
parser.add_argument('--include-source', default=True, action='store_true',
                    help='Include source in training and test ')
parser.add_argument('--ground-truth', dest='ground_truth', type=str, default='',
                    help='ground truth files for plagiarized content')
parser.add_argument('--baseurl', dest='baseurl', type=str, default='',
                    help='baseurl for getting the results')

from requests_testadapter import Resp

# set up to read local files
#
class LocalFileAdapter(requests.adapters.HTTPAdapter):
    def build_response_from_file(self, request):
        file_path = request.url[7:]
        with open(file_path, 'rb') as file:
            buff = bytearray(os.path.getsize(file_path))
            file.readinto(buff)
            resp = Resp(buff)
            r = self.build_response(request, resp)

            return r

    def send(self, request, stream=False, timeout=None,
             verify=True, cert=None, proxies=None):

        return self.build_response_from_file(request)

# read moss data from local files
#
r = requests.session()
r.mount('file://', LocalFileAdapter())


# get results
class Results:
    def __init__(self, name, matches):
        self.name = name
        self.matches = matches
        
    def __str__(self):
        return f'name={self.name} and matches ={self.matches}'

    def __repr__(self):
        return f'name={self.name} and matches ={self.matches}'


class Match:
    def __init__(self, first, second, lines, url):
        self.first = first
        self.second = second
        self.lines = lines
        self.url = url

    @property
    def percent(self):
        return max(self.first.percent, self.second.percent)

    def __str__(self):
        return f'first={self.first.name} and second ={self.second.name}\n lines={self.lines} percent={self.percent}'

    def __repr__(self):
        return f'first={self.first.name} and second ={self.second.name}\n lines={self.lines} percent={self.percent}'


class File:
    def __init__(self, name, percent):
        self.name = name
        self.percent = percent


class Filter:
    def __init__(self):
        filters = ['filter', 'filteri', 'filterx', 'filterxi']
        for f in filters:
            setattr(self, f, None)

        for f in filters:
            if getattr(args, f) != None:
                setattr(self, f, set(getattr(args, f)))

    def include(self, match):
        first = match.first.name
        second = match.second.name
        if (self.filter is not None and (first not in self.filter or second not
                                         in self.filter)):
            return False
        if (self.filteri is not None and (first not in self.filteri and second
                                          not in self.filteri)):
            return False
        if (self.filterx is not None and (first in self.filterx and second in
                                          self.filterx)):
            return False
        if (self.filterxi is not None and (first in self.filterxi or second in
                                           self.filterxi)):
            return False
        return match.lines > args.min_lines and (match.first.percent > args.min_percent or
                                                 match.second.percent > args.min_percent)

    
def date_str():
    return datetime.datetime.today().strftime('%d-%m-%Y_%H%M%S')

def parse_col(col):
    name, per = col.split()
    m = re.match(args.transformer, name)
    if m:
        if m.groups():
            name = '_'.join(m.groups())
        else:
            name = m.group()
    per = int(re.search(r'\d+', per).group())
    return File(name, per)


def random_names(length):
    fake = Faker()

    names = set()
    while len(names) < length:
        names.add(fake.first_name())

    return names

class File:
    def __init__(self, name, percent):
        self.name = name
        self.percent = percent

def get_results(moss_url):
    resp = r.get(moss_url)
    soup = BeautifulSoup(resp.content.decode('utf-8'), 'html5lib')

    if soup is None or soup.table is None:
        print(moss_url, ': is none')
        return

    ps = soup('p')
    name = None
    if len(ps) >= 2:
        name = ps[2].text.strip()
    if not name:
        name = 'moss_%s' % date_str()

    matches = []

    for row in soup.table('tr')[1:]:
        first, second, lines = map(lambda x: x.text, row('td'))
        first = parse_col(first)
        second = parse_col(second)
        lines = int(lines)
        url = row.a['href']
        matches.append(Match(first, second, lines, url))

    fil = Filter()
    matches = list(filter(fil.include, matches))

    return Results(name, matches)

def main():
    global args
    args = parser.parse_args()

    urls = [os.path.join(args.baseurl,url) for url in args.urls]
    #print(urls, args.urls)

    #return

    alldatadf = pd.DataFrame(columns = ['label','filename0','filename1','source0','source1','percent','percent0','percent1','lines'])

    # get the data from the plagiarism file
    #
    groundtruthdatadf = pd.DataFrame(columns = ['label','student0','student1','filename0','filename1'])
    
    with open(args.ground_truth, 'r') as f:
        for line in f:
            # print(line.rstrip().split(','))
            if line[0] == '-':
                currentlocation = line[2:-1]#.replace('/','_')+'_'
                continue

            students = line.rstrip().split(',')
            for c in permutations(students,2): #combinations(students,2):
                comparison = {'label':'1'}
                comparison['student0']=c[0]
                comparison['student1']=c[1]
                comparison['filename0']=os.path.join(currentlocation,c[0])
                comparison['filename1']=os.path.join(currentlocation,c[1])
                groundtruthdatadf = groundtruthdatadf.append(comparison, ignore_index=True)

    groundtruthdatadf.to_csv('groundtruth.csv', encoding='utf-8', index=False)

    for u in urls:
        print(u)
        results = get_results(u)
        print(results.name)
        for m in results.matches:
            #f'first={self.first.name} and second ={self.second.name}\n lines={self.lines} percent={self.percent}'
            filedata = {}
            filedata['label'] = str(m.percent)
            filedata['lines'] = str(m.lines)
            filedata['percent'] = m.percent
            filedata['percent0'] = str(m.first.percent)
            filedata['percent1'] = str(m.second.percent)
            base = os.path.basename(m.first.name)
            filedata[f'filename0'] =  os. path. splitext(m.first.name[-(len(base)+12):])[0]
            base = os.path.basename(m.second.name)
            filedata[f'filename1'] =  os. path. splitext(m.second.name[-(len(base)+12):])[0]
            filedata['plagiarized'] =  '0' if groundtruthdatadf[(groundtruthdatadf['filename0'] == filedata[f'filename0']) & (groundtruthdatadf['filename1'] == filedata[f'filename1'])].empty else '1'
            
            for i,f in zip(range(2),[m.first.name,m.second.name]):
                with open(f,mode='r') as file:
                    # read all lines at once
                    source =  file.read()
                    filedata[f'source{i}'] = source

            alldatadf = alldatadf.append(filedata, ignore_index=True)
            #print(m)
            #break

    #with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
    #    print(alldatadf)

    alldatadf[['label','filename0','filename1','percent','percent0','percent1','lines','plagiarized']].sort_values(by=['percent'], ascending=False).to_csv('alldata.csv', encoding='utf-8', index=False)

    train, test = train_test_split(alldatadf, test_size=0.2)
    train.to_csv('train.csv', encoding='utf-8', index=False)
    test.to_csv('test.csv', encoding='utf-8', index=False)
    
if __name__ == '__main__':
    main()
