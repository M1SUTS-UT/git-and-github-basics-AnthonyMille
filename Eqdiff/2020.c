#include <stdio.h>
#include <math.h>

/*************************************************************
* UNIVERSITÉ PAUL SABATIER - M1 SUTS - PHYSIQUE NUMÉRIQUE
* Contrôle Terminal 2020/2021
* Compilation : gcc controle_physnum.c -o controle -lm
*************************************************************/

/*************************************************************
* EXERCICE 1 : MÉTHODE DE SIMPSON 3/8
*************************************************************/

// Question 1.a - Simpson 3/8 simple
double simpson38(double a, double b, double (*f)(double)) {
    double h = (b - a) / 3.0;
    double res = (3.0 * h / 8.0) * (f(a) + 3.0 * f(a + h) + 3.0 * f(a + 2.0 * h) + f(b));
    return res;
}

// Question 1.b - Simpson 3/8 sur plusieurs sous-intervalles [ai, ai+1]
double simpson38List(int n, double L[], double (*f)(double)) {
    double somme = 0.0;
    for (int i = 0; i < n; i++) {
        somme += simpson38(L[i], L[i + 1], f);
    }
    return somme;
}

// Question 1.c - Simpson 3/8 composite avec n sous-intervalles égaux
double simpson38Multi(double a, double b, int n, double (*f)(double)) {
    double h = (b - a) / n;
    double somme = 0.0;
    for (int i = 0; i < n; i++) {
        double ai = a + i * h;
        double bi = ai + h;
        somme += simpson38(ai, bi, f);
    }
    return somme;
}

// Fonction exemple pour 1/x
double f_1surx(double x) {
    return 1.0 / x;
}

// Fonction pour l’intégrale 1/(1+x²)
double f1(double x) { return 1.0 / (1.0 + x * x); }
// Fonction pour l’intégrale 1/(1+x³)
double f2(double x) { return 1.0 / (1.0 + x * x * x); }

/*************************************************************
* EXERCICE 2 : MÉTHODE DE RUNGE-KUTTA 3/8
*************************************************************/

// Question 2.a - Implémentation d’un pas RK3/8
double RK38(double y, double t, double h, double (*F)(double, double)) {
    double k1 = h * F(y, t);
    double k2 = h * F(y + k1 / 3.0, t + h / 3.0);
    double k3 = h * F(y - k1 / 3.0 + k2, t + 2.0 * h / 3.0);
    double k4 = h * F(y + k1 - k2 + k3, t + h);
    double ynext = y + (k1 + 3.0 * k2 + 3.0 * k3 + k4) / 8.0;
    return ynext;
}

// Fonction différentielle pour y'(t) = exp(-y/2 + t)
double F(double y, double t) {
    return exp(-y / 2.0 + t);
}

/*************************************************************
* EXERCICE 3 : ÉQUATION DIFFÉRENTIELLE D’ORDRE 2
*************************************************************/

// Question 3.b - Fonction qui évalue F(u,t)
void F_vect(double u[], double f[], double t) {
    double x = u[0];
    double y = u[1];
    double vx = u[2];
    double vy = u[3];
    double r = sqrt(x * x + y * y);

    f[0] = vx;
    f[1] = vy;
    double facteur = (2.0 + cos(t)) / (r * r);
    f[2] = facteur * x;
    f[3] = facteur * y;
}

/*************************************************************
* PROGRAMME PRINCIPAL - MENU
*************************************************************/

int main() {
    int choix;
    printf("\n=== CONTROLE PHYSIQUE NUMERIQUE ===\n");
    printf("1 - Simpson 3/8 simple et composite\n");
    printf("2 - Runge-Kutta 3/8\n");
    printf("3 - Équation différentielle d’ordre 2\n");
    printf("Choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        double a = 1.0, b = 2.0;
        printf("\n--- Simpson 3/8 : intégrale de 1/x sur [1,2] ---\n");
        for (int n = 1; n <= 256; n *= 2) {
            double I = simpson38Multi(a, b, n, f_1surx);
            printf("n=%3d -> I=%.15f\n", n, I);
        }

        double R = 10.0;
        int n = 20;
        double I1 = simpson38Multi(0.0, R, n, f1);
        double I2 = simpson38Multi(0.0, R, n, f2);
        printf("\n--- Simpson 3/8 : I1 - I2 sur [0,%.1f] ---\n", R);
        printf("Résultat : %.10f\n", I1 - I2);
    }

    else if (choix == 2) {
        printf("\n--- Méthode de Runge-Kutta 3/8 ---\n");
        double y = 0.0, t = 0.0, h = 0.02;
        FILE *f = fopen("RK38_result.txt", "w");
        for (int j = 0; j <= 100; j++) {
            fprintf(f, "%f %f\n", t, y);
            y = RK38(y, t, h, F);
            t += h;
        }
        fclose(f);
        printf("Résultats écrits dans RK38_result.txt\n");
    }

    else if (choix == 3) {
        printf("\n--- Équation différentielle d’ordre 2 : F_vect(u,t) ---\n");
        double u[4] = {1.0, 0.5, 0.0, 1.0};
        double f[4];
        double t = 0.0;
        F_vect(u, f, t);
        printf("F_vect(u,t) = [%.3f, %.3f, %.3f, %.3f]\n", f[0], f[1], f[2], f[3]);
    }

    else {
        printf("Choix invalide.\n");
    }

    return 0;
}
