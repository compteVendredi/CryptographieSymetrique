#ifndef DH_PRIME_H
#define DH_PRIME_H

#define MAX_PRIME 4294967296/1000 // 2^32 = sqrt(2^64)
#define MIN_PRIME 100

long random_long(long min,long max);
long puissance_mod_n (long a, long e, long n);
int rabin (long a, long n) ;
long genPrimeSophieGermain(long min,long max,int *cpt);
long seek_generator(long start,long p);
long xchange_shared_key(long generateur, long premier);
long generate_shared_key(long min,long max, FILE* logfp);

#endif 
