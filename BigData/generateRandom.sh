#!/bin/bash
# 用来生成一个随机数大文件
# 文件名为data

num=100000

if [ -e data ]
then
	rm data
fi

i=0
while [ $i -lt $num ]
do
	echo $RANDOM >> data
	i=$(($i+1));
done
