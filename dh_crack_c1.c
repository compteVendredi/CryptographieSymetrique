#include "dh_crack_c1.h"

void initTabKey(t_tab_keys *tabKey)
{
    tabKey->tab_keys = malloc(tabKey->key_size * sizeof(byte*));
    for(int i = 0; i < tabKey->key_size; i++)
    {
        tabKey->tab_keys[i] = malloc(MAX_VALID_KEY_CHARS * sizeof(byte));
        for(int j = 0; j < MAX_VALID_KEY_CHARS; j++)
            tabKey->tab_keys[i][j] = j;
    }
    tabKey->tab_keys[0][0] = 10;
}

void produitCartesien(t_tab_keys *tabKey, int profondeur, char *key, int *nbCle, char **keys)
{
    if(profondeur < tabKey->key_size)
        for(int i = 0; i < MAX_VALID_KEY_CHARS; i++)
        {
            if(*nbCle >= MAX_KEYS)
                break;
            if(tabKey->tab_keys[profondeur][i] != 10)
            {
                key[profondeur] = 48+tabKey->tab_keys[profondeur][i];
                profondeur++;
                produitCartesien(tabKey, profondeur, key, nbCle, keys);
                profondeur--;
            }
        }
    else
    {
        strcpy(keys[*nbCle], key);
        *nbCle=*nbCle+1;
    }
        
}

int caracValide(int c)
{
    return ispunct(c) || isalnum(c) || isspace(c) || isblank(c);
}

void crack1(t_tab_keys *tabKey, char* chemin_msg, char **keys, int *nbCle, int affichage)
{
    FILE* fichier_msg = NULL;
    fichier_msg = fopen(chemin_msg, "r");
    if(fichier_msg != NULL)
    {
        int i = 0, val = 0;
        while((val=fgetc(fichier_msg)) != EOF)
        {
            for(int j = 0; j < MAX_VALID_KEY_CHARS; j++)
                if(tabKey->tab_keys[i][j] != -1 && !caracValide((48+tabKey->tab_keys[i][j])^val))
                    tabKey->tab_keys[i][j] = 10;  
            i++;
            if(i >= tabKey->key_size)
                i = 0;
        }
        fclose(fichier_msg);
        char *key=NULL;
        key=malloc(tabKey->key_size);
        for(int j = 0; j < tabKey->key_size; j++)
            key[j] = ' ';
        key[tabKey->key_size]='\0';
        produitCartesien(tabKey, 0, key, nbCle, keys);
        if(affichage)
        {
            for(int j = 0; j < tabKey->key_size; j++)
            {
                printf("[");
                for(int k = 0; k < MAX_VALID_KEY_CHARS; k++)
                    if(isdigit(48+tabKey->tab_keys[j][k]))
                        printf("%c,", 48+tabKey->tab_keys[j][k]);
                printf("]\n");
            }
            printf("\nSoit %d clef(s)\n", *nbCle);
        }
        free(key);  
    }
    else
        printf("Erreur lors de l'ouverture du fichier %s", chemin_msg);

}
