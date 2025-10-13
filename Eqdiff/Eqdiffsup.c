#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Définition des paramètres
#define OMEGA0 (2 * M_PI)  // Fréquence propre ω₀ = 2π
#define DT 0.001           // Pas de temps
#define T_MAX 2            // Durée totale de simulation (en secondes)
#define N ((int)(T_MAX / DT)) // Nombre de pas de simulation
#define EPSILON 0.1           // Coefficient d'amortissement ε

/*
// Fonction pour v' = -ω₀² y
double acceleration(double y) {
    return -OMEGA0 * OMEGA0 * y;
}


// Déclaration des variables
    
int main() {

    // Variables pour les 3 méthodes
    double t = 0.0; // Temps courant

    // Euler
    double y_e = 1.0, v_e = 0.0; // Position initiale : y(0) = 1 et Vitesse initiale : y'(0) = 0

    // Heun
    double y_h = 1.0, v_h = 0.0;

    // RK4
    double y_rk = 1.0, v_rk = 0.0;
    
    // Fichier de sortie pour visualiser les résultats avec Gnuplot ou Python
    FILE *f = fopen("comparaison_3_methodes.dat", "w");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Boucle principale : méthode d'Euler explicite
    for (int i = 0; i <= N; i++) {
        // Sauvegarde de l’état courant dans le fichier
        fprintf(f, "%lf %lf %lf %lf\n", t, y_e, y_h, y_rk);

 // Calcul des prochaines valeurs

// ========= MÉTHODE D’EULER ========
   		double a_e = acceleration(y_e);
        double y_e_next = y_e + DT * v_e;
        double v_e_next = v_e + DT * a_e;
        y_e = y_e_next;
        v_e = v_e_next;
 
// ========= MÉTHODE DE HEUN =========
        double a1 = acceleration(y_h);
        double y_pred = y_h + DT * v_h;
        double v_pred = v_h + DT * a1;
        double a2 = acceleration(y_pred);
        y_h += DT * 0.5 * (v_h + v_pred);
        v_h += DT * 0.5 * (a1 + a2);

// ========= MÉTHODE DE RUNGE-KUTTA 4 =========
        double k1y = DT * v_rk;
        double k1v = DT * acceleration(y_rk);   
        
        double k2y = DT * (v_rk + 0.5 * k1v);
        double k2v = DT * acceleration(y_rk + 0.5 * k1y);

        double k3y = DT * (v_rk + 0.5 * k2v);
        double k3v = DT * acceleration(y_rk + 0.5 * k2y);

        double k4y = DT * (v_rk + k3v);
        double k4v = DT * acceleration(y_rk + k3y);

        y_rk += (k1y + 2*k2y + 2*k3y + k4y) / 6.0;
        v_rk += (k1v + 2*k2v + 2*k3v + k4v) / 6.0;

        // Avancer dans le temps
        t += DT;
    }  
      
    fclose(f);
    printf("Simulation terminée. Résultats dans 'comparaison_3_methodes.dat'.\n");

    return 0;
}*/



/// On ajoute un terme d'amortissement de la forme 2ϵω0y′ pour avoir un sytème amorti

// Fonction pour v' = -2ϵω₀v -ω₀² y
double acceleration(double y, double v) {
    return - 2 * EPSILON * OMEGA0 * v - OMEGA0 * OMEGA0 * y;
}

// Déclaration des variables
    
int main() {

    // Variables pour les 3 méthodes
    double t = 0.0; // Temps courant

    // Euler
    double y_e = 1.0, v_e = 0.0; // Position initiale : y(0) = 1 et Vitesse initiale : y'(0) = 0

    // Heun
    double y_h = 1.0, v_h = 0.0;

    // RK4
    double y_rk = 1.0, v_rk = 0.0;
    
    // Fichier de sortie pour visualiser les résultats avec Gnuplot ou Python
    FILE *f = fopen("comparaison_3_methodes.dat", "w");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Boucle principale : méthode d'Euler explicite
    for (int i = 0; i <= N; i++) {
        // Sauvegarde de l’état courant dans le fichier
        fprintf(f, "%lf %lf %lf %lf\n", t, y_e, y_h, y_rk);

 // Calcul des prochaines valeurs

// ========= MÉTHODE D’EULER ========
   		double a_e = acceleration(y_e, v_e);
        double y_e_next = y_e + DT * v_e;
        double v_e_next = v_e + DT * a_e;
        y_e = y_e_next;
        v_e = v_e_next;
 
// ========= MÉTHODE DE HEUN =========
        double a1 = acceleration(y_h, v_h);
        double y_pred = y_h + DT * v_h;
        double v_pred = v_h + DT * a1;
        double a2 = acceleration(y_pred, v_pred);
        y_h += DT * 0.5 * (v_h + v_pred);
        v_h += DT * 0.5 * (a1 + a2);

// ========= MÉTHODE DE RUNGE-KUTTA 4 =========
        double k1y = DT * v_rk;
		double k1v = DT * acceleration(y_rk, v_rk);

		double k2y = DT * (v_rk + 0.5 * k1v);
		double k2v = DT * acceleration(y_rk + 0.5 * k1y, v_rk + 0.5 * k1v);

		double k3y = DT * (v_rk + 0.5 * k2v);
		double k3v = DT * acceleration(y_rk + 0.5 * k2y, v_rk + 0.5 * k2v);

		double k4y = DT * (v_rk + k3v);
		double k4v = DT * acceleration(y_rk + k3y, v_rk + k3v);


        y_rk += (k1y + 2*k2y + 2*k3y + k4y) / 6.0;
        v_rk += (k1v + 2*k2v + 2*k3v + k4v) / 6.0;

        // Avancer dans le temps
        t += DT;
    }  
      
    fclose(f);
    printf("Simulation terminée. Résultats dans 'comparaison_3_methodes.dat'.\n");

    return 0;
}


