import os
import sys, getopt
import shutil
import numpy as np
import json
import time
from itertools import combinations
from collections import OrderedDict
import random
#import moss as mosspy
import mosspy

#userid = 987654321
#userid=753680109
#userid=571722601
userid = 335919964

#m = mosspy.Moss(userid, "python")
m = mosspy.Moss(userid, "c")

#m.addBaseFile("submission/a01.py")
#m.addBaseFile("submission/test_student.py")
#m.addBaseFile("../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z1/Z1/student1013.c")
#m.addBaseFile("../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z4/Z3/student2704.c")

# Submission Files
#m.addFile("submission/a01-sample.py")
#m.addFilesByWildcard("submission/a01-*.py")
m.addFilesByWildcard("../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z1/Z1/student1*.c")
#m.addFile("../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z4/Z3/student3315.c")
# progress function optional, run on every file uploaded
# result is submission URL
url = m.send(lambda file_path, display_name: print('*', end='', flush=True))
#print()

print ("Report Url: " + url)

# Save report file
#m.saveWebPage(url, "submission/report.html")
m.saveWebPage(url, "report3.html")
# Download whole report locally including code diff links
#mosspy.download_report(url, "submission/report/", connections=8, log_level=10, on_read=lambda url: print('*', end='', flush=True))
mosspy.download_report(url, "report3/", connections=8, log_level=10, on_read=lambda url: print('*', end='', flush=True))
