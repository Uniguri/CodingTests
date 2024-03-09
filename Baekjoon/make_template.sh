#!/bin/bash

if [ $# != 1 ]; then
  echo "Usage $0 [problem number]"
  exit
elif ! [[ $1 =~ ^[0-9]+$ ]]; then
  echo "problem number must be number"
  exit
fi

prob_num=$1
echo "Make $prob_num"
mkdir $prob_num
cp ./solution.cc $prob_num
cp ./testcase.json $prob_num