#!/bin/bash
set -e

SRC=$1
DEST=$2

mkdir /tmp/build-data

rsync -rv --exclude=.git --exclude=.tmp --exclude=textures --exclude=*.tga \
     --exclude=*.jpg --exclude=*.map --exclude=*.qh --exclude=*.qc \
     --exclude=*.ogg --exclude=*.wav --exclude=*.shader --exclude=*.mp3  \
     --exclude=*.inc --exclude=*.ase --exclude=.gitignore --exclude=.gitattributes \
     --exclude=*.yml --exclude=.tx --exclude=Makefile --exclude=*.sp2 --exclude=*.mid \
     --exclude=README.md --exclude=cmake --exclude=CMakeLists.txt --exclude=*.sh  \
     --exclude=Dockerfile --exclude=docker \
     --exclude=*.sh --exclude=*.sw[op] --exclude=*.dem "$1" /tmp/build-data


pushd /tmp/build-data
7za a -tzip -mx=9  "/var/tmp/artifacts/xonotic-data-$(date +%Y%m%d).pk3"  ./
popd
