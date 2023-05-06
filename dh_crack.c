#include "dh.h"
#include "dh_crack.h"
#include "dh_crack_c1.h"
#include "dh_crack_c2.h"

int estChaineChiffre(char* chaine)
{
    for(int i = 0; chaine[i] != '\0'; i++)
        if(!isdigit(chaine[i]))
            return 0;
    return 1;
}

int verifierCMDCrack(int argc, char **argv, char **chemin_msg, char **methode, int *longueur_key)
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
            else if(strcmp(argv[i-1], "-m") == 0 && strcmp(*methode, "") == 0)
                *methode = argv[i];
            else if(strcmp(argv[i-1], "-k") == 0 && *longueur_key == 0)
            {
                if(estChaineChiffre(argv[i]))
                    *longueur_key = atoi(argv[i]);
                else
                    return 1;
            }
            else
               return 1;
        } 
        else
            return 1;
    }
    if(strcmp(*chemin_msg, "") == 0 || *longueur_key == 0 || (strcmp(*methode, "c1") != 0
    && strcmp(*methode, "c2") != 0 && strcmp(*methode, "all") != 0))
        return 1;
    return END;
}

void lancerCMDCrack(int longueur_key, char *chemin_msg, char *methode)
{
    char **keys = NULL;
    int nbCle = 0;
    t_tab_keys tabKey;
    tabKey.key_size = longueur_key;
    if(tabKey.key_size > MAX_SIZE_KEY)
        tabKey.key_size = MAX_SIZE_KEY;
    initTabKey(&tabKey);
    keys = malloc(MAX_KEYS * sizeof(char*));
    for(int i = 0; i < MAX_KEYS; i++)
        keys[i] = malloc(tabKey.key_size * sizeof(char));
    if(strcmp(methode, "c1") == 0 || strcmp(methode, "all") == 0)
    {
        crack1(&tabKey, chemin_msg, keys, &nbCle, 1);
        if(strcmp(methode, "all") == 0)
            crack2(chemin_msg, keys, nbCle, tabKey.key_size);
    }
    else
    {
        crack1(&tabKey, chemin_msg, keys, &nbCle, 0);
        crack2(chemin_msg, keys, nbCle, tabKey.key_size);
    }
    for(int i = 0; i < tabKey.key_size; i++)
        free(tabKey.tab_keys[i]);
    free(tabKey.tab_keys);
    for(int i = 0; i < MAX_KEYS; i++)
        free(keys[i]);
    free(keys);
}

int main(int argc, char **argv)
{
    int longueur_key = 0;
    char *chemin_msg = "", *methode = "";

    int retour = verifierCMDCrack(argc, argv, &chemin_msg, &methode, &longueur_key);

    if(retour == 2)
        printf(CRACK_CMD_H);  
    else if(retour == 1)
        printf("Commande inconnue, faites dh_crack -h pour avoir de l'aide\n");
    else
        lancerCMDCrack(longueur_key, chemin_msg, methode);
    return END;
}
