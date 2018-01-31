#!/usr/bin/env bash
set -e

# source environment variables
source ./env.sh

UNINSTALL_TYPE="Debug"

if [[ $# > 0 ]]; then
  if [[ $1 == "-d" ]]; then
    UNINSTALL_TYPE="Debug"
  elif [[ $1 == "-r" ]]; then
    UNINSTALL_TYPE="Release"
  fi
fi

if [[ ${UNINSTALL_TYPE} == "Debug" ]]; then
  printf "\nUninstalling Debug ${APP}\n"
  rm -vf /usr/include/ob/parg.hh
  rm -vf /usr/include/ob/term.hh
  rm -vf /usr/include/ob/widthstream.hh

elif [[ ${UNINSTALL_TYPE} == "Release" ]]; then
  printf "\nUninstalling Release ${APP}\n"
  rm -vf /usr/include/ob/parg.hh
  rm -vf /usr/include/ob/term.hh
  rm -vf /usr/include/ob/widthstream.hh
fi
