#!/bin/bash

if [ "$1" == "start" ]
  then
  	sudo service ntp start
	echo "123" >> /dev/stdin>/dev/null
elif [ "$1" == "stop" ]
  then
	sudo service ntp stop
  	echo "123" >> /dev/stdin>/dev/null
  else
  echo "input error."
fi
