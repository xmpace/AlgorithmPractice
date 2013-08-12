#!/bin/bash
#让使用者输入一个档名,我们判断:
#1. 这个档案是否存在,若不存在则给予一个『Filename does not exist』的讯息,并中断程序;
#2. 若这个档案存在,则判断他是个档案或目录,结果输出『Filename is regular file』 
#『Filenameis directory』
#3.判断一下,执行者的身份对这个档案或目录所拥有的权限,并输出权限数据!

echo "Please Input the filename with path: "
read filename

test -e $filename || (echo "$filename does not exist" && exit 0)
(test -f $filename && echo "$filename is regular file") || (test -d $filename && echo "$filename is a drecotry")

test -r $filename && perm="readable"
test -w $filename && perm="$perm, writable"
test -x $filename && perm="$perm, executable"

echo "$filename is $perm"

