# Files for generating dataset
#
The key part of generating our dataset is to combine  key data from
[PROGRAMMING HOMEWORK DATASET FOR PLAGIARISM DETECTION](https://dx.doi.org/10.21227/71fw-ss32) which has
Subfolders of this folder are named after courses: A2016, A2017, B2016 and B2017. This further contain subfolders
for individual assignments. On each course students were required to solve 16-22 assignments labeled 
"Z1/Z1", "Z1/Z2", "Z2/Z1" etc. Finally, in each folder are actual C or C++ files named after student (anonymized, 
so actual student names were replaced by strings in form "student1393").

generatemoss.sh - compares different files and gets the degree of similarity expressed by MOSS and tags each comparison with whether
or not the two comparison files have been plagiarized. The scripts looks at 

[gathermoss.sh](./gathermoss.sh)
[generatedata.sh](./generatedata.sh)
[generatedataset.sh](./generatedataset.sh)
[gethwplag.sh](./gethwplag.sh)
