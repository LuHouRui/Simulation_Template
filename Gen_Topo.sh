#!/bin/bash
node_num=$1
request_num=$2
area=$3
date=$4
mkdir topo
mkdir ./topo/$4
mkdir ./topo/$4/$3area/
mkdir ./topo/$4/$3area/$2requests
mkdir ./topo/$4/$3area/$2requests/$1_$2
for j in `seq 100`
do
  mkdir ./topo/$4/$3area/$2requests/$1_$2/$j
  ./Topo.out $1 $2 $3
  sleep 1.5s
  python3 Draw_topo_figure.py
  mv ./Node_Topolist.txt ./topo/$4/$3area/$2requests/$1_$2/$j
  mv ./Edge_Topolist.txt ./topo/$4/$3area/$2requests/$1_$2/$j
  mv ./Request_Topolist.txt ./topo/$4/$3area/$2requests/$1_$2/$j
  mv ./topo_figure.png ./topo/$4/$3area/$2requests/$1_$2/$j
  cp ./setup.txt ./topo/$4/$3area/$2requests/$1_$2/$j
  echo run $j
done
