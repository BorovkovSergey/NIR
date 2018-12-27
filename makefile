all:
	g++  main.cpp \
	libs/files_working/*  \
	libs/log_shell/* \
	libs/parser/* \
	libs/sentence/* \
	libs/synthesis/* \
	libs/words/* \
	libs/misc.* \
	-o hello
