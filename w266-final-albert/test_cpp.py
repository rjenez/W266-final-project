import os
import math
from json import dumps, loads

import nltk
import numpy as np
import pandas as pd
from scipy.spatial.distance import cosine

import antlr4
from antlr4 import *
import CPP14Parser
import CPP14Lexer

from rkr_gst_helpers.rkr_gst import rkr_gst
from rkr_gst_helpers.manage_tokens import ManageTokens

def main():
    # test()
    process_tokens()
    # process_vsm()
    process_lm()


def test():
    with open("test_cpp.c", "r") as f:
        code = f.read()
    lexer = CPP14Lexer.CPP14Lexer(antlr4.InputStream(code))
    stream = antlr4.CommonTokenStream(lexer)
    stream.fill()
    # Print tokens as text (EOF is stripped from the end)
    tmp = [token.text for token in stream.tokens][:-1]
    print(" ".join(tmp))


def process_tokens():
    root = "../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z1/Z1"
    for f in os.listdir(root):
        if f.endswith(".c"):
            tokens_of = "{}/{}".format(root, f.replace(".c", "_tokens_3.json"))
            indexes_of = "{}/{}".format(root, f.replace(".c", "_indexes_3.json"))
            

            with open("{}/{}".format(root, f), "r") as f:
                code = f.read()
            lexer = CPP14Lexer.CPP14Lexer(antlr4.InputStream(code))
            stream = antlr4.CommonTokenStream(lexer)
            stream.fill()

            tokens = [token.text for token in stream.tokens][:-1]
            tokens = list(nltk.trigrams(tokens))
            with open(tokens_of, "w") as of:
                # save tokens as text (EOF is stripped from the end)
                of.write(dumps(tokens))

            tokens_dict = dict()
            for t in tokens:
                t = "{},{},{}".format(t[0], t[1], t[2])
                if t not in tokens_dict:
                    tokens_dict[t] = 0
                tokens_dict[t] += 1
            # print(len(tokens_dict))
            # import nltk
            # input(len(nltk.probability.FreqDist(tokens).most_common()))
            with open(indexes_of, "w") as of:
                # save token indexes
                of.write(dumps(tokens_dict))


def process_vsm():
    _preprocess_vsm()
    root = "../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z1/Z1"
    outf = "cpp_vsm_result_ranks_2.json"
    if os.path.exists(outf):
        with open(outf, "r") as f:
            result_ranks = loads(f.read())
    else:
        token_files = ["{}/{}".format(root, f) for f in os.listdir(root) if f.endswith("_indexes_2.json")]
        results = dict()
        result_ranks = dict()
        for current_f in token_files:
            results[current_f] = dict()
            print("")
            print(current_f)
            for compare_f in token_files:
                # print("")
                # print(current_f, compare_f)
                if current_f == compare_f:
                    continue
                cos_sim = _process_vsm_helper(current_f, compare_f)
                results[current_f][compare_f] = cos_sim

            result_ranks[current_f] = sorted([(v, k) for k, v in results[current_f].items()], reverse=True)

        with open(outf.replace("_ranks", "s"), "w") as of:
            of.write(dumps(results))
        with open(outf, "w") as of:
            of.write(dumps(result_ranks))

    with open("A2016Z1Z1.txt", "r") as f:
        plagiarised_students = loads(f.read())

    aps = []
    for current_p in plagiarised_students:
        n_plag = len(current_p) - 1
        for current_original in current_p:
            current_ranks = [i[1].split("/")[-1].split("_")[0] for i in result_ranks["{}/{}_indexes_2.json".format(root, current_original)]]
            numerator = 0
            current_rel_retreived = 0
            current_plag_ranks = []
            for current_other in current_p:
                if current_original == current_other:
                    continue
                current_plag_ranks.append(current_ranks.index(current_other) + 1)

            for rank in sorted(current_plag_ranks):
                current_rel_retreived += 1
                prec = current_rel_retreived/rank
                numerator += prec
            aps.append(numerator/n_plag)

    print(aps)
    print(np.mean(aps))

def _preprocess_vsm():
    root = "../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z1/Z1"
    outf = "{}/trigram_indexes.json".format(root)
    # if not os.path.exists(outf):
    check = dict()
    for f in os.listdir(root):
        if f.endswith("indexes_3.json") and "gram" not in f:
            with open("{}/{}".format(root, f), "r") as f:
                tmp = loads(f.read())
            for k, v in tmp.items():
                if k not in check:
                    check[k] = 0
                check[k] += v

    with open(outf, "w") as of:
        of.write(dumps(check))

    for k in check.keys():
        check[k] = 0
    with open(outf.replace(".json", "_zeroed.json"), "w") as of:
        of.write(dumps(check))

def _process_vsm_helper(orig, other):
    with open(orig, "r") as f:
        tmp_orig_indexes = loads(f.read())
    with open(other, "r") as f:
        tmp_other_indexes = loads(f.read())
    with open("../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z1/Z1/bigram_indexes.json", "r") as f:
        orig_indexes = loads(f.read())
        # print(len(orig_indexes))
        # print(len(tmp_orig_indexes))
        # print(orig_indexes)
        # print(tmp_orig_indexes)
        orig_indexes.update(tmp_orig_indexes)
        # print(len(orig_indexes))

    with open("../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z1/Z1/bigram_indexes.json", "r") as f:
        other_indexes = loads(f.read())
        # print(len(other_indexes))
        # print(len(tmp_other_indexes))
        other_indexes.update(tmp_other_indexes)
        # print(len(other_indexes))

    orig_vec = np.array([i[1] for i in sorted(orig_indexes.items())])
    other_vec = np.array([i[1] for i in sorted(other_indexes.items())])
    # print(orig_vec)
    # print(other_vec)
    # print(orig_vec.shape, other_vec.shape)
    cos_sim = _calc_cos_sim(orig_vec, other_vec)
    # input(cos_sim)
    return cos_sim

def _calc_cos_sim(a, b):
    # print(np.dot(a, b))
    # print(np.linalg.norm(a))
    # print(np.linalg.norm(b))
    return np.dot(a, b)/(np.linalg.norm(a) * np.linalg.norm(b)) 


def process_lm():
    _preprocess_vsm()
    root = "../data/programming-homework-dataset-plagiarism-detection/src/A2016/Z1/Z1"
    with open("{}/trigram_indexes.json".format(root), "r") as f:
    # with open("bigram_indexes.json", "r") as f:
        collection_indexes = loads(f.read())

    outf = "cpp_lm_result_ranks_3.json"
    if os.path.exists(outf):
        with open(outf, "r") as f:
            result_ranks = loads(f.read())
    else:
        token_files = ["{}/{}".format(root, f) for f in os.listdir(root) if f.endswith("_indexes_3.json")]
        results = dict()
        result_ranks = dict()
        for current_f in token_files:
            results[current_f] = dict()
            print("")
            print(current_f)
            for compare_f in token_files:
                # print("")
                # print(current_f, compare_f)
                if current_f == compare_f:
                    continue
                cos_sim = _process_lm_helper(current_f, compare_f, collection_indexes)
                results[current_f][compare_f] = cos_sim

            result_ranks[current_f] = sorted([(v, k) for k, v in results[current_f].items()], reverse=True)

        with open(outf.replace("_ranks", "s"), "w") as of:
            of.write(dumps(results))
        with open(outf, "w") as of:
            of.write(dumps(result_ranks))

    with open("A2016Z1Z1.txt", "r") as f:
        plagiarised_students = loads(f.read())

    aps = []
    for current_p in plagiarised_students:
        n_plag = len(current_p) - 1
        for current_original in current_p:
            current_ranks = [i[1].split("/")[-1].split("_")[0] for i in result_ranks["{}/{}_indexes_3.json".format(root, current_original)]]
            numerator = 0
            current_rel_retreived = 0
            current_plag_ranks = []
            for current_other in current_p:
                if current_original == current_other:
                    continue
                current_plag_ranks.append(current_ranks.index(current_other) + 1)

            for rank in sorted(current_plag_ranks):
                current_rel_retreived += 1
                prec = current_rel_retreived/rank
                numerator += prec
            aps.append(numerator/n_plag)

    print(aps)
    print(np.mean(aps))

def _process_lm_helper(orig, other, collection_indexes):
    with open(orig, "r") as f:
        orig_indexes = loads(f.read())
    with open(other, "r") as f:
        other_indexes = loads(f.read())

    results = []
    other_denom = len(orig_indexes)
    collection_denom = len(collection_indexes)
    # other_denom = sum(other_indexes.values())
    # collection_denom = sum(collection_indexes.values())
    for tok in orig_indexes.keys():
        results.append(np.log(0.3 * other_indexes.get(tok, 0)/other_denom + 0.7 * collection_indexes[tok]/collection_denom))

    return sum(results)


if __name__ == "__main__":
    main()