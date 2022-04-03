#!/bin/sh
#python processhomework.py --source='../data/programming-homework-dataset-plagiarism-detection/src' --desc='../data/programming-homework-dataset-plagiarism-detection/ground-truth-static-anon.txt' --odir='../data/programming-homework-dataset-plagiarism-detection' --samples=10
python processhomework.py --source='../data/programming-homework-dataset-plagiarism-detection/src' --desc='../data/programming-homework-dataset-plagiarism-detection/ground-truth-static-anon.txt' --odir='.' --samples=$1


