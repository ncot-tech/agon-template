#!/bin/sh

newname="${1%.*}"

convert $1 -colors 64 -posterize 4 ${newname}_64.png
