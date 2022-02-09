#! /bin/sh/

sh build.sh
if [ $? -eq 0 ]; then
    #echo build_success
    sh run.sh
else
    echo FAIL
fi