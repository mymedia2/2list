#!/usr/bin/python
# coding: utf-8
from __future__ import print_function
import re, sys

def invalid(*args):
	print("{0}:{1}: предупреждение: неизвестная команда '{2}'".format(
		readme["file"].name, readme["line"], args[0]), file=sys.stderr)

def get_code():
	line = readme["file"].readline()
	if line: readme["line"] += 1
	if line.lower() == "```c\n":
		result = ""
		while True:
			line = readme["file"].readline()
			if not line or line == "```\n": break
			readme["line"] += 1
			result += line
		return result

def get_line_block():
	line = readme["file"].readline()
	if line: readme["line"] += 1
	return re.search("`([^`]+)`", line).groups()[0]

def run():
	print("{")
	print(get_code())
	print("}")

def pass_pre():
	"""Пропускаем следующий блок кода"""
	get_code()

def code():
	print(get_code())
	print(r"""{
		lst_iter_t p;
		for (p = lst_iter_first(L); !lst_iter_is_null(p); p = lst_iter_next(p)) {
			printf("%ld ", lst_iter_deref(p));
		}
		printf("\n");
	}
	""")
	print("lst_free(L); }")

def before():
	print("{ list_t L; lst_new(&L);")
	for elem in get_line_block().split():
		print("lst_append(L, {0});".format(elem))

def after():
	for elem in get_line_block().split():
		print("lst_append(L, {0});".format(elem))

def app():
	global readme

	# выкусывает строчки вида "<!-- doctest: (.*) -->"
	wild_expr = re.compile(r"\s*<!--\s*doctest\s*:(.+)\s*-->\s*")

	readme = { "file": open(sys.argv[1]), "line": 0 }

	print("""
	#include <stdio.h>
	#include <stdlib.h>
	#include "list.h"
	int main() {
	""")

	while True:
		text = readme["file"].readline()
		if not text: break
		readme["line"] += 1

		command = re.match(wild_expr, text)
		if command:
			cmd = [ l.strip() for l in command.groups() ]
			if cmd[0] in func: func[cmd[0]](*cmd[1:])
			else: invalid(*cmd)
	
	print("return 0; }")

func = { "run": run, "pass": pass_pre, "code": code, "before": before }

if __name__ == "__main__": app()
