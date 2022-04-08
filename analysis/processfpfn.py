#
# FP/FN/TP/TN data and do analysis of errors.
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
from side_by_side import print_side_by_side

from sklearn.metrics.pairwise import cosine_similarity
from sklearn.metrics import precision_recall_fscore_support
from sklearn.metrics import f1_score,confusion_matrix,precision_score,recall_score,precision_recall_fscore_support,accuracy_score
from sklearn.metrics import average_precision_score
from sklearn.metrics import auc, plot_precision_recall_curve, precision_recall_curve
from scipy.spatial import distance
from tqdm.notebook import tqdm
from imblearn.over_sampling import RandomOverSampler
from tabulate import tabulate
from sklearn.model_selection import train_test_split

#
percent_threshold = 71.00000000000006
test_df = pd.read_csv('test2.csv')
oversample = RandomOverSampler(sampling_strategy='minority',random_state=1234)

test_over, y_test_over = oversample.fit_resample(test_df, test_df.plagiarized)
test_df = test_over


mosstruepos = test_df[np.logical_and(test_df['percent'] >= percent_threshold,test_df['plagiarized'] == 1)]
mossfalsepos = test_df[np.logical_and(test_df['percent'] >= percent_threshold,test_df['plagiarized'] == 0)]
mosstrueneg = test_df[np.logical_and(test_df['percent'] < percent_threshold,test_df['plagiarized'] == 0)]
mossfalseneg = test_df[np.logical_and(test_df['percent'] < percent_threshold,test_df['plagiarized'] == 1)]

bertfalseneg = pd.read_csv('bertfalseneg.csv',index_col=0)
bertfalsepos = pd.read_csv('bertfalsepos.csv',index_col=0)
codebertfalseneg = pd.read_csv('codebertfalseneg.csv',index_col=0)
codebertfalsepos = pd.read_csv('codebertfalsepos.csv',index_col=0)

berttrueneg = pd.read_csv('berttrueneg.csv',index_col=0)
berttruepos = pd.read_csv('berttruepos.csv',index_col=0)
codeberttrueneg = pd.read_csv('codeberttrueneg.csv',index_col=0)
codeberttruepos = pd.read_csv('codeberttruepos.csv',index_col=0)

"""
p = pd.merge(bertfalsepos[['filename0','filename1']], codebertfalsepos[['filename0','filename1']], how='outer', indicator=True)
m=p.where(p._merge =='both').dropna().drop_duplicates()
bertfalseposint = bertfalsepos.merge(m, on=['filename0','filename1'])
codebertfalseposint = codebertfalsepos.merge(m, on=['filename0','filename1'])
m=p.where(p._merge =='left_only').dropna().drop_duplicates()
bertfalseposdiff = bertfalsepos.merge(m, on=['filename0','filename1'])
m=p.where(p._merge =='right_only').dropna().drop_duplicates()
codebertfalseposdiff = codebertfalsepos.merge(m, on=['filename0','filename1'])

p = pd.merge(bertfalseneg[['filename0','filename1']], codebertfalseneg[['filename0','filename1']], how='outer', indicator=True)
m=p.where(p._merge =='both').dropna().drop_duplicates()
bertfalsenegint = bertfalseneg.merge(m, on=['filename0','filename1'])
codebertfalsenegint = codebertfalseneg.merge(m, on=['filename0','filename1'])
m=p.where(p._merge =='left_only').dropna().drop_duplicates()
bertfalsenegdiff = bertfalseneg.merge(m, on=['filename0','filename1'])
m=p.where(p._merge =='right_only').dropna().drop_duplicates()
codebertfalsenegdiff = codebertfalseneg.merge(m, on=['filename0','filename1'])


p = pd.merge(berttrueneg[['filename0','filename1']], codeberttrueneg[['filename0','filename1']], how='outer', indicator=True)
m=p.where(p._merge =='both').dropna().drop_duplicates()
berttruenegint = berttrueneg.merge(m, on=['filename0','filename1'])
codeberttruenegint = codeberttrueneg.merge(m, on=['filename0','filename1'])
m=p.where(p._merge =='left_only').dropna().drop_duplicates()
berttruenegdiff = berttrueneg.merge(m, on=['filename0','filename1'])
m=p.where(p._merge =='right_only').dropna().drop_duplicates()
codeberttruenegdiff = codeberttrueneg.merge(m, on=['filename0','filename1'])


p = pd.merge(berttruepos[['filename0','filename1']], codeberttruepos[['filename0','filename1']], how='outer', indicator=True)
m=p.where(p._merge =='both').dropna().drop_duplicates()
berttrueposint = berttruepos.merge(m, on=['filename0','filename1'])
codeberttrueposint = codeberttruepos.merge(m, on=['filename0','filename1'])
m=p.where(p._merge =='left_only').dropna().drop_duplicates()
berttrueposdiff = berttruepos.merge(m, on=['filename0','filename1'])
m=p.where(p._merge =='right_only').dropna().drop_duplicates()
codeberttrueposdiff = codeberttruepos.merge(m, on=['filename0','filename1'])
"""

def printcommon(av,title):
    
    print('-'*30,title,'-'*30)
    
    for i in range(len(av)):
        notsim = (av.iloc[i])
        print(f"{i} plagiarize={notsim['plagiarized']} percent={notsim['percent']}, source0 length = {len(notsim['source0'])} source1 length = {len(notsim['source1'])}", '-'*50,'\n\n')
        print_side_by_side(notsim['source0'][:512],notsim['source1'][:512])#,delimiter='|++|')

"""
# codebert false positive better
a = codebertfalseposdiff
printcommon(a,'CodeBERT Improved False Positive Over BERT')

# cases where codebert false negative better
a = codebertfalsenegdiff
printcommon(a,'CodeBERT Improved False Negative Over BERT')


# cases where codebert true negative is better
a = codeberttruenegdiff
printcommon(a,'CodeBERT Improved True Negative Over BERT')

# cases where codebert true positive is better
a = codeberttrueposdiff
printcommon(a,'CodeBERT Improved True Positive Over BERT')


# cases where BERTcodebert true positive is better
a = berttrueposdiff
printcommon(a,'BERT Improved True Positive Over CodeBERT')
"""
def generatedifferences(fp1,fp2,fn1,fn2,tn1,tn2,tp1,tp2):
    p = pd.merge(fp1[['filename0','filename1']], fp2[['filename0','filename1']], how='outer', indicator=True)
    m=p.where(p._merge =='both').dropna().drop_duplicates()
    fp1int = fp1.merge(m, on=['filename0','filename1'])
    fp2int = fp2.merge(m, on=['filename0','filename1'])
    m=p.where(p._merge =='left_only').dropna().drop_duplicates()
    fp1diff = fp1.merge(m, on=['filename0','filename1'])
    m=p.where(p._merge =='right_only').dropna().drop_duplicates()
    fp2diff = fp2.merge(m, on=['filename0','filename1'])
    p = pd.merge(fn1[['filename0','filename1']], fn2[['filename0','filename1']], how='outer', indicator=True)
    m=p.where(p._merge =='both').dropna().drop_duplicates()
    fn1int = fn1.merge(m, on=['filename0','filename1'])
    fn2int = fn2.merge(m, on=['filename0','filename1'])
    m=p.where(p._merge =='left_only').dropna().drop_duplicates()
    fn1diff = fn1.merge(m, on=['filename0','filename1'])
    m=p.where(p._merge =='right_only').dropna().drop_duplicates()
    fn2diff = fn2.merge(m, on=['filename0','filename1'])
    p = pd.merge(tn1[['filename0','filename1']], tn2[['filename0','filename1']], how='outer', indicator=True)
    m=p.where(p._merge =='both').dropna().drop_duplicates()
    tn1int = tn1.merge(m, on=['filename0','filename1'])
    tn2int = tn2.merge(m, on=['filename0','filename1'])
    m=p.where(p._merge =='left_only').dropna().drop_duplicates()
    tn1diff = tn1.merge(m, on=['filename0','filename1'])
    m=p.where(p._merge =='right_only').dropna().drop_duplicates()
    tn2diff = tn2.merge(m, on=['filename0','filename1'])
    p = pd.merge(tp1[['filename0','filename1']], tp2[['filename0','filename1']], how='outer', indicator=True)
    m=p.where(p._merge =='both').dropna().drop_duplicates()
    tp1int = tp1.merge(m, on=['filename0','filename1'])
    tp2int = tp2.merge(m, on=['filename0','filename1'])
    m=p.where(p._merge =='left_only').dropna().drop_duplicates()
    tp1diff = tp1.merge(m, on=['filename0','filename1'])
    m=p.where(p._merge =='right_only').dropna().drop_duplicates()
    tp2diff = tp2.merge(m, on=['filename0','filename1'])
    return [[tn1, tn1diff,fp1, fp1diff,fn1, fn1diff, tp1, tp1diff],[tn2, tn2diff,fp2, fp2diff,fn2, fn2diff, tp2, tp2diff]]
#    return [[tn1, tn1int,tn1diff,fp1, fp1int,fp1diff,fn1, fn1int,fn1diff, tp1, tp1int,tp1diff],
#            [tn2, tn2int,tn2diff,fp2, fp2int,fp2diff,fn2, fn2int,fn2diff, tp2, tp2int,tp2diff]]




def printmatrix(m):
    for line in m:
        print(*line)


print('codebert-MOSS differences : \n')

def assembledataframe(columns, m1,m2):
    d = {}
    for c,m,cb in zip(columns,m1,m2):
        d[c] = [m,cb]
    df = pd.DataFrame(d)
    return df


compmatrix =  generatedifferences(mossfalsepos,codebertfalsepos, mossfalseneg,codebertfalseneg,
                                  mosstrueneg,codeberttrueneg,mosstruepos,codeberttruepos)

compmatrix1 =  generatedifferences(mossfalsepos,bertfalsepos, mossfalseneg,bertfalseneg,
                                   mosstrueneg,berttrueneg,mosstruepos,berttruepos)

compmatrix2 =  generatedifferences(codebertfalsepos,bertfalsepos, codebertfalseneg,bertfalseneg,
                                   codeberttrueneg,berttrueneg,codeberttruepos,berttruepos)
#columns = ['Model Comparison', 'tn','tn-common','tn-diff','fp','fp-common','fp-diff','fn','fn-common','fn-diff','tp','tp-common','tp-diff']
columns = ['Model Comparison', 'tn','tn-diff','fp','fp-diff','fn','fn-diff','tp','tp-diff']
mosscodebert = ['MOSS-Codebert'] + list(map(len, compmatrix[0]))
codebertmoss = ['Codebert-MOSS'] + list(map(len, compmatrix[1]))
mossbert = ['MOSS-BERT'] + list(map(len, compmatrix1[0]))
bertmoss = ['BERT-MOSS'] + list(map(len, compmatrix1[1]))
codebertbert = ['CodeBERT-BERT'] + list(map(len, compmatrix2[0]))
bertcodebert = ['BERT-CodeBERT'] + list(map(len, compmatrix2[1]))

#df1 = assembledataframe(columns,mosscodebert,codebertmoss)
df2 = assembledataframe(columns,mossbert,bertmoss)
df3 = assembledataframe(columns,codebertbert,bertcodebert)
#print(tabulate(pd.concat([df1,df2,df3],ignore_index=True).set_index('Model Comparison'), headers = 'keys', tablefmt = 'psql'))
print(tabulate(pd.concat([df2,df3],ignore_index=True).set_index('Model Comparison'), headers = 'keys', tablefmt = 'psql'))

print('codebert-MOSS :\n')
printmatrix([['tn','fp',],['fn','tp',]])
m = [[len(codeberttrueneg), len(codebertfalsepos)],[len(codebertfalseneg),len(codeberttruepos)]]
printmatrix(m)

print('MOSS-codebert :\n ')
printmatrix([['tn','fp',],['fn','tp',]])
m = [[len(mosstrueneg), len(mossfalsepos)],[len(mossfalseneg),len(mosstruepos)]]
printmatrix(m)

y_true, y_pred = test_df['plagiarized'], test_df['percent'] >= percent_threshold
r = np.flip(confusion_matrix(y_true,y_pred))
print('Confusion matrix:\n', r)

precision_c, recall_c, thresholds = precision_recall_curve(y_true, y_pred)
auc_precision_recall = auc(recall_c, precision_c)
print(f'AUCpr = {auc_precision_recall}')

accuracy = accuracy_score(y_true=y_true, y_pred=y_pred)
print(f'accuracy = {accuracy}')

precision = precision_score(y_true=y_true, y_pred=y_pred)
print(f'precision = {precision}')

recall = recall_score(y_true=y_true, y_pred=y_pred)
print(f'recall={recall}')

f1 = f1_score(y_true=y_true, y_pred=y_pred)
print(f'f1={f1}')
