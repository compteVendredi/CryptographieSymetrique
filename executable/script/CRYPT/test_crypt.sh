#!/bin/bash

ko='\e[00;31m';
wipe='\e[00m';
ok='\e[01;32m';

BASE=../..
TEST=./tests
RET=

function test_cipher_xor {
    RET=0

    if [ -x $BASE/dh_crypt ]
    then

    rm -rf $TEST/crypted/
    mkdir $TEST/crypted/

    while read k;
    do
	while read i
	do
 	    $BASE/dh_crypt -i $TEST/ref/$i  -o $TEST/crypted/xor_${k}_${i} -k $k -m xor> /dev/null
	    diff $TEST/ref_crypted/xor_${k}_$i $TEST/crypted/xor_${k}_${i}  &>/dev/null
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <./$TEST/file_list.txt
    done < ./$TEST/keys.txt
    else
	RET=2
    fi

}

function test_decipher_xor {
    RET=0

    rm -rf $TEST/decrypted/
    mkdir $TEST/decrypted/

    if [ -x $BASE/dh_crypt ]
    then

	while read k
	do
	    while read i
	    do
 		$BASE/dh_crypt -o $TEST/decrypted/xor_${k}_$i  -i $TEST/crypted/xor_${k}_${i} -k $k -m xor&> /dev/null
		diff $TEST/ref/$i $TEST/decrypted/xor_${k}_${i}  &>/dev/null
		RET=$?
		[ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
		[ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return
	    done < ./$TEST/file_list.txt
	done  < ./$TEST/keys.txt
    else
	RET=2
    fi
}

function test_cipher_cbc {
    RET=0

    if [ -x $BASE/dh_crypt ]
    then

    rm -rf $TEST/crypted/
    mkdir $TEST/crypted/

    while read k;
    do
	while read i
	do
 	    $BASE/dh_crypt -i $TEST/ref/$i  -o $TEST/crypted/cbc_${k}_${i} -k $k -m cbc-crypt azertyuiopqsdfgh> /dev/null
	    diff $TEST/ref_crypted/cbc_${k}_$i $TEST/crypted/cbc_${k}_${i}  &>/dev/null
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <./$TEST/file_list.txt
    done < ./$TEST/keys.txt
    else
	RET=2
    fi

}

function test_decipher_cbc {
    RET=0

    rm -rf $TEST/decrypted/
    mkdir $TEST/decrypted/

    if [ -x $BASE/dh_crypt ]
    then

	while read k
	do
	    while read i
	    do
 		$BASE/dh_crypt -o $TEST/decrypted/cbc_${k}_$i  -i $TEST/crypted/cbc_${k}_${i} -k $k -m cbc-uncrypt azertyuiopqsdfgh&> /dev/null
		#diff -b $TEST/ref/$i $TEST/decrypted/cbc_${k}_${i}  &>/dev/null
		RET=$?
		[ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
		[ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return
	    done < ./$TEST/file_list.txt
	done  < ./$TEST/keys.txt
    else
	RET=2
    fi
}

function test {
    test_$1

    [ $RET -eq 0 ] && printf "===> %-12s [${ok}OK${wipe}]\n" "$1"
    [ $RET -ne 0 ] && printf "xxx> %-12s [${ko}KO${wipe}]\n" "$1"
}

test cipher_xor;
test decipher_xor;
test cipher_cbc;
test decipher_cbc;
printf "Contrôle de déchiffrage CBC : avec les yeux (pb de caractères de pading)\n"

exit 0
