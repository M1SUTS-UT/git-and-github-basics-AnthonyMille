#include <stdio.h>
#include <stdlib.h>  // Nécessaire pour malloc et free

int main() {
    int *tableauEntier;  // Pointeur vers int, pour le tableau d'entiers dynamique
    float *tableauFlottant;  // Pointeur vers float, pour le tableau de flottants dynamique
    int tailleTableau;

    // Demander à l'utilisateur la taille des tableaux
    printf("Entrez la taille des tableaux: ");
    scanf("%d", &tailleTableau);

    // Allouer de la mémoire pour le tableau d'entiers
    tableauEntier = (int *) malloc(tailleTableau * sizeof(int));

    // Vérifier si l'allocation de mémoire a réussi
    if(tableauEntier == NULL) {
        printf("Impossible d'allouer de la mémoire pour le tableau d'entiers\n");
        return 1;  // Retourner avec un code d'erreur
    }

    // Allouer de la mémoire pour le tableau de flottants
    tableauFlottant = (float *) malloc(tailleTableau * sizeof(float));

    // Vérifier si l'allocation de mémoire a réussi
    if(tableauFlottant == NULL) {
        printf("Impossible d'allouer de la mémoire pour le tableau de flottants\n");
        free(tableauEntier);  // Libérer la mémoire allouée pour le tableau d'entiers avant de sortir
        return 1;  // Retourner avec un code d'erreur
    }

    // Exemple: Stocker et imprimer les éléments des tableaux
    for(int i = 0; i < tailleTableau; i++) {
        tableauEntier[i] = i;  // Stocker i dans le i-ème élément de tableauEntier
        tableauFlottant[i] = i * 0.1f;  // Stocker i * 0.1 dans le i-ème élément de tableauFlottant
        printf("tableauEntier[%d] = %d, tableauFlottant[%d] = %f\n", i, tableauEntier[i], i, tableauFlottant[i]);
    }

    // N'oubliez pas de libérer la mémoire allouée!
    free(tableauEntier);
    free(tableauFlottant);

    return 0;
}

