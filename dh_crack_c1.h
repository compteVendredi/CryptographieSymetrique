#ifndef CRACK_H_C1
#define CRACK_H_C1

/// \file dh_crack_c1.h
/// \author Tom Gresset 
/// \date décembre 2020
/// \brief Les prototypes de fonction pour executer crack_c1

#include "dh.h"
#include "dh_crack.h"

void initTabKey(t_tab_keys *tabKey);
/// \brief Initialise un tabKey.tab_keys de 0 à 9 avec [0][0]=10=nul
/// \param[in] tabKey : un tabKey à intialiser

void produitCartesien(t_tab_keys *tabKey, int profondeur, char *key, int *nbCle, char **keys);
/// \brief Effectuer le produit cartesien d'un tabKey.tab_keys recursivement
/// \param[in] tabKey : un tabKey
/// \param[in] profondeur : utilisé pour la recursivité (à quelle tab_keys[x][], x on est)
/// \param[in] key : la clef en construction
/// \param[in] nbCle : le nombre de clef qui augmente
/// \param[in] keys : un tableau 2d qui contient les keys

int caracValide(int c);
/// \brief Indique si un caractère est valide dans un résultat d'un xor
/// \returns 1 si vrai, 0 sinon

void crack1(t_tab_keys *tabKey, char* chemin_msg, char **keys, int *nbCle, int affichage);
/// \brief permet de lançer le crack1 et le produitCartesien
/// \param[in] affichage : 1 pour affichage des clefs possibles sous forme (de tab) et nombre de clefs
/// \param[in] affichage : sinon pas d'affichage

#endif
