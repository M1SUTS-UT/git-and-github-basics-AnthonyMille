#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

 //Déclaration de variables

        double a,b,c;
        double delta, x1, x2;
        
        printf("Entrez les coefficients a, b et c : ");
        scanf("%lf %lf %lf", &a, &b, &c);
       
    // Vérification si a est nul
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("L'équation a une infinité de solutions.\n");
            } else {
                printf("L'équation n'a pas de solution.\n");
            }
        } else {
            x1 = -c / b;
            printf("C'est une équation linéaire. Solution unique : x = %.2lf\n", x1);
        }
    } else {
        delta = b * b - 4 * a * c;

        if (delta > 0) {
            x1 = (-b + sqrt(delta)) / (2 * a);
            x2 = (-b - sqrt(delta)) / (2 * a);
            printf("Deux racines réelles distinctes : x1 = %.2lf et x2 = %.2lf\n", x1, x2);
        } else if (delta == 0) {
            x1 = -b / (2 * a);
            printf("Une racine réelle double : x = %.2lf\n", x1);
        } else {
            printf("Pas de racines réelles (delta < 0).\n");
        }
     	}
      
 // Affiche les valeurs saisies
 
    return 0;

}

  
