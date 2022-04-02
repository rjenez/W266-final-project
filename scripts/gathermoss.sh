#!/bin/sh
# get moss comparisons done
# instructions:
# create directory for the moss comparison output
# then execute this file to do the moss comparisons and outputs train.csv, test.cvs, and alldata.csv ...
# this data can be packaged and checked in
#
# this example compares files in the directories of samples.json and marks the comparisons as being plagiaried if they are in ground-truth-static-anon.txt
# note if blocks of code appears over 50 times [-m 50 ] allows us to exclude common blocks from comparison from all files
#
for i in {1..20}; do  python ../mosscompare.py -s ../samples.json -e ../../data/programming-homework-dataset-plagiarism-detection/ground-truth-static-anon.txt -i ../../data/programming-homework-dataset-plagiarism-detection/src/ -d reporttest -o report -n 1000  -m 50 -v 1 -u 845202178; sleep 300;  done

# this is commented out, # note if blocks of code appears over 1000000 times [-m 1000000 ] allows us to exclude common blocks from comparison from all files
#for i in {1..20}; do python ../mosscompare.py -s ../samples.json -e ../../data/programming-homework-dataset-plagiarism-detection/ground-truth-static-anon.txt -i ../../data/programming-homework-dataset-plagiarism-detection/src/ -d reporttest -o report -n 1000  -m 1000000 -v 1 -u 752204224; sleep 300;  done

