#!/bin/bash
### 这个脚本用来生成一个随机字符串文件

###字符串最大长度
MaxLength=10
###生成NUM个字符串
NUM=100000

Alpha=(`echo {a..z}`)

for (( i = 0; i < $NUM; i++ ))
do
  StringLength=$(($RANDOM % $MaxLength + 1))
  for (( j = 1; j <= $StringLength; j++ ))
  do
     index=$(($RANDOM % 26))
     printf ${Alpha[$index]}
  done
  echo
done
