#include "dh_crack_c2.h"

void calculScore(float **freq, int nbCle, float *score)
{
    //freq en texte anglais
    float freq_th[26] = {8.2, 1.5, 2.8, 4.3, 13, 2.2, 2, 6.1,
    //i    
    7, 0.15, 0.77, 4, 2.4, 6.7, 7.5, 1.9, 0.095, 6, 6.3, 9.1, 2.8,
    //v
    0.98, 2.4, 0.15, 2, 0.074};
    for(int i = 0; i < 26; i++)
        for(int j = 0; j < nbCle; j++)
            score[j] += pow(freq_th[i]-freq[i][j], 2);
}

void afficherScore(char **keys, int nbCle, float *score)
{
    int minimum = 0;
    for(int i = 0; i < nbCle; i++)
    {
        if(score[minimum] > score[i])
            minimum = i; 
    }
    printf("La meilleur clef est %s avec %f en distance\n", keys[minimum], score[minimum]);
}

void crack2(char* chemin_msg, char **keys, int nbCle, int tailleCle)
{
    FILE* fichier_msg = NULL;
    fichier_msg = fopen(chemin_msg, "r");
    if(fichier_msg != NULL)
    {    
        int val = 0, caracTotal = 0, indice = 0;
        float **freq, *score;
        freq = malloc(26 * sizeof(float*));
        score = malloc(nbCle * sizeof(float));
        for(int i = 0; i < nbCle; i++)
            score[i] = 0;
        for(int i = 0; i < 26; i++)
        {
            freq[i] = malloc(nbCle * sizeof(float));
            for(int j = 0; j < nbCle; j++)
                freq[i][j] = 0;        
        }
        while((val=fgetc(fichier_msg)) != EOF)
        {
            for(int i = 0; i < nbCle; i++)
            {
                val = (48+keys[i][indice])^val;
                if(isalpha(val))
                {
                    if(isupper(val))
                        val = tolower(val);
                    freq[val-97][i]++;
                }
            }
            indice++;
            caracTotal++;
            if(indice > tailleCle)
                indice = 0;
        }
        fclose(fichier_msg);   
        for(int i = 0; i < 26; i++)
            for(int j = 0; j < nbCle; j++)
                freq[i][j] = freq[i][j]/caracTotal*100;  
        printf("C2:\n");
        calculScore(freq, nbCle, score);
        afficherScore(keys, nbCle, score);
        free(score);
        for(int i = 0; i < 26; i++)
            free(freq[i]);
        free(freq);   
    }
    else
        printf("Erreur lors de l'ouverture du fichier %s", chemin_msg);
}
