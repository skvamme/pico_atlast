#!/bin/sh
sed 's/$/ \\n\\/' $1 > forth.h
sed -i 's/"/\\"/g' forth.h
sed -i '1ichar FORTH[5000] = \" ( ATLAST forth ) \\n\\' forth.h
sed -i '$ago\\n\";' forth.h
