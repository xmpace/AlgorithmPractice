#!/bin/bash
#
#
#
#
#
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
echo -e "Hello World! \a \n"

read -p "请输入有多少个数字？" number
read -p "请输入你的名字？" yourname
echo "The nubmer is: $number.\n你的名字是:$yourname!"
