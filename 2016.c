Examen de Méthodes Numériques - Réponses et Programmes C
Ce document regroupe les réponses théoriques et les implémentations en langage C des deux sujets d'examen fournis.

Sujet 1 : Contrôle Continu de Méthodes Numériques (Problèmes numériques)
I. Recherche de zéro de f(x) = \cos(x) - x par la méthode de dichotomie

La question est résolue par la fonction dichotomie. J'ai corrigé l'intervalle [1, 3] de l'énoncé car il n'encadre pas la racine de \cos(x) - x = 0 (qui est \approx 0.739). L'exemple utilise [0.5, 1.5].
Programme C (Question II.)
#include <stdio.h>
#include <math.h>

// Définition de la fonction f(x) = cos(x) - x
double f(double x) {
    return cos(x) - x;
}

// Fonction de dichotomie
void dichotomie(double a, double b, double precision) {
    double fa = f(a);
    double fb = f(b);
    double c;
    int iterations = 0;

    printf("\nRésultats de la question II. : Recherche de zéro par dichotomie\n");
    if (fa * fb > 0) {
        printf("Erreur: f(a) et f(b) n'ont pas de signes opposés dans l'intervalle [%.6f, %.6f]. Impossible de garantir la convergence.\n", a, b);
        return;
    }

    while ((b - a) > precision) {
        c = (a + b) / 2.0;
        double fc = f(c);
       
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
            fa = fc;
        }
        iterations++;
    }

    double zero_approx = (a + b) / 2.0;
    double vraie_solution = 0.739085133215; // Racine de cos(x)=x
   
    printf("1. Zéro de la fonction (approximation) dans [%.1f, %.1f]: %.6f\n", a, b, zero_approx);
    printf("2. Nombre d'itérations nécessaires: %d\n", iterations);
    printf("3. Écart à la vraie solution (si l'intervalle est correct): %.10e\n", fabs(zero_approx - vraie_solution));
}

II. Résolution d'une Équation Différentielle

L'équation est transformée en u'(x) = \frac{2(x^2 - 1)}{x^2} \frac{u(x)}{u(x) - 1}. La résolution est implémentée avec la méthode de Runge-Kutta 4 (RK4).

Programme C (Question III.)
#include <stdio.h>
#include <math.h>

#define N 1000   // Nombre de pas
#define X_MIN 1.0
#define X_MAX 10.0
#define U0 2.0   // Condition initiale hypothétique

// 1. La fonction f(x, u) = u'(x) qui définit l'équation
double f_equation(double x, double u) {
    // Gestion de la singularité en u=1 et x=0
    if (fabs(u - 1.0) < 1e-9 || fabs(x) < 1e-9) return 0.0;
    return 2.0 * (x * x - 1.0) / (x * x) * u / (u - 1.0);
}

// 2. Fonction qui permet de calculer u_{n+1} en fonction de u_n (pas RK4)
double rk4_step(double u_n, double x_n, double h) {
    double k1, k2, k3, k4;

    k1 = h * f_equation(x_n, u_n);
    k2 = h * f_equation(x_n + h / 2.0, u_n + k1 / 2.0);
    k3 = h * f_equation(x_n + h / 2.0, u_n + k2 / 2.0);
    k4 = h * f_equation(x_n + h, u_n + k3);

    return u_n + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
}

// 3. Fonction principale qui reconstruit toute la solution
void solve_edo(double x_min, double x_max, int n_steps, double u_initial) {
    double h = (x_max - x_min) / n_steps;
    double x[N + 1];
    double u[N + 1];
    int i;

    x[0] = x_min;
    u[0] = u_initial;

    printf("\nRésultats de la question III. : Résolution numérique par RK4\n");
    printf("Pas h: %.4e | Condition initiale u(%.1f) = %.1f\n", h, X_MIN, U0);
    printf("n=0, x=%.4f, u=%.8f\n", x[0], u[0]);

    for (i = 0; i < n_steps; i++) {
        x[i+1] = x[i] + h;
        u[i+1] = rk4_step(u[i], x[i], h);
       
        if (i < 5 || i > n_steps - 6) {
            printf("n=%d, x=%.4f, u=%.8f\n", i + 1, x[i+1], u[i+1]);
        } else if (i == 5) {
             printf("...\n");
        }
    }
}

III. Calcul d'intégrale par la méthode de Simpson
La question 3 demande de trouver le nombre de points N pour une erreur \epsilon = 10^{-12}. Le calcul est basé sur la formule d'erreur E_n \propto 1/n^4. L'exemple utilise f(x)=x^4 sur [0, 1].

Programme C (Question 3)
#include <stdio.h>
#include <math.h>

// Définition d'une fonction hypothétique pour l'exemple : f(x) = x^4
double f_int(double x) {
    return x * x * x * x;
}

// Question 3. Calcul du nombre de points N pour une erreur epsilon
void calculate_N_simpson(double a, double b, double epsilon) {
   
    // M4 = max |f''''(x)|. Pour f(x)=x^4 sur [0,1], M4=24.
    // Cette valeur dépend de la fonction f(x) du problème non spécifié.
    double M4_hypothetique = 24.0;
    double B_A_5 = pow(b - a, 5);
   
    // n_min^4 >= ( (b-a)^5 * M4 ) / (180 * epsilon)
    double n_min_float = pow(B_A_5 * M4_hypothetique / (180.0 * epsilon), 0.25);
   
    // Le nombre de sous-intervalles (n) doit être pair et supérieur au minimum calculé
    int n_min = (int)ceil(n_min_float);
    if (n_min % 2 != 0) {
        n_min++;
    }

    // Le nombre de points est N = n + 1
    int N_points = n_min + 1;

    printf("\nRésultats de la question 3. : Calcul du nombre de points N (Exemple avec f(x)=x^4 sur [0,1])\n");
    printf("1. Borne de l'erreur |I - I_n| <= (%.2e / n^4)\n", B_A_5 * M4_hypothetique / 180.0);
    printf("2. Nombre de sous-intervalles (n) pour |E_n| <= %.1e: %d\n", epsilon, n_min);
    printf("3. Nombre de points (N=n+1) à utiliser: %d\n", N_points);
}

Fonction main pour le Sujet 1
int main_sujet1() {
    // Q. II. Dichotomie sur [0.5, 1.5] avec précision 1e-6
    dichotomie(0.5, 1.5, 1e-6);

    // Q. III. Résolution EDO par RK4 (hypothèses: X_MIN=1, X_MAX=10, U0=2)
    solve_edo(X_MIN, X_MAX, N, U0);

    // Q. 3. Simpson (hypothèses: f(x)=x^4, a=0, b=1, epsilon=1e-12)
    calculate_N_simpson(0.0, 1.0, 1e-12);

    return 0;
}

Sujet 2 : Réalisation de deux programmes et Questions Théoriques
I. Racine d'un nombre (Méthode de Newton-Raphson)
9. Formule de récurrence (pour f(x)=x^2-2)
10. Calcul des premiers termes (avec x_0 = 1)
*  * 11. Programme C pour Newton-Raphson
#include <stdio.h>
#include <math.h>

#define EPSILON 1e-8
#define MAX_ITER 50

double f(double x) {
    return x * x - 2.0;
}

// I. Racine d'un nombre : Newton-Raphson pour sqrt(2)
void newton_raphson_sqrt2() {
    double x_k = 1.0;
    double x_k_plus_1 = 0.0;
    int k = 0;
   
    printf("\n--- Section I. Racine d'un nombre (Newton-Raphson pour sqrt(2)) ---\n");

    while (k < MAX_ITER) {
        // Formule de récurrence
        x_k_plus_1 = 0.5 * (x_k + 2.0 / x_k);

        // Critère d'arrêt: |x^2 - 2| < 10^{-8}
        if (fabs(f(x_k_plus_1)) < EPSILON) {
            break;
        }

        x_k = x_k_plus_1;
        k++;
    }
   
    printf("11. Approximation de sqrt(2): %.15f\n", x_k_plus_1);
    printf("    Nombre d'itérations: %d\n", k + 1);
}

II. Expansion de l'univers
La résolution passe par le calcul de l'intégrale t(a) = \int_1^a \frac{\sqrt{x}}{\sqrt{1-\mu + \mu/x}} dx. La méthode des trapèzes est utilisée pour l'intégration numérique.
12. Programme C pour l'Expansion de l'univers
#include <stdio.h>
#include <math.h>

#define MU 0.3
#define N_TRAPEZES 10000

// La fonction à intégrer f(a) = dt/da
double integrand_t_of_a(double a) {
    // f(a) = sqrt(a) / sqrt(1 - mu + mu/a)
    return sqrt(a) / sqrt(1.0 - MU + MU / a);
}

// Méthode des trapèzes pour calculer t(a)
double t_of_a_trapezoidal(double a_end, int n) {
    if (a_end <= 1.0) return 0.0;
   
    double a_start = 1.0;
    double h = (a_end - a_start) / n;
    double integral = 0.0;
    int i;
   
    for (i = 1; i < n; i++) {
        integral += integrand_t_of_a(a_start + i * h);
    }
   
    // Formule des Trapèzes composite
    integral = h * ( (integrand_t_of_a(a_start) + integrand_t_of_a(a_end)) / 2.0 + integral );
   
    return integral;
}

// Fonction principale pour la simulation de l'expansion
void expansion_univers() {
    int i;
    int num_a_values = 100;
    double a_max = 5.0;
    double da = (a_max - 1.0) / num_a_values;
    double current_a;
    double current_t;

    printf("\n--- Section II. Expansion de l'univers (Calcul de t(a)) ---\n");
    printf("12. Programme C - Affichage du facteur d'échelle a(t):\n");

    for (i = 0; i <= num_a_values; i++) {
        current_a = 1.0 + i * da;
        current_t = t_of_a_trapezoidal(current_a, N_TRAPEZES);
       
        // Affichage partiel
        if (i % 10 == 0 || i == num_a_values) {
            printf(" a = %.4f | t = %.8f\n", current_a, current_t);
        }
    }
}

Fonction main pour le Sujet 2
int main_sujet2() {
   
    // Appel du programme I.
    newton_raphson_sqrt2();

    // Appel du programme II.
    expansion_univers();

    return 0;
}

Réponses Théoriques (Sujet 2)

III. Analyse d'un programme (Questions 13-16)
* 13. À quoi sert-il ? Quelle équation résout-il ? À quel problème physique cette équation correspond-elle ?

   * Sert à calculer numériquement le zéro d'une fonction.
   * Résout l'équation \mathbf{x^2 - 2 = 0}.
   * Problème : Calcul de la racine carrée de 2 (\sqrt{2}), problème mathématique fondamental.

* 14. Quelle méthode numérique est utilisée ici ? Quel est son ordre ?
   * Méthode de Newton-Raphson (ou des tangentes).
   * Ordre : 2 (convergence quadratique).

* 15. À quoi correspondent physiquement les deux composantes du tableau X ?

   * Elles correspondent à l'approximation courante de la racine (x_k) et à l'approximation précédente (x_{k-1}), utilisées pour la récurrence et/ou le critère d'arrêt.

* 16. À quoi sert la grande boucle for(){} la plus externe ?

   * Elle contrôle le processus itératif en appliquant la formule de récurrence (x_{k+1} = g(x_k)) et en vérifiant le critère d'arrêt (précision ou nombre maximal d'itérations).

Méthodes et performances (Questions 1-8)

* 1. Méthodes de Newton-Cotes composites :

Servent au calcul approché d'intégrales définies. Elles subdivisent l'intervalle d'intégration en sous-intervalles et appliquent une formule simple (basée sur l'interpolation polynomiale) sur chaque sous-intervalle avant de sommer.

* 2. Ordres de précision :

   * Rectangles : \mathbf{1} (Exact pour polynômes de degré 0).
   * Trapèzes : \mathbf{2} (Exact pour polynômes de degré 1).
   * Simpson : \mathbf{4} (Exact pour polynômes de degré \leq 3).

* 3. Évolution de l'erreur sur un graphique log-log (n \geq 10^6) :

L'erreur \log(E) est une droite de pente -\alpha. À très grand n, l'erreur va stagner ou augmenter en raison de l'accumulation des erreurs d'arrondi (ou erreurs numériques), qui dominent l'erreur de troncature (erreur théorique).

* 4. Plus rapide pour une précision donnée (rectangles vs trapèzes) : La méthode des Trapèzes est beaucoup plus rapide, car son ordre de précision \alpha=2 est supérieur à celui des rectangles (\alpha=1). Le nombre de points n requis pour une précision \epsilon est proportionnel à 1/\sqrt{\epsilon} (Trapèzes) au lieu de 1/\epsilon (Rectangles).

* 5. Plus rapide pour un nombre de points donné (trapèzes vs Simpson) :

La méthode de Simpson est la plus rapide/efficace, car son ordre de précision \alpha=4 est le plus élevé (E_{simp} \propto 1/n^4).

* 6. Intégration de f(x) = 1 + \cos(2\pi x) sur [0, 1] :

Le résultat I=1 par la méthode des rectangles est exact (à la précision machine) car la fonction f(x) est périodique de période T=1. La somme des erreurs locales due à la méthode des rectangles s'annule exactement sur une période complète.

* 7. Formule générale de Simpson (composite) :
  
* 8. Méthode de Heun :

C'est une méthode pour la résolution numérique d'équations différentielles ordinaires (EDO). Son ordre est \mathbf{2}. C'est une méthode de type prédicteur-correcteur (Runge-Kutta d'ordre 2).
