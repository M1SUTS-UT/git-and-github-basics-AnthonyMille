#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Méthode du rectangle point du milieu 

// On définit la fonction 

double f(double x){
	return sin(x);
}

// On définit la méthode d'intégration utilisée

double rectangle(double start,double b, double n){
	double h = (b-start)/n; // n= le nombre de point dans l'air 
	double somme = 0.0; //On s'assure que ca reste une double avec des chiffres aprés la virgule
	double xk = start; // Valeur initial xk au début vaut 0
	double xk1 = xk + h;
	double milieu = 0; 

// On écrit la boucle pour la calculer la fonction 

	for (int k = 0; k < n; k++) {
		
		milieu = (xk + xk1)/2; // Formule voir cours sur la méthode des triangle
		somme += f(milieu); // Fait le calcul de somme c'est le sigma 
    }

    return h * somme;
    
}

// Fonction main pour que le terminal comprenne ce que je lui écrit 

int main() {
    double a = 0.0;
    double b = M_PI / 2;  // [0, π/2]
    int n;

    printf("Intégration de sin(x) sur [%.2f, %.2f] avec méthode du point milieu\n", a, b);
    printf("Entrez le nombre de sous-intervalles n : ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Le nombre de sous-intervalles doit être strictement positif.\n");
        return 1;
    }

    double resultat = rectangle(a, b, n);
    printf("Valeur approchée de l'intégrale : %.10f\n", resultat);
    printf("Valeur exacte attendue          : %.10f\n", 1.0);  // sin(x) sur [0, π/2] donne 1

    return 0;
}




	
