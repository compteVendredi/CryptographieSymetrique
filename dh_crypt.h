#ifndef CRYPT_H
#define CRYPT_H

/// \file dh_crypt.h
/// \author Tom Gresset 
/// \date décembre 2020
/// \brief Les prototypes de fonction pour executer crypt

#include "dh.h"

#define CRYPT_CMD_H "\t    -i suivie du nom du fichier contenant le message à chiffrer en xor\n\
            -o suivie du nom du fichier où l’on va écrire le chiffré en xor\n\
            -k suivie de la clef\n\
            -m méthode de chiffrement suivie (xor uniquement)\n\
            -h affichant l’aide des commandes. Cette option, si elle est présente, annule toutes les autres.\n" 

void chiffrageXOR(char* chemin_msg, char* chemin_msg_crypte, byte* key);
/// \brief Lance le cryptage xor
/// \param[in] chemin_msg : le chemin du fichier à crypter en xor
/// \param[in] chemin_msg_cryptee : le chemin du fichier en sortie
/// \param[in] key : la clef a utilisé pour le xor

int verifierCMDcrypt(int argc, char **argv, char **chemin_msg, char **chemin_msg_cryptee, int *option_k
, char **methode, byte **key);
/// \brief Renvoie un code de retour en fonction des paramètre rentrés par la ligne de commande
/// \returns END (define) si elle est correcte, 1 si elle est fausse, 2 s'il y a l'option h

#endif
