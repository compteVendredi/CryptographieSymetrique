#include "dh_crypt.h"


void chiffrageXOR(char* chemin_msg, char* chemin_msg_crypte, byte* key)
{
    FILE* fichier_msg = NULL;
    fichier_msg = fopen(chemin_msg, "r");
    if (fichier_msg != NULL)
    {
        FILE* fichier_msg_crypte = NULL;
        fichier_msg_crypte = fopen(chemin_msg_crypte, "w+");
        int val = 0, indice_key = 0;
        while((val=fgetc(fichier_msg)) != EOF)
        {
            val = val^key[indice_key];
            indice_key++;
            if(key[indice_key] == '\0')
                indice_key = 0;
            fputc(val, fichier_msg_crypte);
        }
        fclose(fichier_msg_crypte);
        fclose(fichier_msg);
    }
    else
        printf("Erreur lors de l'ouverture du fichier %s", chemin_msg);
}

int verifierCMDcrypt(int argc, char **argv, char **chemin_msg, char **chemin_msg_cryptee, int *option_k
, char **methode, byte **key)
{
    if(argc <= 1)
        return 1;
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-h") == 0)
            return 2;
        else if(i+1 < argc)
        {
            i++;
            if(strcmp(argv[i-1], "-i") == 0 && strcmp(*chemin_msg, "") == 0)
                *chemin_msg = argv[i];                   
            else if(strcmp(argv[i-1], "-o") == 0 && strcmp(*chemin_msg_cryptee, "") == 0)
                *chemin_msg_cryptee = argv[i];
            else if(strcmp(argv[i-1], "-k") == 0 && *option_k == 0)
            {
                *option_k=1;
                *key = argv[i];
            }
            else if(strcmp(argv[i-1], "-m") == 0 && strcmp(*methode, "") == 0)
                *methode = argv[i];
            else
                return 1;
        } 
        else
            return 1;
    }
    if(strcmp(*chemin_msg, "") == 0 || strcmp(*chemin_msg_cryptee, "") == 0 || *option_k == 0 
    || strcmp(*methode, "xor") != 0)
        return 1;
    return END;
}

int main(int argc, char **argv)
{
    int option_k = 0;
    char *chemin_msg = "", *chemin_msg_cryptee = "", *methode= "";
    byte* key = 0;
    int retour = verifierCMDcrypt(argc, argv, &chemin_msg, &chemin_msg_cryptee, &option_k, &methode, &key);
    if(retour == 2)
        printf(CRYPT_CMD_H);  
    else if(retour == 1)
        printf("Commande inconnue, faites dh_crypt -h pour avoir de l'aide\n");
    else 
        chiffrageXOR(chemin_msg, chemin_msg_cryptee, key);
    return END;
}
