#include "dh.h"
#include "dh_crack.h"
#include "dh_prime.h"

#define GENKEY_CMD_H "\t    dh_genkey [option] [file]\n\
            Options: -h = aide, -o file écrit les résultats de l'affichage dans file\n\
            Si aucune option alors uniquement de l'affichage\n"


long dh_genkey(FILE* logfp)
{
    return generate_shared_key(MIN_PRIME, MAX_PRIME, logfp);
}

int main(int argc, char **argv)
{
    FILE *affichage;
    srand(time(NULL));
    if(argc == 1)
    {  
        affichage = fopen(".tempo_dhgenkey", "w+");
        if(affichage != NULL)
        {
            fprintf(affichage, "La clef générée est %ld\n", dh_genkey(affichage));
            char chaine[300] = "";
            fclose(affichage);
            affichage = fopen(".tempo_dhgenkey", "r");
            while(fgets(chaine, 300, affichage) != NULL)
                printf("%s", chaine);
            fclose(affichage);
            remove(".tempo_dhgenkey");
        }
        else
            printf("dh_genkey a besoin d'écrire dans un fichier .tempo_dhgenkey qu'il supprimera après"); 
    }
    else if(argc == 2 && strcmp(argv[1], "-h") == 0)
        printf(GENKEY_CMD_H);
    else if(argc == 3 && strcmp(argv[1], "-o") == 0)
    {
        affichage = fopen(argv[2], "w");
        if(affichage != NULL)
        {
            fprintf(affichage, "La clef générée est %ld\n", dh_genkey(affichage));
            fclose(affichage);
        }   
        else
            printf("Erreur lors de l'ouverture du fichier %s", argv[2]);         
    }
    else
        printf("Commande inconnue, faites dh_genkey -h pour avoir de l'aide\n");
    return END;
}
