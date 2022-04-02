#!/bin/sh
# get data from MOSS comparisons and create data set.
python ../readurl.py --ground-truth='../../data/programming-homework-dataset-plagiarism-detection/ground-truth-static-anon.txt' -p 0 --baseurl 'file:///Users/rrj/Documents/courses/MIDS/W266/W266-final-project/src/mossreports03042022' reportA2016_Z1_Z1.html reportA2016_Z1_Z2.html reportA2016_Z1_Z4.html
python ../readurl.py --ground-truth='../../data/programming-homework-dataset-plagiarism-detection/ground-truth-static-anon.txt' -p 0 --baseurl 'file:///Users/rrj/Documents/courses/MIDS/W266/W266-final-project/src/mossreports03142022' reportA2016*.html reportA2017*.html
