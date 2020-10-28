#!/bin/bash
DZIEN='date +%u'
if [ "$DZIEN" = 6 ]
then
    echo "Weekend"
else
    if [ "$DZIEN" = 7 ]
    then
        echo "Weekend"
    else
        echo "Dzien roboczy"
    fi
fi
