import os
import sys, getopt
import shutil
import numpy as np
import json
import time
from itertools import combinations
from collections import OrderedDict
import random
import mosspylocal as mosspy

# get files for comparison
#
# comparison files
#
def getcomparison(samplefile):
    with open(samplefile) as json_file:
        data = json.load(json_file, object_pairs_hook=OrderedDict)
        #print(json.dumps(data,sort_keys=True, indent=4))

    return data

# log_level=logging.DEBUG (20 to disable)
# on_read function run for every downloaded file

#
# do the comparisons
#
def docomparisons(samplefile,groundtruth, inputdir, outputdir, outputfile, n,matches, nfiles,verbose=0,userid=0):
    samples = getcomparison(samplefile)
    whitelist = ['.c','.cpp']
    allfiles={}

    print(f'userid={userid}',flush=True)
    groundtruthdetail={}
    currentlocation = ""
    currentstudents = {'nonsimilar': [], 'similar':[]}

    with open(groundtruth, 'r') as f:
        for line in f:
            #print(line.rstrip().split(','))
            if line[0] == '-':
                if currentlocation != "":
                    groundtruthdetail[currentlocation]=currentstudents
                    currentstudents = {'nonsimilar': [], 'similar':[]}
                currentlocation = line[2:-1]#.replace('/','_')+'_'
                continue
            students = line.rstrip().split(',')
            if len(students) > 1:
                currentstudents['similar'].append(students)
            else:
                currentstudents['nonsimilar'].append(students)
        #students = list(map(lambda x: currentlocation+x,students))
        #currentstudents.append(students)

    #print(json.dumps(groundtruthdetail,sort_keys=True, indent=4))
   # return
    for k,v in samples.items():
        if os.path.isdir(outputdir+k.replace("/","_")):
            # already exists so move on
            print(f'Already processed {k}')
            continue
        count = 0
        m = mosspy.Moss(userid, "cc")
        print(f'count = {count}')
        print(n,matches,nfiles)
        m.setNumberOfMatchingFiles(n)
        m.setIgnoreLimit(matches)
        #m.setExperimentalServer(1)
        rootdir = os.path.join(inputdir,k)
        for root, subdirs, files in os.walk(rootdir):
            print('--\nroot = ' + root + rootdir)
            #for filename in files:
            for filename,_ in zip(files,range(nfiles)):
                if os.path.splitext(filename)[1] in whitelist:
                    if  allfiles.get(k,False) == False:
                        allfiles[k] = {filename.split('.')[0] : os.path.join(root, filename)}
                        m.addFile(os.path.join(root, filename))
                        count += 1
                    else:
                        allfiles[k][filename.split('.')[0]] = os.path.join(root, filename)
                        m.addFile(os.path.join(root, filename))
                        count +=1
                #print('\t- file %s (full path: %s) (destination path %s)' % (filename, filepath,destinationfile))
                #shutil.copy(filepath,destinationfile)
        if count == 0:
            # no files found, so need to create the directory to keep track and move on..
            os.mkdir(outputdir+k.replace("/","_"))
            continue
        #print(json.dumps(allfiles,sort_keys=True, indent=4))
        print(f'sending...{count}' )

        try:
            url,resp = m.send(lambda file_path, display_name: print(display_name,  flush=True) if verbose > 0 else lambda file_path, display_name: file_path )
        except IOError as e:
            print(f'Failed getting {k} with error {e}  continuing tryng next section')
            del m
            m = None
            count = 0
            print('sleeping...')
            time.sleep(300)
            continue

        print(f'waiting... for data, {url}',url)
        try:
            
            m.saveWebPage(url, outputfile+k.replace("/","_")+".html")
        except Exception as e:
            print(f'Failed getting {url} {resp} with error {e}  continuing tryng next section')
            del m
            m = None
            count = 0
            print('sleeping...')
            time.sleep(300)
            continue            
        print('webpage saved...')
        mosspy.download_report(url, outputdir+k.replace("/","_"), connections=4, log_level=20)#, on_read=lambda url: print(url,  flush=True))
        print('files saved...')
        print('sleeping...')
        count =0
        del m
        m = None
        time.sleep(300)
        
    
    

def main(argv):
    
    try:
        opts, args = getopt.getopt(argv[1:],"hs:e:d:i:o:n:m:f:v:u:",["sample_file=","examples", "inputdir=","outputdir=","ofile=","samples=","repeats=","files=","verbose=","userid="])
    except getopt.GetoptError:
        print(f'{argv[0]} --s <sample_file> --e <examples> --i <inputdir> --d <outputdir> --o <outputfile> --n <numberofsamples> --m <numberofrepeats> --f <numberoffiles --v level --u userid')
        sys.exit()

    samplefile = ""
    inputdir = ""
    outputdir = ""
    groundtruh = ""
    n = 250
    m = 10
    nfiles = 1000
    verbose = 0
    userid = 845202178
    
    for opt, arg in opts:
        if opt == '-h':
            print(f'{argv[0]} --s <sample_file> --e <examples> --i <inputdir> --d <outputdir> --o <outputfile> --n <numberofsamples> --m <numberofrepeats> --f <numberoffiles --v level --u userid')
            sys.exit(2) 
        elif opt in ("-s", "--sample_file"):
            samplefile = arg
        elif opt in ("-e", "--examples"):
            groundtruth = arg
        elif opt in ("-i", "--inputdir"):
            inputdir = arg
        elif opt in ("-d", "--outputdir"):
            outputdir = arg
        elif opt in ("-o", "--ofile"):
            outputfile = arg
        elif opt in ("-n", "--samples"):
            n= int(arg)
        elif opt in ("-m", "--repeats"):
            m= int(arg)
        elif opt in ("-f", "--files"):
            nfiles= int(arg)
        elif opt in ("-v", "--verbose"):
            verbose= int(arg)
        elif opt in ("-u", "--userid"):
            userid = int(arg)

    docomparisons(samplefile,groundtruth,inputdir, outputdir,outputfile,n,m,nfiles,verbose=verbose,userid=userid)

if __name__ == '__main__':
    main(sys.argv)
