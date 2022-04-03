### Main Data directory
This directory contains main training data and archived results of MOSS runs and resource dataset.<br>
[programming-homework-dataset-plagiarism-detection](./programming-homework-dataset-plagiarism-detection) - Main plagiarized data set of 
c/c++ files that are used in <br>
 our core data set. More details on the dataset and organization in the readme.txt in that directory<br>
[training](./training) - Main data used for training in train2.csv and test2.csv (and tar-ed into plag2.tar 
that is uploaded to our GCP storage bucket and accessed in colab).<br>
[mossbase03042022 ](./mossbase03042022( - consolidated data from MOSS run which takes days to generate that was used as basis for our current training and test dataset.
More details in the mosscompare.py script that is used to generate it. The directory is tar-ed, gzipped and broken into 50M chunks to store in github. <br>
[mossbase03142022](./mossbase03142022) - second consolidated MOSS run, that is not currently used but is more extensive and can be uesd for future model building. Broken up
in chunks as above to store in github. <br>
[problemsFPFN.txt](./problemsFPFN.txt) - Brief notes on the output of our model runs around the outcomes for FP/FN and what we could do to improve our models. <br>
