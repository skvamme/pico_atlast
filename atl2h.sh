#!/bin/sh
sed 's/$/ \\n\\/' $1 > forth.h
sed -i 's/"/\\"/g' forth.h
sed -i '1i#define ATLAST \" ( ATLAST forth ) \\n\\' forth.h
sed -i '$ago\\n\"' forth.h
