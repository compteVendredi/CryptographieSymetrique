#!/bin/sh
gcc dh_prime.c dh_genkey.c -o executable/dh_genkey
gcc dh_crypt.c -o executable/dh_crypt
gcc dh_crack.c dh_crack_c1.c dh_crack_c2.c -o executable/dh_crack -lm
