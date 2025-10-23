* Compilation : gcc -O2 -lm -o exam_program exam_program.c
* Exécution   : ./exam_program
*
* Ce programme répond à :
*   Exercice 1 : Méthodes d’intégration (Questions a → e)
*   Exercice 2 : Équations différentielles ordinaires (Questions a → c)
* =========================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884
#endif

/* =========================================================================
* EXERCICE 1 : MÉTHODES D’INTÉGRATION
* ========================================================================= */

/* -------------------------------------------------------------------------
* ==== Question 1.a ====
* On cherche à approximer numériquement l’intégrale :
*   I = ∫_a^b f(x) dx
* par la méthode des trapèzes ou de Simpson (ici Simpson).
*
* f(x) doit être au moins 4 fois dérivable.
* -------------------------------------------------------------------------
*/

/* Fonction intégrande : f(x) = 3 / (1 + x^2)
* (sera utilisée plus loin pour calculer π)
*/
double f_integrande(double x) {
    return 3.0 / (1.0 + x * x);
}

/* -------------------------------------------------------------------------
* ==== Question 1.b ====
* Méthode de Simpson composite.
* On découpe [a,b] en 2n sous-intervalles égaux de taille h = (b - a) / (2n)
* et on utilise la formule :
*   I ≈ (h/3)[f(x0) + 4f(x1) + 2f(x2) + ... + 4f(x_{2n-1}) + f(x_{2n})]
* -------------------------------------------------------------------------
*/
double simpson_composite(double a, double b, long n_panel) {
    if (n_panel < 1) n_panel = 1;
    long N = 2 * n_panel; // nombre de sous-intervalles (pair)
    double h = (b - a) / (double)N;
    double sum = f_integrande(a) + f_integrande(b);

    for (long i = 1; i < N; ++i) {
        double x = a + i * h;
        if (i % 2 == 1)
            sum += 4.0 * f_integrande(x);
        else
            sum += 2.0 * f_integrande(x);
    }
    return (h / 3.0) * sum;
}

/* -------------------------------------------------------------------------
* ==== Question 1.c ====
* Calcul "à la main" de π par la méthode de Simpson simple (n = 1) :
*   π = ∫₀^{√3} 3/(1 + x²) dx
* Ici, n=1 correspond à la méthode de Simpson simple (2 sous-intervalles).
* -------------------------------------------------------------------------
*/

/* Cette intégration est réalisée plus bas dans le main pour démonstration. */

/* -------------------------------------------------------------------------
* ==== Question 1.d ====
* Écrire un programme C qui calcule l’intégrale (2) avec la méthode de Simpson
* composite pour différentes valeurs de n, et compare à la valeur exacte π.
*
* Le programme produit un fichier ASCII `resultat.dat` contenant :
*   n   log10(n)   I_num   eps   log10(eps)
*
* (eps = |π - I_num|)
* -------------------------------------------------------------------------
*/

/* Cette fonctionnalité est implémentée dans le main() ci-dessous. */

/* -------------------------------------------------------------------------
* ==== Question 1.e ====
* On donne la commande gnuplot pour tracer log10(eps) en fonction de log10(n),
* et on commente la dépendance théorique (eps ~ n⁻⁴ pour Simpson composite).
* -------------------------------------------------------------------------
*/

/* La commande gnuplot est affichée en console à la fin du calcul. */

/* =========================================================================
* EXERCICE 2 : ÉQUATIONS DIFFÉRENTIELLES ORDINAIRES
* ========================================================================= */

/* -------------------------------------------------------------------------
* ==== Question 2.a ====
* Équation différentielle :
*     dy/dt = F(y, t)
* On donne les formules d’Euler, Heun, Runge-Kutta (ici RK4 utilisée).
* -------------------------------------------------------------------------
*/

/* -------------------------------------------------------------------------
* ==== Question 2.b ====
* Implémentation en C de la fonction :
*     double RK_pas(double y, double t, double h)
* qui effectue un seul pas de la méthode de Runge-Kutta classique (ordre 4).
* -------------------------------------------------------------------------
*/

/* Fonction F(y,t) spécifique à l’équation de la question 2.c */
double F(double y, double t) {
    return sin(y) + cos(t);
}

/* Méthode de Runge-Kutta 4 (RK4) : un seul pas */
double RK_pas(double y, double t, double h) {
    double k1 = F(y, t);
    double k2 = F(y + 0.5 * h * k1, t + 0.5 * h);
    double k3 = F(y + 0.5 * h * k2, t + 0.5 * h);
    double k4 = F(y + h * k3, t + h);
    return y + (h / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}

/* -------------------------------------------------------------------------
* ==== Question 2.c ====
* Résolution numérique de :
*     dy/dt = sin(y) + cos(t)
*     y(0) = 1
* sur l’intervalle [0, 2] avec 101 points uniformes.
* Résultats écrits dans `solution.dat`
* -------------------------------------------------------------------------
*/

/* =========================================================================
* MAIN PROGRAMME
* ========================================================================= */

int main(void) {

    /* ==============================================================
     * SECTION : Exercice 1 (Questions 1.c → 1.e)
     * ============================================================== */
    {
        const double a = 0.0;
        const double b = sqrt(3.0);
        const double exact_pi = M_PI;

        FILE *fout = fopen("resultat.dat", "w");
        if (!fout) {
            fprintf(stderr, "Erreur : impossible d’ouvrir resultat.dat\n");
            return 1;
        }

        fprintf(fout, "# Exercice 1 - Méthode de Simpson composite\n");
        fprintf(fout, "# Colonnes : n  log10(n)  I_num  eps  log10(eps)\n");

        long n = 1;
        while (n <= 1000000L) {
            double I_num = simpson_composite(a, b, n);
            double eps = fabs(exact_pi - I_num);
            double log10n = log10((double)n);
            double log10eps = (eps > 0) ? log10(eps) : -INFINITY;

            fprintf(fout, "%ld  %.6f  %.15e  %.15e  %.6f\n",
                    n, log10n, I_num, eps, log10eps);

            printf("n=%6ld | log10(n)=%.2f | I_num=%.10f | eps=%.3e | log10(eps)=%.2f\n",
                   n, log10n, I_num, eps, log10eps);

            n *= 2; // double à chaque itération
        }

        fclose(fout);
        printf("\n--> Fichier 'resultat.dat' créé (Question 1.d)\n");

        /* Affichage de la commande gnuplot (Question 1.e) */
        printf("\nCommande gnuplot (Question 1.e) :\n");
        printf("  set xlabel 'log10(n)'\n");
        printf("  set ylabel 'log10(eps)'\n");
        printf("  plot 'resultat.dat' using 2:5 with linespoints title 'Erreur Simpson'\n");
        printf("Théoriquement : eps ~ n^-4 (pente ≈ -4 sur le graphique)\n");
    }

    /* ==============================================================
     * SECTION : Exercice 2 (Questions 2.a → 2.c)
     * ============================================================== */
    {
        FILE *fsol = fopen("solution.dat", "w");
        if (!fsol) {
            fprintf(stderr, "Erreur : impossible d’ouvrir solution.dat\n");
            return 1;
        }

        fprintf(fsol, "# Exercice 2 - Méthode de Runge-Kutta (ordre 4)\n");
        fprintf(fsol, "# Colonnes : t_n  y_n\n");

        const double T0 = 0.0;
        const double TEND = 2.0;
        const int Nsteps = 100;     // 100 pas
        const int Npoints = Nsteps + 1; // 101 points
        const double h = (TEND - T0) / Nsteps;

        double t = T0;
        double y = 1.0; // condition initiale

        fprintf(fsol, "%.10f  %.10f\n", t, y);

        for (int i = 0; i < Nsteps; ++i) {
            y = RK_pas(y, t, h);
            t += h;
            fprintf(fsol, "%.10f  %.10f\n", t, y);
        }

        fclose(fsol);
        printf("\n--> Fichier 'solution.dat' créé (Question 2.c)\n");
        printf("Méthode utilisée : Runge-Kutta 4 (RK4)\n");
    }

    printf("\nProgramme terminé avec succès ✅\n");
    return 0;
