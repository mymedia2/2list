#!/usr/bin/python
# coding: utf-8
from __future__ import print_function
import re, sys

def invalid(*args):
	print("{0}:{1}: предупреждение: неизвестная команда '{2}'".format(
		readme.name, readme.line, args[0]), file=sys.stderr)

def get_code():
	line = readme.get()
	if line.lower().strip() == "```c":
		result = ""
		while True:
			line = readme.get()
			if not line or line.strip() == "```": break
			result += line
		return result

def get_line_block():
	line = readme.get()
	return re.search("`([^`]+)`", line).groups()[0]

def run():
	print("{")
	print('#line {0} "{1}"'.format(readme.line+2, readme.name))
	print(get_code())
	print("}")

def pass_pre():
	"""Пропускаем следующий блок кода"""
	get_code()

def code():
	print('#line {0} "{1}"'.format(readme.line+2, readme.name))
	print(get_code())
	print(r"""
		#line 39 "doctest.py"
		print_list(L);
		lst_free(L); }
	""")

def assert_pre():
	print('#line {0} "{1}"'.format(readme.line+2, readme.name))
	for line in get_code().strip().split("\n"):
		line = line.replace(";", "")
		print(r"""printf(({0}) ? "true " : "false ");""".format(line))
		print("true ", end="", file=result)
	print(r"""printf("\n");""")
	print(file=result)
	print("lst_free(L); }")

def before():
	print('#line {0} "{1}"'.format(readme.line+1, readme.name))
	print("{ list_t* L = lst_new(0);")
	for elem in get_line_block().split():
		print('#line {0} "{1}"'.format(readme.line, readme.name))
		print("lst_append(L, {0});".format(elem))

def after():
	print(get_line_block(), file=result)

class ProxyFile(object):
	name = ""
	line = 0
	def __init__(self, name):
		self.__file = open(name)
		self.name = name
	def get(self):
		text = self.__file.readline()
		if not text: raise StopIteration
		self.line += 1
		return text

def app():
	global readme, result

	# выкусывает строчки вида "<!-- doctest: (.*) -->"
	wild_expr = re.compile(r"<!--\s*doctest\s*:(.+)\s*-->")

	readme = ProxyFile(sys.argv[1])
	result = open(sys.argv[2], "w")

	print(r"""
		#line 86 "doctest.py"
		#include <stdio.h>
		#include <stdlib.h>
		#include "list.h"
		#define print_list(l) do {                                                    \
			lst_iter_t p;                                                             \
			for (p = lst_iter_first(l); !lst_iter_is_null(p); p = lst_iter_next(p)) { \
				printf("%ld ", lst_iter_deref(p));                                    \
			}                                                                         \
			printf("\n");                                                             \
		} while(0)
		int main() {
	""")

	while True:
		try: text = readme.get()
		except StopIteration: break

		command = re.match(wild_expr, text.strip())
		if command:
			cmd = [ l.strip() for l in command.groups() ]
			if cmd[0] in func: func[cmd[0]](*cmd[1:])
			else: invalid(*cmd)
	
	print('#line {0} "{1}"'.format(readme.line, readme.name))
	print("return 0; }")

func = { "run": run,
         "pass": pass_pre,
         "code": code,
         "before": before,
         "after": after,
		 "assert": assert_pre,
       }

if __name__ == "__main__": app()
