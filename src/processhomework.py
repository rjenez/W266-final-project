import os
import sys, getopt
import shutil
import numpy as np
import json
from itertools import combinations
import random

homeworkDir='../data/programming-homework-dataset-plagiarism-detection/src'
groundtruth='../data/programming-homework-dataset-plagiarism-detection/ground-truth-anon.txt'

class SimilarityManager:
    def __init__(self,rootdir,whitelist,groundtruth):
        allfiles={}
        # print('walk_dir (absolute) = ' + os.path.abspath(rootdir))
        absrootdir = os.path.abspath(rootdir)
        #absdestination = os.path.abspath(destinationdir)

        #try:
        #os.mkdir(absdestination)
        #except FileExistsError as error:
        # all good if it already exist
        #   pass
        # except BaseException as err:
        # print(f"Unexpected {err}, {type(err)}")
        # return

        for root, subdirs, files in os.walk(rootdir):
            # print('--\nroot = ' + root)
            for filename in files:
                if os.path.splitext(filename)[1] in whitelist:
                    if  allfiles.get(root[len(rootdir)+1:],False) == False:
                        allfiles[root[len(rootdir)+1:]] = {filename.split('.')[0] : os.path.join(root, filename)}
                    else:
                        allfiles[root[len(rootdir)+1:]][filename.split('.')[0]] = os.path.join(root, filename)
                                                      
                #print('\t- file %s (full path: %s) (destination path %s)' % (filename, filepath,destinationfile))
                #shutil.copy(filepath,destinationfile)


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
        self.allfiles = allfiles
        self.groundtruthdetail = groundtruthdetail

    def getsimilar(self,n):
        similar = []
        while n > 0:
            location = random.choice(list(self.groundtruthdetail.keys()))
            if self.allfiles.get(location,False) is False or self.groundtruthdetail.get(location,False) is False or \
               self.groundtruthdetail[location].get('similar',False) is False or len(self.groundtruthdetail[location]['similar']) <= 1:
                continue
            students = random.choice(self.groundtruthdetail[location]['similar'])
            if students is None or len(students) <= 1:
                continue
            c = random.choice(list(combinations(students,2)))
            if self.allfiles[location].get(c[0], False) is False or self.allfiles[location].get(c[1], False) is False:
                continue
            similar.append({c[0]:self.allfiles[location][c[0]],c[1]:self.allfiles[location][c[1]]})
            n -= 1
        return similar

    def getnonsimilar(self,n):
        nonsimilar = []
        while n > 0:
            location = random.choice(list(self.groundtruthdetail.keys()))
            if self.allfiles.get(location,False) is False or self.groundtruthdetail.get(location,False) is False or \
               self.groundtruthdetail[location].get('nonsimilar',False) is False or len(self.groundtruthdetail[location]['nonsimilar']) <= 1:
                continue
            c = random.choice(list(combinations(self.groundtruthdetail[location]['nonsimilar'],2)))
            if c is None or len(c) <= 1:
                continue

            if self.allfiles[location].get(c[0][0], False) is False or self.allfiles[location].get(c[1][0], False) is False:
                continue

            nonsimilar.append({c[0][0]:self.allfiles[location][c[0][0]],c[1][0]:self.allfiles[location][c[1][0]]})
            n -= 1
        return nonsimilar
    def generatedataset(self,n):
        similar = self.getsimilar(n)
        nonsimilar= self.getnonsimilar(n)
        output={}

        count=0
        for i,s,n in zip(range(len(similar)),similar,nonsimilar):
            filedata = {}
            for k,v in s.items():
                # Open a file: file
                file = open(v,mode='r')
 
                # read all lines at once
                filedata[k] =  file.read()#.replace('"', '\\"').replace('\n', '\\n')
                # close the file
                file.close()
                # copy the file
                #shutil.copy(v,location)
            filedata['label'] = '1'
            output[count] = filedata
            count +=1

            filedata={}
            for k,v in n.items():
                # Open a file: file
                file = open(v,mode='r')
 
                # read all lines at once
                filedata[k] = file.read()#.replace('"', '\\"').replace('\n', '\\n')
                # close the file
                file.close()
                # copy the file
                #shutil.copy(v,location)

            filedata['label'] = '0'
            output[count] = filedata
            count +=1

        return output


def main(argv):
    # process arguments

    homeworkDir= ''
    groundtruth = ''
    outputfile=''
    n = 0
    
    try:
        opts, args = getopt.getopt(argv[1:],"hs:d:o:n:",["source=","desc=","ofile=","samples="])
    except getopt.GetoptError:
        print(f'{argv[0]} --s <sourcedir> --d <groundtruthfile> --o <outputfile> --n <numberofsamples>')
        sys.exit()

    for opt, arg in opts:
        if opt == '-h':
            print(f'{argv[0]} --source <sourcedir> --desc <groundtruthfile> --o <outputfile> --samples <numberofsamples>')
            sys.exit(2)
        elif opt in ("-s", "--source"):
            homeworkDir= arg
        elif opt in ("-d", "--desc"):
            groundtruth= arg
        elif opt in ("-o", "--ofile"):
            outputfile= arg
        elif opt in ("-n", "--samples"):
            n= int(arg)

    #print(f'{homeworkDir} {groundtruth} {outputfile} {n}')

    s = SimilarityManager(homeworkDir,['.c','.cpp'],groundtruth)
    d = s.generatedataset(n)
    with open(outputfile, 'w') as outfile:
        json.dump(d, outfile,sort_keys=True, indent=4)

    return
    with open(outputfile) as json_file:
        data = json.load(json_file)
        print(json.dumps(data,sort_keys=True, indent=4))

if __name__ == '__main__':
    main(sys.argv)
    #similar = s.getsimilar(n)
    #nonsimilar= s.getnonsimilar(n)
    
    #print('similar', json.dumps(similar,sort_keys=True, indent=4))
    #print('nonsimilar', json.dumps(nonsimilar,sort_keys=True, indent=4))

    #print('data', json.dumps(d,sort_keys=True, indent=4))
