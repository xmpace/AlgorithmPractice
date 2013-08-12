#!/bin/bash

echo "Input two numbers, I will multip them!"
read -p "first number: " first
read -p "second number: " second
var=$(($second*$first))
echo "The result of $first*$second is $var"