import os
import math
from json import dumps, loads

import numpy as np
import pandas as pd
from scipy.spatial.distance import cosine

import antlr4
from antlr4 import *
import JavaParser
import JavaLexer

from rkr_gst_helpers.rkr_gst import rkr_gst
from rkr_gst_helpers.manage_tokens import ManageTokens

def main():
	# test()
	# process_tokens()
	process_rkrgst()
	# process_vsm()
	# process_lm()


def test():
	with open("test.txt", "r") as f:
		code = f.read()
	lexer = JavaLexer.JavaLexer(antlr4.InputStream(code))
	stream = antlr4.CommonTokenStream(lexer)
	stream.fill()
	# Print tokens as text (EOF is stripped from the end)
	tmp = [token.text for token in stream.tokens][:-1]
	print(" ".join(tmp))


def process_tokens():
	for root, dirs, fs in os.walk("IR-Plag-Dataset"):
		for f in fs:
			if f.endswith(".java"):
				tokens_of = "{}/{}".format(root, f.replace(".java", "_tokens.json"))
				indexes_of = "{}/{}".format(root, f.replace(".java", "_indexes.json"))
				

				with open("{}/{}".format(root, f), "r") as f:
					code = f.read()
				lexer = JavaLexer.JavaLexer(antlr4.InputStream(code))
				stream = antlr4.CommonTokenStream(lexer)
				stream.fill()

				tokens = [token.text for token in stream.tokens][:-1]
				with open(tokens_of, "w") as of:
					# save tokens as text (EOF is stripped from the end)
					of.write(dumps(tokens))

				tokens_dict = dict()
				for t in tokens:
					if t not in tokens_dict:
						tokens_dict[t] = 0
					tokens_dict[t] += 1
				# print(len(tokens_dict))
				# import nltk
				# input(len(nltk.probability.FreqDist(tokens).most_common()))
				with open(indexes_of, "w") as of:
					# save token indexes
					of.write(dumps(tokens_dict))


def calculate_avg_precision(ranks, n_relevant_o):
	numerator = 0
	relevant_retrieved = 0
	for rank, (score, fname) in enumerate(ranks, 1):
		is_p = "non-plagiarized" not in fname
		relevant_retrieved += is_p
		if is_p:
			prec = relevant_retrieved/rank
			numerator += prec

	return numerator/n_relevant_o


def process_rkrgst():
	cutoff = 0.5
	tp = []
	tn = []
	fp = []
	fn = []
	layers_dict = dict()
	for layer in range(1, 7):
		layers_dict[layer] = {
			"tp": [],
			"tn": [],
			"fp": [],
			"fn": [],
			"map_check": [],
			"ranks": [],
			"n_plagiarized_files": 0
		}
	map_check = []
	for i in range(1, 8):
		case = str(i)
		print("\n\nCheck {}".format(case))
		orig = "IR-Plag-Dataset/case-0{}/original/T{}_tokens.json".format(case, case)
		with open(orig, "r") as f:
			orig_tokens = loads(f.read())
		mantok_orig = ManageTokens(orig_tokens)

		ranks = []
		np_ranks = []
		print("\nNon-plagiarized")
		nonp_check = []
		for root, dirs, files in os.walk("IR-Plag-Dataset/case-0{}/non-plagiarized".format(case)):
			for f in files:
				if f.endswith("tokens.json"):
					nonp = "{}/{}".format(root, f)

					with open(nonp, "r") as f:
						nonp_tokens = loads(f.read())
					mantok_nonp = ManageTokens(nonp_tokens)
					print(nonp)
					result = _process_rkrgst_helper(mantok_orig, mantok_nonp)
					nonp_check.append(result)
					if result <= 0.5:
						fp.append(nonp)
					else:
						tn.append(nonp)

					rank = (result, nonp)
					ranks.append(rank)
					np_ranks.append(rank)

		print("\nPlagiarized")
		n_plagiarized_files = 0
		p_check = []
		for root, dirs, files in os.walk("IR-Plag-Dataset/case-0{}/plagiarized".format(case)):
			for f in files:
				if f.endswith("tokens.json"):
					n_plagiarized_files += 1
					p = "{}/{}".format(root, f)

					with open(p, "r") as f:
						p_tokens = loads(f.read())
					mantok_p = ManageTokens(p_tokens)
					print(p)
					result = _process_rkrgst_helper(mantok_orig, mantok_p)
					p_check.append(result)

					layer = int(p.split("/")[3][-1])
					current_tp = layers_dict[layer]["tp"]
					current_fn = layers_dict[layer]["fn"]
					if result <= 0.5:
						current_tp.append(p)
					else:
						current_fn.append(p)

					rank = (result, p)
					ranks.append(rank)
					current_ranks = layers_dict[layer]["ranks"]
					current_ranks.append(rank)
					layers_dict[layer]["n_plagiarized_files"] += 1

		ranks = sorted(ranks)
		print(ranks)
		avg_precision = calculate_avg_precision(ranks, n_plagiarized_files)
		print(avg_precision)
		map_check.append(avg_precision)

		for layer in range(1, 7):
			current_ranks = layers_dict[layer]["ranks"]
			current_ranks = sorted(current_ranks + np_ranks)
			current_n_plagiarized_files = layers_dict[layer]["n_plagiarized_files"]
			# print(current_ranks)
			# print(current_n_plagiarized_files)
			current_avg_precision = calculate_avg_precision(current_ranks, current_n_plagiarized_files)
			# input(current_avg_precision)
			current_map_check = layers_dict[layer]["map_check"]
			current_map_check.append(current_avg_precision)
			# input(layers_dict[layer]["map_check"])

	print("\n\nOverall")
	print(map_check)
	print(np.mean(map_check))
	print("\nBy Layer")
	for layer in range(1, 7):
		print(np.mean(layers_dict[layer]["map_check"]))



	# print("\n")
	# print(tp)
	# print(tn)
	# print(fp)
	# print(fn)
	# print(len(tp), len(tn), len(fp), len(fn))
	# for i in range(1, 7):
	# 	print("\nL{} precision recall".format(i))
	# 	current_tp = len(layers_dict[i]["tp"])
	# 	current_fn = len(layers_dict[i]["fn"])
	# 	print(current_tp, current_tp/(current_tp + len(fp)), current_tp/(current_tp + current_fn))
		


	# nonp = "IR-Plag-Dataset/case-01/non-plagiarized/01/T01_tokens.json"
	# p = "IR-Plag-Dataset/case-01/plagiarized/L1/01/L1_tokens.json"

	# with open(orig, "r") as f:
	# 	orig_tokens = loads(f.read())
	# with open(nonp, "r") as f:
	# 	nonp_tokens = loads(f.read())
	# with open(p, "r") as f:
	# 	p_tokens = loads(f.read())

	# mantok_orig = ManageTokens(orig_tokens)
	# mantok_nonp = ManageTokens(nonp_tokens)
	# mantok_p = ManageTokens(p_tokens)
	
	# _process_rkrgst_helper(mantok_orig, mantok_nonp)
	# _process_rkrgst_helper(mantok_orig, mantok_p)
	
def _process_rkrgst_helper(mantok_orig, mantok_other):
	mininum_match_length = 2
	initial_search_size = 8
	rkr_gst(mantok_orig, mantok_other, mininum_match_length, initial_search_size)

	tiles = {}
	i = 0
	for token in mantok_orig.is_marked:
		if token:
			i += 1
		elif not token and i > 0:
			if i in tiles:
				tiles[i] += 1
			else:
				tiles[i] = 1
			i = 0

	normalization = (mantok_orig.length_of_tokens + mantok_other.length_of_tokens)/2.0
	similarity = 0
	for tile_length, total in tiles.items():
		similarity += total*tile_length*math.log(tile_length + 1)

	normalized_similarity = similarity/normalization

	print(normalized_similarity)
	return normalized_similarity


def process_vsm():
	check = dict()
	for root, dirs, files in os.walk("IR-Plag-Dataset"):
		print(root)
		print(dirs)
		print(files)
		for f in files:
			if f.endswith("indexes.json"):
				with open("{}/{}".format(root, f)) as f:
					tmp = loads(f.read())
				for k, v in tmp.items():
					if k not in check:
						check[k] = 0
					check[k] += v
	print(check)
	# for k in check.keys():
	# 	check[k] = 0
	with open("unigram_indexes.json", "w") as of:
		of.write(dumps(check))
	return


	# for i in range(1, 8):
	# 	case = str(i)
	# 	orig = "IR-Plag-Dataset/case-0{}/original/T{}_indexes.json".format(case, case)

	# 	print("\nNon-plagiarized")
	# 	nonp_check = []
	# 	for root, dirs, files in os.walk("IR-Plag-Dataset/case-0{}/non-plagiarized".format(case)):
	# 		for f in files:
	# 			if f.endswith("indexes.json"):
	# 				nonp = "{}/{}".format(root, f)
	# 				# print(nonp)
	# 				nonp_check.append(_process_vsm_helper(orig, nonp))

	# 	print("\nPlagiarized")
	# 	p_check = []
	# 	for root, dirs, files in os.walk("IR-Plag-Dataset/case-0{}/plagiarized".format(case)):
	# 		for f in files:
	# 			if f.endswith("indexes.json"):
	# 				p = "{}/{}".format(root, f)
	# 				# print(p)
	# 				p_check.append(_process_vsm_helper(orig, p))

	# 	print(nonp_check)
	# 	print(p_check)
	# 	break

	# 	print(np.mean(nonp_check), np.mean(p_check))

def _process_vsm_helper(orig, other):
	# with open(orig, "r") as f:
	# 	orig_indexes = loads(f.read())
	# with open(other, "r") as f:
	# 	other_indexes = loads(f.read())
	# orig_keys = set(orig_indexes.keys())
	# other_keys = set(other_indexes.keys())
	# all_keys = orig_keys.union(other_keys)
	# missing_orig_keys = all_keys.difference(orig_keys)
	# missing_other_keys = all_keys.difference(other_keys)
	# missing_orig = dict([(i, 0) for i in missing_orig_keys])
	# missing_other = dict([(i, 0) for i in missing_other_keys])
	# orig_indexes.update(missing_orig)
	# other_indexes.update(missing_other)

	with open(orig, "r") as f:
		tmp_orig_indexes = loads(f.read())
	with open(other, "r") as f:
		tmp_other_indexes = loads(f.read())
	with open("unigram_indexes.json", "r") as f:
		orig_indexes = loads(f.read())
		orig_indexes.update(tmp_orig_indexes)
	with open("unigram_indexes.json", "r") as f:
		other_indexes = loads(f.read())
		other_indexes.update(tmp_other_indexes)

	orig_vec = np.array([i[1] for i in sorted(orig_indexes.items())])
	other_vec = np.array([i[1] for i in sorted(other_indexes.items())])
	# print(orig_vec)
	# print(other_vec)
	# print(orig_vec.shape, other_vec.shape)
	cos_sim = _calc_cos_sim(orig_vec, other_vec)
	# input(cos_sim)
	return cos_sim

def _calc_cos_sim(a, b):
	print(np.dot(a, b))
	print(np.linalg.norm(a))
	print(np.linalg.norm(b))
	return np.dot(a, b)/(np.linalg.norm(a) * np.linalg.norm(b))	


def process_lm():
	with open("unigram_indexes.json", "r") as f:
		collection_indexes = loads(f.read())

	for i in range(1, 8):
		case = str(i)
		orig = "IR-Plag-Dataset/case-0{}/original/T{}_indexes.json".format(case, case)
		


		print("\nNon-plagiarized")
		nonp_check = []
		for root, dirs, files in os.walk("IR-Plag-Dataset/case-0{}/non-plagiarized".format(case)):
			for f in files:
				if f.endswith("indexes.json"):
					nonp = "{}/{}".format(root, f)
					print(nonp)
					result = _process_lm_helper(orig, nonp, collection_indexes)

					nonp_check.append(result)

		print("\nPlagiarized")
		p_check = []
		for root, dirs, files in os.walk("IR-Plag-Dataset/case-0{}/plagiarized".format(case)):
			for f in files:
				if f.endswith("indexes.json"):
					p = "{}/{}".format(root, f)
					print(p)
					result = _process_lm_helper(orig, p, collection_indexes)

					p_check.append(result)
		
		print(nonp_check)
		print(p_check)
		print(np.mean(nonp_check), np.mean(p_check))
		input(i)

def _process_lm_helper(orig, other, collection_indexes):
	with open(orig, "r") as f:
		orig_indexes = loads(f.read())
	with open(other, "r") as f:
		other_indexes = loads(f.read())

	results = []
	for tok in orig_indexes.keys():
		results.append(np.log(0.3 * other_indexes.get(tok, 0)/len(other_indexes) + 0.7 * collection_indexes[tok]/len(collection_indexes)))

	return sum(results)

if __name__ == '__main__':
	main()
