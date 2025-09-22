#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE *fich;

    fich = fopen("resultats_syracus.txt", "w");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return 1;
    }

    int u0;
    printf("Entrez un entier u0 > 1 : ");
    scanf("%d", &u0);

    if (u0 <= 1) {
        printf("L'entier doit être strictement supérieur à 1.\n");
        return 1;
    }

    int u = u0;      // Valeur actuelle de la suite
    int p = 0;       // Temps de vol (nombre d'étapes jusqu'à 1)
    int altitude = u0; // Altitude = valeur maximale atteinte par la suite

    fprintf(fich, "%d \t %d\n", u, p); // Écriture de la première valeur

    // Calcul de la suite jusqu'à ce que u atteigne 1
    while (u != 1) {
        if (u % 2 == 0) {
            u /= 2;
        } else {
            u = 3 * u + 1;
        }

        p++;  // Incrémentation du temps de vol
        if (u > altitude) {
            altitude = u;  // Mise à jour de l'altitude si u est plus grand
        }

        fprintf(fich, "%d \t %d\n", u, p);
    }

    printf("\nRésultats :\n");
    printf("Temps de vol : %d étapes\n", p);
    printf("Altitude : %d\n", altitude);

    fclose(fich);
    return 0;
}

