#!/bin/sh
sed 's/\\/\\\\/g' $1 > blk.atl
sed -i 's/"/\\"/g' blk.atl
sed -i 's/^\(.*\)$/"\1"/' blk.atl

