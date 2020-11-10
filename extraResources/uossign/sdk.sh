#!/bin/bash

#workdir=$(cd $(dirname $0); pwd)
#echo $workdir

export LD_LIBRARY_PATH=$(pwd):$(pwd)/GSSignClientSDK:.
echo $LD_LIBRARY_PATH
