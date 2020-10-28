#!/bin/bash

dzien=date | cut -d ' ' -f 1
if [ $dzien == 'sun' ] || [ $dzien == 'sat' ]
then
    echo "Weekend"
else
    echo "Dzien roboczy"
fi
