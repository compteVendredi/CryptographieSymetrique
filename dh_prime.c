/// \file dh_prime.c
/// \author Tom Gresset (modification de celui de DUGAT)
/// \date novembre 2020
/// \brief Calculs sur les nombres premiers, génération, tests, etc.

#include "dh.h"
long random_long(long min,long max){
/// \brief génère un uint aléatoire entre min et max
/// \param[in] min et max des uint
/// \return n : min≤n≤max
  return (rand()%(max-min)) + min;
}

long puissance_mod_n (long a, long e, long n) {
  /// /brief puissance modulaire, calcule a^e mod n
  /// a*a peut dépasser la capacité d'un long
  /// https://www.labri.fr/perso/betrema/deug/poly/exp-rapide.html
  /// vu au S1 en Python
  long p;
  for (p = 1; e > 0; e = e / 2) {
    if (e % 2 != 0)
      p = (p * a) % n;
    a = (a * a) % n;
  }
  return p;
}

int rabin (long a, long n) {
  /// \brief test de Rabin sur la pimarité d'un entier
  /// \brief c'est un test statistique. Il est plus rapide que le précédent.
  /// \param[in] a : on met 2, ça marche
  /// \param[in] n : le nombre à tester
  /// \returns 1 il est premier, 0 sinon
  long p, e, m;
  int i, k;

  e = m = n - 1;
  for (k = 0; e % 2 == 0; k++)
    e = e / 2;

  p = puissance_mod_n (a, e, n);
  if (p == 1) return 1;

  for (i = 0; i < k; i++) {
    if (p == m) return 1;
    if (p == 1) return 0;
    p = (p * p) % n;
  }

  return 0;
}


long genPrimeSophieGermain(long min,long max,int *cpt){
  /// \brief fournit un nombre premier de Sophie Germain vérifié avec le test de rabin
  /// \param[in] min et max
  /// \param[out] cpt : le nombre d'essais pour trouver le nombre
  /// \returns un nombre premier p min≤p≤max && p = 2*q+1 avec q premier
  long num;
  *cpt=1;
  int a=2;
  do{
    num = random_long(min,max);
  } while (num%2!=1);

  while ((!rabin(a,num) || !rabin(a,2*num+1)) && num<max){
    (*cpt)++;
    num=num+2;
  }
  return 2*num+1;
}

long seek_generator(long start,long p){
  /// \brief recherche d'un générateur du groupe (corps) cyclique Z/pZ avec p premier
  long q = (p-1)/2; /// \note p est un premier de Sophie Germain ie p =2q+1 avec q premier

  /// \note si p = \prod(i=1,k,{p_i}^{n_i}) alors g est un générateur si \forall i 1..k, g^p_i != 1 (mod p)
  /// comme p = 2q+1 et q premier, k = 2 et p_i = 2 et q.
  /// il suffit que g^2 et g^q soient tous les deux différents de 1 (mod p)
  while ((puissance_mod_n(start, 2, p) == 1 || puissance_mod_n(start,q,p) == 1) && start < p-1){
    start++;
  }
  if (start == p-1) return -1;
  return start;
}

long xchange_shared_key(long p, long g){
/// \brief similateur d'échange de clefs de Diffie-Hellman par réseau
/// \param[in] premier : un nombre premier, generateur : un générateur du groupe Z/premierZ
/// \returns la clef commune générée
    printf("1. Alice et Bob ont choisi le nombre premier p=%ld et la base g=%ld (public)\n", p, g);
    long a, b, A, B, cle;
    a = rand()%(p-1)+1;
    printf("2. Alice choisit le nombre secret a=%ld (privé)\n", a);
    A = puissance_mod_n(g, a, p);
    printf("3. Elle envoie à Bob la valeur A=%ld (public)\n", A);
    b = rand()%(p-1)+1;
    printf("4. Bob chiosit à son tour un nombre secret b=%ld (privé)\n", b);
    B = puissance_mod_n(g, b, p);
    printf("5. Bob envoie à Alice la valeur B=%ld (public)\n", B);
    cle = puissance_mod_n(B, a, p);
    printf("6. Alice calcul la clé secrète qui est %ld (privé)\n", cle);
    cle = puissance_mod_n(A, b, p);
    printf("7. Bob calcul la clé secrète qui est %ld (privé)\n", cle);
    return cle;
}

long generate_shared_key(long min,long max, FILE* logfp){
  /// \brief calcule un nombre premier p de Sophie Germain et un générateur du groupe p/Zp.
  /// appelle le simulateur d'échange de clef partagée.
  /// \returns la clef partagée
  int cpt;
  fprintf(logfp,"Génération de la clef partagée\n");
  long premier = genPrimeSophieGermain(min,max,&cpt);
  fprintf(logfp,"Premier (Sophie Germain) = %ld\n",premier);
  long generateur = seek_generator(3,premier); // exemple 100
  long ordre = puissance_mod_n (generateur, premier-1, premier); // generateur^{premier -1} (mod premier)
  fprintf(logfp,"Générateur = %ld ordre = %ld\n",generateur,ordre);
  assert (generateur != -1);
  return xchange_shared_key(premier, generateur);
}


