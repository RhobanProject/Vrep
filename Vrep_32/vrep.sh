#!/bin/sh

dirname=`dirname $0`

if [ $dirname != "." ]; then
	echo "*****************************************"
	echo "*****************************************"
	echo "Please launch V-REP from a terminal, from"
	echo "within its folder with ./vrep.sh         "
	echo "*****************************************"
	echo "*****************************************"
	sleep 5s
else
	appname=`basename $0 | sed s,\.sh$,,`

	tmp="${dirname#?}"

	if [ "${dirname%$tmp}" != "/" ]; then
		dirname=$PWD/$dirname
	fi
	LD_LIBRARY_PATH=$dirname
	export LD_LIBRARY_PATH
	$dirname/$appname "$@"
fi


