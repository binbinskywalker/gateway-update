#!/bin/sh
gatewayhome=${HOME}/work/gateway-daemon/build
export gatewayhome
export LD_LIBRARY_PATH=${gatewayhome}/lib:$LD_LIBRARY_PATH
cd ${gatewayhome}
nohup ./gateway-daemon &
