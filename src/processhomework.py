import os
import sys, getopt
import shutil
import numpy as np
import pandas as pd
import json
from itertools import combinations
from itertools import chain
import random

homeworkDir='../data/programming-homework-dataset-plagiarism-detection/src'
groundtruth='../data/programming-homework-dataset-plagiarism-detection/ground-truth-static.txt'
groundtruth='../data/programming-homework-dataset-plagiarism-detection/ground-truth-anon.txt'
groundtruth='../data/programming-homework-dataset-plagiarism-detection/ground-truth-dynamic.txt'
locationfilter=['A2016/Z1/Z1','A2016/Z1/Z2','A2016/Z1/Z3','A2016/Z1/Z4',
                'A2016/Z2/Z1','A2016/Z2/Z2','A2016/Z2/Z3','A2016/Z2/Z4',
                'A2016/Z3/Z1','A2016/Z3/Z2','A2016/Z3/Z3',
                'A2016/Z4/Z1','A2016/Z4/Z2','A2016/Z4/Z3','A2016/Z4/Z4',
                'A2016/Z5/Z1','A2016/Z5/Z2','A2016/Z5/Z3',
                'A2017/Z1/Z1','A2017/Z1/Z2','A2017/Z1/Z3','A2017/Z1/Z4',
                'A2017/Z2/Z1','A2017/Z2/Z2','A2017/Z2/Z3','A2017/Z2/Z4',
                'A2017/Z3/Z1','A2017/Z3/Z2','A2017/Z3/Z3','A2017/Z3/Z4',
                'A2017/Z4/Z1','A2017/Z4/Z2','A2017/Z4/Z3','A2017/Z4/Z4',
                'A2017/Z5/Z1','A2017/Z5/Z2','A2017/Z5/Z3','A2017/Z5/Z4']


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

        #print('files', json.dumps(allfiles,sort_keys=True, indent=4))

        groundtruthdetail={}
        currentlocation = ""
        currentstudents = {'nonsimilar': [], 'similar':[]}
        with open(groundtruth, 'r') as f:
            for line in f:
                #print(line.rstrip().split(','))
                if line[0] == '-':
                    if currentlocation != "":
                        #print('***',currentlocation)
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
        found = []
        for location in [random.choice(list(self.groundtruthdetail.keys())) for _ in range(n)]:
            #if location not in locationfilter:
            #    continue
            if self.allfiles.get(location,False) is False or self.groundtruthdetail.get(location,False) is False or \
               self.groundtruthdetail[location].get('similar',False) is False or \
               len(self.groundtruthdetail[location]['similar']) < 1: #or len(self.groundtruthdetail[location]['similar'][0]) <= 0:
                    #print('continuing', location,self.groundtruthdetail[location]['similar'],len(self.groundtruthdetail[location]['similar']))
                    #print('____',location,self.groundtruthdetail[location]['similar'])
                    continue
            students = random.choice(self.groundtruthdetail[location]['similar'])
            if students is None or len(students) <= 1:
                continue
            c = random.choice(list(combinations(students,2)))
            if self.allfiles.get(location, False) is False or self.allfiles[location].get(c[0], False) is False or \
               self.allfiles[location].get(c[1], False) is False or \
               (location,c[0],c[1]) in found or (location,c[1],c[0]) in found:
                #print('continuing...@@ ' ,location, c)
                continue
            # don't check for now. just over sample
            found.append((location,c[0],c[1]))
            found.append((location,c[1],c[0]))
            similar.append({c[0]:self.allfiles[location][c[0]],c[1]:self.allfiles[location][c[1]]})
        return similar

    def xxx_getsimilar(self,n):
        similar = []
        found = []
        for location in list(self.groundtruthdetail.keys()):
            #if location not in locationfilter:
            #    continue
            if self.allfiles.get(location,False) is False or self.groundtruthdetail.get(location,False) is False or \
               self.groundtruthdetail[location].get('similar',False) is False:
                if len(self.groundtruthdetail[location]['similar']) <= 0:
                    #print('continuing', location,self.groundtruthdetail[location]['similar'],len(self.groundtruthdetail[location]['similar']))
                    #print('____',location,self.groundtruthdetail[location]['similar'])
                    continue
                
            #students = random.choice(self.groundtruthdetail[location]['similar'])
            for students in self.groundtruthdetail[location]['similar']:
                if students is None or len(students) <= 1:
                    break
                #c = random.choice(list(combinations(students,2)))
                for c in list(combinations(students,2)):
                    if self.allfiles.get(location, False) is False or self.allfiles[location].get(c[0], False) is False or \
                    self.allfiles[location].get(c[1], False) is False or \
                    (location,c[0],c[1]) in found or (location,c[1],c[0]) in found:
                        #print('continuing...@@ ' ,location, c)
                        continue
                    #won't do this check for now
                    #found.append((location,c[0],c[1]))
                    #found.append((location,c[1],c[0]))
                    similar.append({c[0]:self.allfiles[location][c[0]],c[1]:self.allfiles[location][c[1]]})
                    n -= 1
        return similar

    def xxx_getnonsimilar(self,n):
        nonsimilar = []
        found = []
        for location in list(self.groundtruthdetail.keys()):
            #if location not in locationfilter:
            #    continue
            if self.allfiles.get(location,False) is False or self.groundtruthdetail.get(location,False) is False or \
               self.groundtruthdetail[location].get('similar',False) is False or len(self.groundtruthdetail[location]['similar']) <= 0:
                continue

            allstudents = self.groundtruthdetail[location]['similar']
            for  i in range(len(allstudents)-1):
                for student in allstudents[i]:
                    if student is None or len(student) == 0:
                        continue
                    flat = list(np.array(allstudents[i+1]).flatten())
                    flat.append(student)
                    for c in combinations(flat,2):
                        if self.allfiles[location].get(c[0], False) is False or self.allfiles[location].get(c[1], False) is False or \
                           (location,c[0],c[1]) in found or (location,c[1],c[0]) in found:
                            continue
                        found.append((location,c[0],c[1]))
                        found.append((location,c[1],c[0]))
                        nonsimilar.append({c[0]:self.allfiles[location][c[0]],c[1]:self.allfiles[location][c[1]]})
        return nonsimilar                        
                        
    def getnonsimilar(self,n):
        nonsimilar = []
        found = []
        flatlistvals = {}
        filecombinations = {}
        flatlist = []
        for location in [random.choice(list(self.groundtruthdetail.keys())) for _ in range(n)]:
            if self.allfiles.get(location,False) is False or len(self.allfiles[location]) == 0:
                continue
            if filecombinations.get(location,False) is False:
                fc = list(combinations(self.allfiles[location],2))
                filecombinations[location] = fc
            else:
                fc = filecombinations[location]
            c = random.choice(fc)
            if c is None or len(c) <= 1:
                continue

            if flatlistvals.get(location,False) is False:
                flatlist = sum(self.groundtruthdetail.get(location,{}).get('similar',[]),[])
                flatlistvals[location] = flatlist
            else:
                flatlist = flatlistvals[location]

            if (c[0] in flatlist or c[1] in flatlist) or (location,c[0],c[1]) in found or (location,c[1],c[0]) in found:
                continue

            #print(c[0],flatlist,c[0] in flatlist)
            #return

            #if self.allfiles[location].get(c[0][0], False) is False or self.allfiles[location].get(c[1][0], False) is False:
            #    continue
            found.append((location,c[0],c[1]))
            found.append((location,c[1],c[0]))

            nonsimilar.append({c[0]:self.allfiles[location][c[0]],c[1]:self.allfiles[location][c[1]]})

        return nonsimilar

    def generatedataset(self,n):
        #
        # generate the dataset
        #
        similar = self.getsimilar(n)
        nonsimilar= self.getnonsimilar(n)
        train={}
        test={}
        print('generating')
        count=0
        # 70/10/20 split
        sizesimilar = len(similar)
        sizenonsimilar = len(nonsimilar)
        print(sizesimilar,sizenonsimilar)
        trainsizesimilar = int(sizesimilar*0.8)
        trainsizenonsimilar = int(sizenonsimilar*0.8)
        testsizesimilar = sizesimilar-trainsizesimilar
        testsizenonsimilar = sizenonsimilar - trainsizenonsimilar
        
        for s in nonsimilar[:trainsizenonsimilar]:
            filedata = {}
            v = s.values()
            filedata['label'] = '0'
            for f,i in zip(v,range(len(v))):
                #print(f,i)
                # Open a file: file
                with open(f,mode='r') as file:
                    # read all lines at once
                    #print(f)
                    source =  file.read()
                    filedata[f'source{i}'] = source
                    filedata[f'filename{i}'] =  f
                    # copy the file
                #shutil.copy(v,location)
            train[count] = filedata
            count +=1
            filedata={}
            filedata['label'] = '1'
            # get the balanced random sample of plagiarized content
            s = random.choice(similar[:trainsizesimilar])      
            v = s.values()
            for f,i in zip(v,range(len(v))):
                #print(f,i)
                # Open a file: file
                with open(f,mode='r') as file:
                    # read all lines at once
                    source =  file.read()
                    filedata[f'source{i}'] = source
                    filedata[f'filename{i}'] =  f
                    # copy the file
                #shutil.copy(v,location)
            train[count] = filedata
            count +=1
        #print('train: ',json.dumps(train, sort_keys=True, indent=4))
        count = 0
        for s in nonsimilar[trainsizenonsimilar:]:
            filedata = {}
            filedata['label'] = '0'
            v = s.values()
            for f,i in zip(v,range(len(v))):
                # Open a file: file
                #print(f,i)
                with open(f,mode='r') as file:
                    # read all lines at once
                    source =  file.read()
                    filedata[f'source{i}'] = source
                    filedata[f'filename{i}'] =  f
                    # copy the file
                #shutil.copy(v,location)
            test[count] = filedata
            count +=1
            filedata = {}
            filedata['label'] = '1'
            # get the balanced random sample of plagiarized content
            s = random.choice(similar[trainsizesimilar:])      
            v = s.values()
            for f,i in zip(v,range(len(v))):
                # Open a file: file
                with open(f,mode='r') as file:
                    # read all lines at once
                    source =  file.read()
                    filedata[f'source{i}'] = source
                    filedata[f'filename{i}'] =  f
                    # copy the file
                #shutil.copy(v,location)
            test[count] = filedata
            count +=1
        #print('test: ',json.dumps(test, sort_keys=True, indent=4))

        return train,test

def main(argv):
    # process arguments

    homeworkDir= ''
    groundtruth = ''
    outdir=''
    n = 0

    try:
        opts, args = getopt.getopt(argv[1:],"hs:d:o:n:",["source=","desc=","odir=","samples="])
    except getopt.GetoptError:
        print(f'{argv[0]} --s <sourcedir> --d <groundtruthfile> --o <outputdirectory> --n <numberofsamples>')
        sys.exit()

    for opt, arg in opts:
        if opt == '-h':
            print(f'{argv[0]} --s <sourcedir> --d <groundtruthfile> --o <outputdirectory> --n <numberofsamples>')
            sys.exit(2)
        elif opt in ("-s", "--source"):
            homeworkDir= arg
        elif opt in ("-d", "--desc"):
            groundtruth= arg
        elif opt in ("-o", "--odir"):
            outdir= arg
        elif opt in ("-n", "--samples"):
            n= int(arg)

    #print(f'{homeworkDir} {groundtruth} {outputfile} {n}')
    s = SimilarityManager(homeworkDir,['.c','.cpp'],groundtruth)
    train,test = s.generatedataset(n)
    #print(train,test)
    #print('train: ',json.dumps(train, sort_keys=True, indent=4))
    
    dftrain = pd.DataFrame.from_dict(train,orient='index')
    dftest = pd.DataFrame.from_dict(test,orient='index')
    pd.set_option('display.width', 10)
    print(dftrain.shape,dftest.shape)
#    with pd.option_context('display.max_rows', None, 'display.max_columns', None):  # more options can be specified also
#        print(dftrain)
    dftrain.to_csv(os.path.join(outdir, 'train.csv'), encoding='utf-8')
    dftest.to_csv(os.path.join(outdir, 'test.csv'), encoding='utf-8')

#     with open(outputfile, 'w') as outfile:
#         json.dump(d, outfile,sort_keys=True, indent=4)

#     return
#     with open(outputfile) as json_file:
#         data = json.load(json_file)
#         print(json.dumps(data,sort_keys=True, indent=4))

if __name__ == '__main__':
    main(sys.argv)
    #similar = s.getsimilar(n)
    #nonsimilar= s.getnonsimilar(n)
    
    #print('similar', json.dumps(similar,sort_keys=True, indent=4))
    #print('nonsimilar', json.dumps(nonsimilar,sort_keys=True, indent=4))

    #print('data', json.dumps(d,sort_keys=True, indent=4))
