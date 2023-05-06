#ifndef CRACK_H_C2
#define CRACK_H_C2

/// \file dh_crack_c2.h
/// \author Tom Gresset 
/// \date décembre 2020
/// \brief Les prototypes de fonction pour executer crack_c2

#include "dh.h"
#include "dh_crack.h"

void calculScore(float **freq, int nbCle, float *score);
/// \brief Calcul le score/distance d'un tableau de frequence en fonction des freqs de la langue anglaise
/// \param[in] freq : le tableau de frequence
/// \param[in] nbCle : le nombre de clefs
/// \param[in] score : le tableau des scores/distances des clefs

void afficherScore(char **keys, int nbCle, float *score);
/// \brief Affiche la clef avec le meilleur (le plus bas) score/distance

void crack2(char* chemin_msg, char **keys, int nbCle, int tailleCle);
/// \brief permet de lançer le crack2

#endif
