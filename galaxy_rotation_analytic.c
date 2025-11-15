#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_sf_bessel.h>  // Fonctions de Bessel modifiées I_n, K_n

//-----------------------------------------------
// Constantes physiques
//-----------------------------------------------
#define SIGMA0 1e10
#define RC 1.0
#define PI M_PI
#define G 4.30091e-6

//-----------------------------------------------
// Paramètres numériques
//-----------------------------------------------
#define NRPRIME 200
#define RMAX 20.0

//-----------------------------------------------
// Structure pour K(x)
//-----------------------------------------------
typedef struct {
    double x;
    double Kx;
} KPoint;

KPoint *K_table = NULL;
int K_size = 0;

//-----------------------------------------------
// Chargement du fichier K(x)
//-----------------------------------------------
void load_K_table(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        printf("Erreur : impossible d’ouvrir %s\n", filename);
        exit(1);
    }

    K_size = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fin)) {
        if (buffer[0] == '#' || buffer[0] == '\n') continue;
        K_size++;
    }
    rewind(fin);

    K_table = (KPoint *)malloc(K_size * sizeof(KPoint));
    if (!K_table) {
        printf("Erreur d’allocation mémoire.\n");
        fclose(fin);
        exit(1);
    }

    int i = 0;
    while (fgets(buffer, sizeof(buffer), fin)) {
        if (buffer[0] == '#' || buffer[0] == '\n') continue;
        sscanf(buffer, "%lf %lf", &K_table[i].x, &K_table[i].Kx);
        i++;
    }

    fclose(fin);
    printf("✅ %d valeurs de K(x) chargées depuis %s\n", K_size, filename);
}

//-----------------------------------------------
// Interpolation linéaire de K(x)
//-----------------------------------------------
double K_interp(double x) {
    if (x <= K_table[0].x) return K_table[0].Kx;
    if (x >= K_table[K_size - 1].x) return K_table[K_size - 1].Kx;

    for (int i = 0; i < K_size - 1; i++) {
        if (x >= K_table[i].x && x <= K_table[i + 1].x) {
            double x1 = K_table[i].x, x2 = K_table[i + 1].x;
            double y1 = K_table[i].Kx, y2 = K_table[i + 1].Kx;
            return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
        }
    }
    return 0.0;
}

//-----------------------------------------------
// Profils de densité de surface
//-----------------------------------------------
double sigma_exponentiel(double r) {
    return SIGMA0 * exp(-r / RC);
}

double sigma_kuzmin_toomre(double r) {
    return SIGMA0 / pow(1.0 + (r * r) / (RC * RC), 1.5);
}

//-----------------------------------------------
// Intégrande pour M_eff
//-----------------------------------------------
double integrand_Meff(double r, double rp, int profile_type) {
    double x = rp / r;
    double Kx = K_interp(x);
    double sigma_value = (profile_type == 1) ? sigma_exponentiel(rp)
                                             : sigma_kuzmin_toomre(rp);
    return sigma_value * Kx * rp;
}

//-----------------------------------------------
// Intégration de Simpson
//-----------------------------------------------
double integrate_simpson(double r, double a, double b, int n, int profile_type) {
    if (n % 2 != 0) n++;
    double h = (b - a) / n;
    double sum = integrand_Meff(r, a, profile_type) + integrand_Meff(r, b, profile_type);

    for (int i = 1; i < n; i++) {
        double var = a + i * h;
        double coeff = (i % 2 == 0) ? 2.0 : 4.0;
        sum += coeff * integrand_Meff(r, var, profile_type);
    }
    return sum * h / 3.0;
}

//-----------------------------------------------
// Calcul de M_eff(r)
//-----------------------------------------------
double M_eff(double r, int profile_type) {
    double rmin = 1e-5, rmax = RMAX;
    double res = integrate_simpson(r, rmin, rmax, NRPRIME, profile_type);
    return 2.0 * PI * res;
}

//-----------------------------------------------
// Fonctions analytiques exactes
//-----------------------------------------------
double v_analytic_kuzmin(double r, double Mtot) {
    double x = r / RC;
    double v2 = (x * x / pow(1.0 + x * x, 1.5)) * (G * Mtot / RC);
    return sqrt(v2);
}

double v_analytic_exponentiel(double r, double Mtot) {
    double y = r / (2.0 * RC);
    double I0 = gsl_sf_bessel_I0(y);
    double I1 = gsl_sf_bessel_I1(y);
    double K0 = gsl_sf_bessel_K0(y);
    double K1 = gsl_sf_bessel_K1(y);

    double v2 = 2.0 * y * y * (I0 * K0 - I1 * K1) * (G * Mtot / RC);
    return (v2 > 0) ? sqrt(v2) : 0.0;
}

//-----------------------------------------------
// Programme principal
//-----------------------------------------------
int main() {
    load_K_table("K_values_simpson.dat");

    FILE *fout = fopen("vrot_comparaison.txt", "w");
    if (!fout) {
        printf("Erreur : impossible de créer le fichier de sortie.\n");
        return 1;
    }

    fprintf(fout, "# r(kpc)   v_exp_num   v_exp_ana   v_kuz_num   v_kuz_ana\n");

    double Mtot = SIGMA0 * 2 * PI * RC * RC; // masse caractéristique

    for (double r = 0.1; r <= 15.0; r += 0.2) {
        double Meff_exp = M_eff(r, 1);
        double Meff_kuz = M_eff(r, 2);

        double v_exp_num = sqrt(G * Meff_exp / r);
        double v_kuz_num = sqrt(G * Meff_kuz / r);

        double v_exp_ana = v_analytic_exponentiel(r, Mtot);
        double v_kuz_ana = v_analytic_kuzmin(r, Mtot);

        fprintf(fout, "%lf  %lf  %lf  %lf  %lf\n",
                r, v_exp_num, v_exp_ana, v_kuz_num, v_kuz_ana);
    }

    fclose(fout);
    free(K_table);
    printf("Fichier 'vrot_comparaison.txt' généré avec valeurs numériques et analytiques.\n");
    printf("ℹPour compiler : gcc galaxy_rotation_analytic.c -o galaxy_rotation_analytic -lm -lgsl -lgslcblas\n");
    return 0;
}
