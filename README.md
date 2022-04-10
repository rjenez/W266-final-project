# W266-final-project

## Team: Albert (Yu) Jiang, Joe Mirza, Ricardo Jenez

### Title: Rolling Stone: A System To Do Plagiarism Detection Of Software.
This is the main area for our project to analyze the performance of Transformer models against industry standard [MOSS](https://theory.stanford.edu/~aiken/publications/papers/sigmod03.pdf) for plagiarism detection. <p>

## Directory Structure and Replicating Results
[w266_final_project_jiang_jenez_mirza.pdf](./w266_final_project_jiang_jenez_mirza.pdf) - Final paper.
[w266_draft_project_Jiang_Jenez_Mirza_source_code](./w266_draft_project_Jiang_Jenez_Mirza_source_code) - Final paper source.
[analysis](./analysis) - Directory containing all code associated with final analysis of MOSS v. BERT v. CodeBERT.<br>
[antlr](./antlr) - ANTLR preprocessing library<br>
[data](./data) - Main area for Plagiarism homework data and the MOSS generated data.<br>
[models](./models) - Our saved final model for CodeBERT<br>
[notebook](./notebooks) - Main area for all the notebooks that we used to generate the data for our paper.<br>
[oscar](./oscar) - Area for data and replication of the resuls for the paper by [Oscar Karnalim](https://arxiv.org/pdf/1805.11035.pdf)<br>
[scripts](./scripts) - Scripts for data generation and construction.<br>
[src](./src) - Python files used in data generation and construction.<p>
## Paper Details
### Abstract:
Software plagiarism is a growing issue in university and commercial software development environments. The true state of the art in these systems NLP-PL (Natural Language Processing - Programming Languages) has not advanced as quickly as in pure NLP environments. We propose to test and extend NLP systems that will perform Code Similarity Detection on Software (C/C++, Python, Java) code using state of the art deep learning architectures. This system will allow the detection of similar code programs (not just snippets) and determine if there is sufficient similarity between code examples to warrant further review for plagiarism. The goal will be to outperform an industry-standard similarity detection system, called MOSS (“Measure Of Software Similarity”) which uses text fingerprinting\cite{schleimer} to identify software similarity.

Proposal and Steps:
We will use NLP tools to build a plagiarism detector using a dataset based on code snippets from actual student assignments (Datasets #1, #2 below) and Stack Overflow (SO) modified datasets (Datasets #s 3,4,5) . We intend to benchmark MOSS on these datasets and see how effectively Rolling Stone can perform against MOSS.

We may build our  NLP system on top of transformers like BERT and code-specific transformers like CodeBerta (perhaps even CODEX if we gain access). The goal will be to use these systems trained on datasets (#1, #2)  to identify similar code snippets above five lines from the SO-related dataset (#3,4,5).

Once we have Rolling Stone functioning, we intend to compare how it performs against specific systems designed to defeat plagiarism detection (“Mossad: Defeating Software Plagiarism Detection” (https://arxiv.org/abs/2010.01700)) and validate whether our system can do better than MOSS when presented with sophisticated tools built to evade plagiarism detection.
<<<Done Main Proposal>>>

### Motivation:
  In many colleges and universities, there is an increased incidence of plagiarism in code implemented by students in programming assignments \cite{bowyer}. 

Similarly, in industry, there is a danger that commercial code can be “infected” by code snippets taken from the open-source or on popular sites like StackOverflow (SO), leading to liabilities for companies who have unauthorized use of open source in their products. Additionally, copy and paste code leads to more brittle code bases. Detecting similar code fragments that are swept up into common functions or classes would significantly reduce code complexity and size. (“Recent studies have shown that developers use SO snippets in their software projects, regardless of maintainability, security, and licensing implications (citations redacted). Assuming that developers copy and paste snippets from SO without trying to thoroughly understand them, maintenance issues arise”. \cite{baltes}.

The most used plagiarism detection tool MOSS (“Measure Of Software Similarity”  (https://theory.stanford.edu/~aiken/moss) andWinnowing: Local Algorithms for Document Fingerprinting” (https://theory.stanford.edu/~aiken/publications/papers/sigmod03.pd ), was developed at UC Berkeley by Alex Aiken, et al. based upon the paper\cite{schleimer}. MOSS has been in use for over 20 years and is still the gold standard. One question we are attempting to answer is: Given the subsequent advances in NLP and Deep Learning, could we use these techniques to develop a solution that's more effective than MOSS?

The advent of attention-oriented architectures such as Transformers \cite{viswani} and the language models they've enabled, such as BERT\cite{devlin} and T5\cite{raffel}, would seem to provide an opportunity to advance the state of the art in this area. Programming Language (PL) variants, trained on large code corpora, seem even more promising. 

One challenge for the systems named above is that the code files being examined for similarity may contain between 4,000 and 10,000 tokens, far exceeding those systems' maximum input lengths of 512 tokens. So while these transformer architectures may provide benefits, we need to consider architectures that could encode event larger files, such as Sentence-BERT\cite{reimers}[512 tokens], LongT5\cite{guo}[up to 4K tokens], LongFormer\cite{beltagy}[up to 16K tokens] and PoolingFormer\cite{zhang}[up to 16K tokens], all of which might better help determine the similarity between entire documents. In all of these cases, except for CodeBERT, they are not trained specifically on programming languages.

  ### Datasets 

1. Programming Homework Dataset for Plagiarism Detection (https://ieee-dataport.org/open-access/programming-homework-dataset-plagiarism-detection)<br>
Dataset is intended for studying how student programming styles and usage of IDE differs between students who plagiarise their homework and students who solve them honestly.
2. IR-Plag data set (Personal communication with author Oscar Karnalim)
Benefit: it is canonically mapped
Drawback: Small size and only cover introductory programming
https://doi.org/10.15388/infedu.2019.15
https://github.com/oscarkarnalim/sourcecodeplagiarismdataset
3. StaQC: A Systematically Mined Question-Code Dataset from Stack Overflow
https://github.com/LittleYUYU/StackOverflow-Question-Code-Data
StaQC (Stack Overflow Question-Code pairs) is the largest dataset to date of around 148K Python and 120K SQL domain question-code pairs, which are automatically mined from Stack Overflow using a Bi-View Hierarchical Neural Network, as described in the paper "StaQC: A Systematically Mined Question-Code Dataset from Stack Overflow" (WWW'18). 
4. Conala data source for https://conala-corpus.github.io
This challenge was designed to test systems for generating program snippets from natural language. For example, if the input is sort list x in reverse order, then the system would be required to output x.sort(reverse=True) in Python.
Dataset Information
We have released a dataset crawled from Stack Overflow, automatically filtered, then curated by annotators, split into 2,379 training and 500 test examples (read more about the process here). We also provide a large automatically-mined dataset with 600k examples and links to other similar datasets. These data sets can be used for the CoNaLa challenge or for any other research on the intersection of code and natural language.
--- Use this to look at snippets of similar intent and see how the plagiarism detector would grade them (does it present the same results as a well-trained user?). 
5. Stack Overflow - Self Annotated
We have access to the Stack Overflow dataset of millions of questions and code answer pairs, so if the above examples for data sources are insufficient, we can annotate several thousand quickly using StaQC and Conala as templates for templates building a dataset. We could even imagine passing code segments through MOSS as a first pass to determine the similarity between code snippets or simply taking code snippets of an appropriate size and running a source code obfuscator to generate the plagiarized sets.
  
  
### Papers:
- “Winnowing: Local Algorithms for Document Fingerprinting” (https://theory.stanford.edu/~aiken/publications/papers/sigmod03.pdf).
- “Experience Using ”MOSS” to Detect Cheating On Programming Assignments”, Kevin W. Bowyer and Lawrence O. Hall https://www3.nd.edu/~kwb/nsf-ufe/1110.pdf).
- “Mossad: Defeating Software Plagiarism Detection” (https://arxiv.org/abs/2010.01700)
- “SOTorrent: Reconstructing and Analyzing the Evolution of Stack Overflow Posts” https://arxiv.org/pdf/1803.07311.pdf)
- “Are Neural Language Models Good Plagiarists? A Benchmark for Neural Paraphrase Detection” https://arxiv.org/abs/2103.12450
- “Neural Language Models are Effective Plagiarists” https://arxiv.org/abs/2201.07406
- “NLP based Deep Learning Approach for Plagiarism Detection” (http://rochi.utcluj.ro/ijusi/articles/IJUSI-13-1-Rosu.pdf)
- “StaQC: A Systematically Mined Question-Code Dataset from Stack Overflow” https://arxiv.org/abs/1803.09371
- “A Study on Plagiarism Detection and Plagiarism Direction Identification Using Natural Language Processing Techniques”
https://wlv.openrepository.com/bitstream/handle/2436/298219/h?sequence=1
- “Unsupervised Learning Based Approach for Plagiarism Detection in Programming Assignments” https://cdn.iiit.ac.in/cdn/cvit.iiit.ac.in/images/ConferencePapers/2017/cv_17Plagiarism-Detection.pdf
- “Source code plagiarism detection in academia with information retrieval: Dataset and the observation. Informatics in Education,” 18(2):321–344, 2019. https://www.researchgate.net/publication/337013123_Source_Code_Plagiarism_Detection_in_Academia_with_Information_Retrieval_Dataset_and_the_Observation
- “Python Source Code Obfuscation”
https://medium.com/geekculture/python-source-code-obfuscation-6b97f88a460d

#### Systems
- BERT/Roberta/DistilBert/XLNet https://towardsdatascience.com/bert-roberta-distilbert-xlnet-which-one-to-use-3d5ab82ba5f8

- CodeBERT


#### Metrics )
- Maximize the F1-score
  - Highest Precision, Recall and Accuracy.

 





