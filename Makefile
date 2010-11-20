all: spec

spec: tester.c regex_spec.c
	gcc -g -Wall -o $@ tester.c regex_spec.c -lcspec
