#!/usr/bin/env bash
set -e

# source environment variables
source ./env.sh

INSTALL_TYPE="Debug"

if [[ $# > 0 ]]; then
  if [[ $1 == "-d" ]]; then
    INSTALL_TYPE="Debug"
  elif [[ $1 == "-r" ]]; then
    INSTALL_TYPE="Release"
  fi
fi

if [[ ${INSTALL_TYPE} == "Debug" ]]; then
  printf "\nInstalling Debug ${APP}\n"
  mkdir -vp /usr/include/ob
  cp -vr ./include/. /usr/include/ob/

elif [[ ${INSTALL_TYPE} == "Release" ]]; then
  printf "\nInstalling Release ${APP}\n"
  mkdir -vp /usr/include/ob
  cp -vr ./include/. /usr/include/ob/
fi
