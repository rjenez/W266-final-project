# Directory For Notebooks For All Experiments
#
[Plagiarism_with_Bert_Trainer_codebert_antlr_lower_4.ipynb](./Plagiarism_with_Bert_Trainer_codebert_antlr_lower_4.ipynb)<br>
[Plagiarism_with_Bert_Trainer_codebert_antlr_lower_4.ipynb](./Plagiarism_with_Bert_Trainer_codebert_antlr_lower_4.ipynb)<br>
[Plagiarism_with_Chinese_Bert.ipynb](./Plagiarism_with_Chinese_Bert.ipynb)<br>
[Plagiarism_with_CodeBert.ipynb](./Plagiarism_with_CodeBert.ipynb)<br>
[Plagiarism_with_Sentence_Transformer.ipynb](./Plagiarism_with_Sentence_Transformer.ipynb)<br>
[Plagiarism_with_Trainer_Classifiers.ipynb](./Plagiarism_with_Trainer_Classifiers.ipynb)<br>
$$

\begin{table}[h]
\centering
\captionsetup{font=small}
\caption{\textsc{Trained Model Performance}}
\fontsize{20}{24}\selectfont 
\label{table:trainedmodels}
\resizebox{\textwidth}{!}{%
\begin{tabular}{llllll}
\hline
\textbf{Model}   & \parbox{15cm}{Experiment Details} & \textbf{Accuracy} & \textbf{Precision}  & \textbf{Recall}  & \textbf{F1-Score}  \\ \hline
\parbox{10cm}{MOSS} & \parbox{15cm}{Similarity 73.1 pcnt - Max Accuracy} & \parbox{7cm}{0.6970} & \parbox{7cm}{0.6840} & \parbox{7cm}{0.7325}  & \parbox{7cm}{0.7074}\\
\midrule
\hline
\parbox{10cm}{BERT}   & \parbox{15cm}{XXX} & \parbox{7cm}{0.7833} & \parbox{7cm}{0.8032} & \parbox{7cm}{0.7505}  & \parbox{7cm}{0.7760}\\
\hline
\parbox{10cm}{BERT - Chinese Model}   & \parbox{7cm}{XXX}  & \parbox{7cm}{0.7676} & \parbox{7cm}{0.7460} & \parbox{7cm}{0.8114}  & \parbox{7cm}{0.7774}\\
\hline
\parbox{10cm}{BERT w/Whole Word}  & \parbox{15cm}{XXX} & \parbox{7cm}{0.8194} & \parbox{7cm}{0.8809} & \parbox{7cm}{0.7386}  & \parbox{7cm}{0.8035}\\
\hline
\parbox{10cm}{BERT w/Whole Word ANTLR}  & \parbox{15cm}{bert-large-uncased-whole-word-masking, ANTLR preprocessing remove whitespaces and comments} & \parbox{7cm}{0.8195} & \parbox{7cm}{0.8041} & \parbox{7cm}{0.8449}  & \parbox{7cm}{0.8240}\\
\hline
\parbox{10cm}{CodeBERT}  & \parbox{15cm}{XXX} & \parbox{7cm}{0.7845} & \parbox{7cm}{0.8144} & \parbox{7cm}{0.7367}   & \parbox{7cm}{0.7737}\\
\hline
\parbox{10cm}{CodeBERT ANTLR lower case}  & \parbox{15cm}{codebert-base, ANTLR preprocessing remove whitespaces and comments, lower case tokens} & \parbox{7cm}{0.8675} & \parbox{7cm}{0.8424} & \parbox{7cm}{0.8940}   & \parbox{7cm}{0.8611}\\
\hline
\parbox{10cm}{BigBird 1K}  & \parbox{15cm}{XXX}  & \parbox{7cm}{0.7749} & \parbox{7cm}{0.8347} & \parbox{7cm}{0.6855}  & \parbox{7cm}{0.7527}\\
\hline
\parbox{10cm}{BigBird 2K}  & \parbox{15cm}{XXX}  & \parbox{7cm}{0.7653} & \parbox{7cm}{0.7547} & \parbox{7cm}{0.7863}  & \parbox{7cm}{0.7701}\\
\hline
\parbox{10cm}{BigBird 3K}  & \parbox{15cm}{XXX}  & \parbox{7cm}{0.7016} & \parbox{7cm}{0.8609} & \parbox{7cm}{0.4809}  & \parbox{7cm}{0.6171}\\
\hline
\parbox{10cm}{BigBird 4K}  & \parbox{15cm}{XXX} & \parbox{7cm}{0.7057} & \parbox{7cm}{0.9159} & \parbox{7cm}{0.4529}  & \parbox{7cm}{0.6061}\\
\hline
\parbox{10cm}{Longformer 4K}  & \parbox{15cm}{XXX} & \parbox{7cm}{0.7140} & \parbox{7cm}{0.8322} & \parbox{7cm}{0.5361}  & \parbox{7cm}{0.6521}\\
\midrule
\addlinespace[0.5em]

\end{tabular}%
}
\end{table}
\\)

$$
