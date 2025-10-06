#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Fonction représentant l'équation différentielle : y' = f(x, y) = -y
double f(double x, double y) {
    return -y;
}

// Méthode d’Euler (ordre 1)
double euler_step(double x, double y, double h) {
    return y + h * f(x, y);
}

// Méthode de Heun (ordre 2)
double heun_step(double x, double y, double h) {
    double k1 = f(x, y);
    double k2 = f(x + h, y + h * k1);
    return y + h * (k1 + k2) / 2.0;
}

// Méthode de Runge-Kutta 4 (ordre 4)
double rk4_step(double x, double y, double h) {
    double k1 = f(x, y);
    double k2 = f(x + h / 2.0, y + h / 2.0 * k1);
    double k3 = f(x + h / 2.0, y + h / 2.0 * k2);
    double k4 = f(x + h, y + h * k3);
    return y + h * (k1 + 2*k2 + 2*k3 + k4) / 6.0;
}

// Fonction générique de résolution de l'équation différentielle
void resoudre_edo(
    double (*step_method)(double, double, double), // On appelle un pointeur pour a la fin du programme chosir la méthode que l'on veut 
    double h,
    double x0,
    double y0,
    double x_max,
    const char* nom_methode
) {

    int steps = (int)(10.0 / h);  // Nombre d'étapes : (10 - 0) / h
    double x = x0;
    double y = y0;

    printf("\nMéthode : %s | Pas h = %.4f\n", nom_methode, h);
    printf("x\t\t y (Numérique)\t y (Exact)\t Erreur\n");

    for (int k = 0; k <= steps; k++) {
        double y_exact = exp(-x);                // Solution exacte : y(x) = e^{-x}
        double erreur = fabs(y - y_exact);       // Erreur absolue
        printf("%.4f\t %.6f\t %.6f\t %.6f\n", x, y, y_exact, erreur); // Affiche les résultats

        y = step_method(x, y, h); // Mise à jour de y avec la méthode de notre choix
        x += h;  // Incrément de x : x_{n+1} = x_n + h
    }
}

int main() {

// Paramètres du problème

    double x0 = 0.0;   // Valeur initiale de x
    double y0 = 1.0;   // Condition initiale : y(0) = 1
    double x_max = 10.0; // Valeur finale de x
    
// Liste des pas à tester

    double pas[] = {1.0, 0.5, 0.1, 0.01}; // Plus le pas est petit, plus la solution est précise
    int n = sizeof(pas) / sizeof(pas[0]); // Calcul du nombre d’éléments dans le tableau

// Choix de la méthode par l'utilisateur
    int choix;
    printf("Choisissez la méthode :\n");
    printf("1. Euler\n");
    printf("2. Heun \n");
    printf("3. Runge-Kutta 4\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

// Déclaration de pointeur de fonction pour la méthode choisie
    double (*step_method)(double, double, double) = NULL;
    const char* nom_methode = "";

// Sélection de la méthode
    switch (choix) {
        case 1:
            step_method = euler_step;
            nom_methode = "Euler";
            break;
        case 2:
            step_method = heun_step;
            nom_methode = "Heun";
            break;
        case 3:
            step_method = rk4_step;
            nom_methode = "Runge-Kutta 4";
            break;
        default:
            printf("Choix invalide. Veuillez entrer 1, 2 ou 3.\n");
            return 1;
    }
    
 
// Boucle sur chaque pas pour chaque méthode
    for (int i = 0; i < n; i++) {
        double h = pas[i];
        resoudre_edo(step_method, h, x0, y0, x_max, nom_methode); // Appel au terminal de la méthode de mon choix 
    }

    return 0;
}

