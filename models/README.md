### Final Model File
This directory contains all the final model training for our codebert model that uses ANTLR, 
and whole-word-masking and lower case. These are all one model file split into 50M chuncks. To put them together
just executed:<br>
cat codebert_antlr_lower_4_chunks* > codebert_antlr_lower_4
