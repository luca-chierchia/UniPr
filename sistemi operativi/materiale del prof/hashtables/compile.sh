#!/bin/sh

gcc -W -Wall -g main.c ht.c -Wno-unused-parameter -Wno-unused-function $@
