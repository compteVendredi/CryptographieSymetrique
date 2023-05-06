#!/bin/bash

ko='\e[00;31m';
wipe='\e[00m';
ok='\e[01;32m';

BASE=../..
TEST=./tests
RET=

function test_crack_c1 {
# critère C1
    rm -rf $TEST/keys0
    mkdir $TEST/keys0

    if [ -x $BASE/dh_crack ]
    then
    while read k
    do
    while read i
    do
    $BASE/dh_crack -i $TEST/crypted_crack/${k}_${i} -m c1 -k ${#k} > $TEST/keys0/${k}_${i}
    diff $TEST/keys0/${k}_${i} $TEST/ref_keys0/${k}_${i} &>/dev/null
    RET=$?
    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return
    done < ./$TEST/file_list_crack.txt
  done  < ./$TEST/keys_crack.txt
    else
    RET=2
    fi

    }

    function test {
        test_$1

        [ $RET -eq 0 ] && printf "%-12s [${ok}OK${wipe}]\n" "$1"
        [ $RET -ne 0 ] && printf "%-12s [${ko}KO${wipe}]\n" "$1"
    }

test crack_c1; # validité

    exit 0
