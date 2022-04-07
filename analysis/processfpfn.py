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

from sklearn.model_selection import train_test_split

#

bertfalseneg = pd.read_csv('bertfalseneg.csv',index_col=0)
bertfalsepos = pd.read_csv('bertfalsepos.csv',index_col=0)
codebertfalseneg = pd.read_csv('codebertfalseneg.csv',index_col=0)
codebertfalsepos = pd.read_csv('codebertfalsepos.csv',index_col=0)

berttrueneg = pd.read_csv('berttrueneg.csv',index_col=0)
berttruepos = pd.read_csv('berttruepos.csv',index_col=0)
codeberttrueneg = pd.read_csv('codeberttrueneg.csv',index_col=0)
codeberttruepos = pd.read_csv('codeberttruepos.csv',index_col=0)

bertfalsenegdiff = bertfalseneg.loc[bertfalseneg.index.difference(codebertfalseneg.index)]
bertfalseposdiff =  bertfalsepos.loc[bertfalsepos.index.difference(codebertfalsepos.index)]
berttruenegdiff=berttrueneg.loc[berttrueneg.index.difference(codeberttrueneg.index)]
berttrueposdiff=berttruepos.loc[berttruepos.index.difference(codeberttruepos.index)]

codebertfalsenegdiff=codebertfalseneg.loc[codebertfalseneg.index.difference(bertfalseneg.index)]
codebertfalseposdiff=codebertfalsepos.loc[codebertfalsepos.index.difference(bertfalsepos.index)]
codeberttruenegdiff=codeberttrueneg.loc[codeberttrueneg.index.difference(berttrueneg.index)]
codeberttrueposdiff=codeberttruepos.loc[codeberttruepos.index.difference(berttruepos.index)]

bertfalsenegint = bertfalseneg.loc[bertfalseneg.index.intersection(codebertfalseneg.index)]
bertfalseposint = bertfalsepos.loc[bertfalsepos.index.intersection(codebertfalsepos.index)]
berttrueposint = berttruepos.loc[berttruepos.index.intersection(codeberttruepos.index)]
berttruenegint = berttrueneg.loc[berttrueneg.index.intersection(codeberttrueneg.index)]
codebertfalsenegint = codebertfalseneg.loc[codebertfalseneg.index.intersection(bertfalseneg.index)]


codebertfalsenegbetter = bertfalseneg.loc[bertfalseneg.index.difference(bertfalsenegint.index)]
codebertfalseposbetter = bertfalsepos.loc[bertfalsepos.index.difference(bertfalseposint.index)]
codeberttruenegbetter = codeberttrueneg.loc[codeberttrueneg.index.difference(berttruenegint.index)]
codeberttrueposbetter = codeberttruepos.loc[codeberttruepos.index.difference(berttrueposint.index)]

bertfalsenegbetter=codebertfalseneg.loc[codebertfalseneg.index.difference(bertfalsenegint.index)]
bertfalseposbetter=codebertfalsepos.loc[codebertfalsepos.index.difference(bertfalseposint.index)]
berttruenegbetter=berttrueneg.loc[berttrueneg.index.difference(berttruenegint.index)]
berttrueposbetter=berttruepos.loc[berttruepos.index.difference(berttrueposint.index)]


print(len(int_df))
print(f'codebert : {[[len(codeberttrueneg),len(codebertfalsepos)],[len(codebertfalseneg),len(codeberttruepos)]]}')
print(f'bert : {[[len(berttrueneg),len(bertfalsepos)],[len(bertfalseneg),len(berttruepos)]]}')

codebertfalsenegdiff[codebertfalsenegdiff['source0'] != codebertfalsenegdiff['source1']][['source0','source1']]
a = codebertfalsenegdiff
a[a['source0'] != a['source1']][['source0','source1']]

# cases where codebert does not have false positive
#pp.pprint(str(a[a['source0'] != a['source1']][['source1']][:1]))
#pp.pprint(str(a[a['source0'] != a['source1']][['source0']][:1]))
#notsim = (a[a['source0'] != a['source1']][:1])

av = a#[a['source0'] != a['source1']]

def printcommon(av,title):
    
    print('-'*30,title,'-'*30)
    
    for i in range(len(av)):
        notsim = (av.iloc[i])
        print(f"{i} plagiarize={notsim['plagiarized']} percent={notsim['percent']}, source0 length = {len(notsim['source0'])} source1 length = {len(notsim['source1'])}", '-'*50,'\n\n')
        print_side_by_side(notsim['source0'][:512],notsim['source1'][:512])#,delimiter='|++|')

# codebert false positive better
a = codebertfalseposbetter
printcommon(a,'CodeBERT Improved False Positive Over BERT')

# cases where codebert false negative better
a = codebertfalsenegbetter
printcommon(a,'CodeBERT Improved False Negative Over BERT')


# cases where codebert true negative is better
a = codeberttruenegbetter
printcommon(a,'CodeBERT Improved True Negative Over BERT')

# cases where codebert true positive is better
a = codeberttrueposbetter
printcommon(a,'CodeBERT Improved True Positive Over BERT')


# cases where BERTcodebert true positive is better
a = berttrueposbetter
printcommon(a,'BERT Improved True Positive Over CodeBERT')


    
