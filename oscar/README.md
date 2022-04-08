Oscar Code Efforts
This directory contains work done to replicate and adapt Oscar's paper from https://www.researchgate.net/publication/337013123_Source_Code_Plagiarism_Detection_in_Academia_with_Information_Retrieval_Dataset_and_the_Observation.

The IR-Plag-Dataset subdirectory contains Oscar's original Java code dataset.  The main.py file attempts to replicate Oscar's rkr-gst, VSM, and LM based techniques, which needs antlr_java to parse the Java files and mjwise-rkr-gst-master to run rkr-gst.  Due to missing technical parameters, we only pursued our dataset using the VSM and LM based techniques.  The test_cpp.py file runs the VSM and LM based techniques on our C/C++ dataset, which requires antlr_cpp to parse the C/C++ files.  Both the test.txt and test_cpp.c files are just test files to make sure the ANTLR parsing is working as intended.