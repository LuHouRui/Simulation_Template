#!/bin/bash
node_num=$1
request_num=$2
area=$3
date=$4
mkdir result
mkdir result/$4
mkdir result/$4/$3area
mkdir result/$4/$3area/$2requests

DIR="./topo/$4/$3area/$2requests/$1_$2"

for j in `seq 100`
do
  echo run $j
  echo $DIR/$j
  ./Simple_Method.out $DIR/$j/Node_Topolist.txt $DIR/$j/Edge_Topolist.txt $DIR/$j/Request_Topolist.txt $DIR/$j/setup.txt >> ./result/$4/$3area/$2requests/$1_$2.txt
  wait
done

./Average.out ./result/$4/$3area/$2requests/$1_$2.txt >> ./result/$4/$3area/$2requests/$1_$2.txt