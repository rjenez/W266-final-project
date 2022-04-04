# Files for generating dataset
#
The key part of generating our dataset is to combine  key data from
[PROGRAMMING HOMEWORK DATASET FOR PLAGIARISM DETECTION](https://dx.doi.org/10.21227/71fw-ss32) which has
Subfolders of this folder are named after courses: A2016, A2017, B2016 and B2017. This further contain subfolders
for individual assignments. On each course students were required to solve 16-22 assignments labeled 
"Z1/Z1", "Z1/Z2", "Z2/Z1" etc. Finally, in each folder are actual C or C++ files named after student (anonymized, 
so actual student names were replaced by strings in form "student1393").
[samples.json](./samples.json) - File that details all the direcories to use for comparison in mosscompare.py <br>
[gathermoss.sh](./gathermoss.sh) - This simple script repeats trying to run MOSS service against all the files in directories in samples.json by invoking mosscompare.p and storing results in the local directory. It is first important to make a directory for the reports, cd into that directory and the references will allwork against the files in the plagiaristm directory. The output of running this will be a series of html files that represent the results of the MOSS comparisons for the files that were sent.<br>
[generatedata.sh](./generatedata.sh) - older generation script that produces data just based upon the plagiarism dataset without MOSS output.<br>
[generatedataset.sh](./generatedataset.sh) - genreate training and test csv files. It reads the html files gneraed by gathermoss.sh and the identified plagiarized files by students in ground-truth-static-anon.txt file. The results can be packaged in a tar file and in our case we push to a GCP bucket. From there we pick up the results in our Google Colab environments.<br>
[gethwplag.sh](./gethwplag.sh) - Download the plagiarized homework dataset. Note requires access to IEEE dataport. <br>

