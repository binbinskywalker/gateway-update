#!/bin/sh
FILE=${1}
FILEPATH=/home/pi/NFS/sx1302_gateway1/packet_forwarder
COMMONDPATH=/home/pi/NFS/sx1302_gateway1
date=`%Y-%d-%m`
FILEBK="${FILE}_bk_${date}"

echo "mv ${FILEPATH}/${FILE} to ${FILEPATH}/${FILEBK}"
mv ${FILEPATH}/${FILE} ${FILEPATH}/${FILEBK}

echo "mv ${FILE} to ${FILEPATH}/${FILE}"
mv ${FILE} ${FILEPATH}/${FILE}

echo "kill old process ${FILE}"
PROCESS=`ps -ef|grep ${FILE}|grep -v grep|grep -v PPID|awk '{ print $2}'`
for i in $PROCESS
do
    echo "Kill the $1 process [ $i ]"
    kill -9 $i
done

echo "rerun process ${FILE}"
cd ${COMMONDPATH}
source run.sh
