#ifndef CRACK_H
#define CRACK_H

/// \file dh_crack.h
/// \author Tom Gresset 
/// \date décembre 2020
/// \brief Des defines sur une clé, la structure d'un tableau 2d de clé, des prototypes

#define  MAX_SIZE_KEY 8  /* 7 + '\0' caractères max dans la clef */
#define  MAX_VALID_KEY_CHARS 10 // dix caractères numériques possibles pour chaque caractère de la clef
#define  MAX_KEYS 30000 // nombre max de clefs potentielles gérées

//Le message d'aide pour la commande
#define CRACK_CMD_H "\t    -i suivie du nom du fichier contenant le message à décrypter\n\
            -m c1 ou all (c1 lance la méthode c1 seulement et all = c1 et c2)\n\
            -k longueur de la clef\n\
            -h donnant l'aide sans autre action\n\
       Cette option, si elle est présente, annule toutes les autres\n" 

typedef struct {
	int key_size; // longueur de la clef
	byte **tab_keys; // 2 dim : ligne i = liste des caractères admissibles pour clef[i]
} t_tab_keys;

int estChaineChiffre(char* chaine);
/// \brief Test si une chaîne est un nombre
/// \param[in] chaine : la chaîne à tester
/// \returns 1 si elle est composée uniquement de chiffre, 0 sinon

int verifierCMDCrack(int argc, char **argv, char **chemin_msg, char **methode, int *longueur_key);
/// \brief Renvoie un code de retour en fonction des paramètre rentrés par la ligne de commande
/// \returns END (define) si elle est correcte, 1 si elle est fausse, 2 s'il y a l'option h

void lancerCMDCrack(int longueur_key, char *chemin_msg, char *methode);
/// \brief Lance la commande crack en fonction des paramètres rentrés

#endif
