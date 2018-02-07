#!/usr/bin/env bash
set -e

printf "Installing\n"
mkdir -vp /usr/local/include/ob
cp -vr ./include/parg.hh /usr/local/include/ob/
printf "Success\n"
