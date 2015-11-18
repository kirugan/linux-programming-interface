#!/bin/sh
# This helper generates two files one with holes, another without holes
# see http://stackoverflow.com/questions/5315428/how-to-create-a-file-with-file-holes

#dd if=/dev/urandom bs=4096 count=2 of=fwh; # fwh = file with holes
dd if=/dev/urandom seek=7 bs=4096 count=2 of=fwh;


dd if=/dev/zero bs=4096 count=9 of=fwnh; # fwnh = file with no holes