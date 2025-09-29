#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Définition de la fonction f(x) = sin(x)
double f(double x){
    return sin(x);
}

// Méthode du point milieu (rectangle au centre)

double rectangle(double start,double b, double n){ // On définit la méthode d'intégration utilisée
	double h = (b-start)/n; // n= le nombre de point dans l'air 
	double somme = 0.0; //On s'assure que ca reste une double avec des chiffres aprés la virgule
	double milieu = 0; // On itialise à zéro

// On écrit la boucle pour la calculer la fonction 

	for (int k = 0; k < n; k++) {
		
		double xk = start + k* h; // Valeur initial xk au début vaut 0
		double xk1 = xk + h;
		milieu = (xk + xk1)/2; // Formule voir cours sur la méthode des triangle
 		somme += f(milieu); // Fait le calcul de somme c'est le sigma 
    }
    
    return h*somme;
    
}

// Méthode des trapèzes
double trapeze(double a, double b, int n){
    double h = (b - a) / n;
    double somme = (f(a) + f(b)) / 2.0;

    for (int k = 1; k < n; k++) {
        double xk = a + k * h; // a est la fonction et b la fonction suivante 
        somme += f(xk);
    }

    return h * somme;
}

// Méthode de Simpson
double simpson(double a, double b, int n){
    if (n % 2 != 0) {
        printf("Simpson nécessite un nombre pair de sous-intervalles. n est incrémenté de 1.\n");
        n++;  // Simpson nécessite un n pair
    }

    double h = (b - a) / n;
    double somme = f(a) + f(b);

    for (int k = 1; k < n; k++) {
        double xk = a + k * h;
        if (k % 2 == 0) { // Si k est un nombre pair
            somme += 2 * f(xk);
        } else { // Si k est un nombre impair 
            somme += 4 * f(xk);
        }
    }

    return (h / 3.0) * somme;
}

// Programme principal

int main() { // Fonction main pour que le terminal comprenne ce que je lui écrit 
    double a = 0.0;
    double b = M_PI / 2;  // Intégrale de sin(x) entre 0 et π/2 avec M_PI=pi en C
    int n;

    printf("Intégration de sin(x) sur [%.2f, %.2f] avec méthode du point milieu\n", a, b);
    printf("Entrez le nombre de sous-intervalles n : ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Le nombre de sous-intervalles doit être strictement positif.\n");
        return 1;
    }

// On affiche les fonctions 

    double exact = 1.0; // Valeur exact de l'integral sin(x) entre 0 et 2pi

    double res_rect = rectangle(a, b, n);
    double res_trap = trapeze(a, b, n);
    double res_simp = simpson(a, b, n);

    printf("\nMéthode               Résultat        Erreur absolue\n");
    printf("-----------------------------------------------------\n");
    printf("Point milieu (rect) : %.10f erreur :  %.10e\n", res_rect, fabs(res_rect - exact)); /// Car erreur =|val.num - valexact|
    printf("Trapèzes            : %.10f  erreur : %.10e\n", res_trap, fabs(res_trap - exact));
    printf("Simpson             : %.10f  erreur : %.10e\n", res_simp, fabs(res_simp - exact));

// Pour crée un fichier de résultat

 FILE *fich;

    fich = fopen("resultats_integration.txt", "w");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
    } 
    for (int i=0; i<= n; i+=2) { // Pour faire des pas de 2 pour la méthode de simpson
    	 res_rect = rectangle(a, b, i); 
    	 res_trap = trapeze(a, b, i);
    	 res_simp = simpson(a, b, i);
     
       	fprintf(fich, "%d %.10f %.10f %.10f\n", i, fabs(res_rect - exact), fabs(res_trap - exact), fabs(res_simp - exact)); // Écriture de la première valeur
    }
        fclose(fich);
    return 0;
}




	
