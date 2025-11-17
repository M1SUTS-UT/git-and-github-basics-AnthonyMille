#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_sf_bessel.h>

#define SIGMA0 1e10
#define RC 1.0
#define PI M_PI
#define G 4.30091e-6
#define KPC_TO_KM 3.085677581e16

#define NRPRIME 200
#define RMAX 20.0

typedef struct {
    double x;
    double Kx;
} KPoint;

KPoint *K_table = NULL;
int K_size = 0;

void load_K_table(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (!fin) { fprintf(stderr, "Erreur ouverture %s\n", filename); exit(1); }

    K_size = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fin)) {
        if (buffer[0]=='#'||buffer[0]=='\n') continue;
        K_size++;
    }
    rewind(fin);

    K_table = (KPoint *)malloc(K_size*sizeof(KPoint));
    int i=0;
    while(fgets(buffer,sizeof(buffer),fin)){
        if(buffer[0]=='#'||buffer[0]=='\n') continue;
        if(sscanf(buffer,"%lf %lf",&K_table[i].x,&K_table[i].Kx)==2) i++;
    }
    fclose(fin);
}

double K_interp(double x){
    if(!K_table || K_size==0) return 0.0;
    if(x<=K_table[0].x) return K_table[0].Kx;
    if(x>=K_table[K_size-1].x) return K_table[K_size-1].Kx;
    for(int i=0;i<K_size-1;i++){
        if(x>=K_table[i].x && x<=K_table[i+1].x){
            double x1=K_table[i].x, x2=K_table[i+1].x;
            double y1=K_table[i].Kx, y2=K_table[i+1].Kx;
            return y1 + (y2-y1)*(x-x1)/(x2-x1);
        }
    }
    return 0.0;
}

double sigma_exponentiel(double r){ return SIGMA0*exp(-r/RC);}
double sigma_gaussien(double r){ return SIGMA0*exp(-r*r/(2*RC*RC));}
double sigma_kuzmin_toomre(double r){ return SIGMA0/pow(1+r*r/(RC*RC),1.5);}
double sigma_toomre_n(double r,int n){ return SIGMA0*pow(1+r*r/((2*n-1)*RC*RC),-(n+0.5));}
double sigma_profile(double r,int type,int n){
    switch(type){
        case 1: return sigma_exponentiel(r);
        case 2: return sigma_kuzmin_toomre(r);
        case 3: return sigma_gaussien(r);
        case 4: return sigma_toomre_n(r,n);
        default: return 0.0;
    }
}

double integrand_Meff(double r,double rp,int type,int n){
    return sigma_profile(rp,type,n)*K_interp(rp/r)*rp;
}

double integrate_simpson(double r,double a,double b,int n,int type,int n_toomre){
    if(n%2!=0) n++;
    double h=(b-a)/n;
    double sum=integrand_Meff(r,a,type,n_toomre)+integrand_Meff(r,b,type,n_toomre);
    for(int i=1;i<n;i++){
        double var=a+i*h;
        sum += (i%2==0?2.0:4.0)*integrand_Meff(r,var,type,n_toomre);
    }
    return sum*h/3.0;
}

double M_eff(double r,int type,int n_toomre){
    return 2*PI*integrate_simpson(r,1e-5,RMAX,NRPRIME,type,n_toomre);
}

double mond_acceleration_numeric(double aN,double a0){
    if(aN<=0) return 0.0;
    double a=aN;
    double tol=1e-12;
    for(int i=0;i<100;i++){
        double mu=a/sqrt(a*a+a0*a0);
        double f=mu*a - aN;
        double dmu_da=a0*a0/pow(a*a+a0*a0,1.5);
        double fprime=mu + a*dmu_da;
        double da=-f/fprime;
        a+=da;
        if(fabs(da)<tol) break;
    }
    return a;
}

int main(){
    load_K_table("K_values_simpson.dat");

    double a0_m_s2=1e-10;
    double a0_km_s2=a0_m_s2*1e-3;

    FILE *fout=fopen("vrot_mond_single_a0.txt","w");
    fprintf(fout,"# r(kpc)  v_exp_newt  v_exp_MOND  v_gauss_newt  v_gauss_MOND  v_kuz_newt  v_kuz_MOND  v_toomre_newt  v_toomre_MOND\n");

    int n_toomre=2;
    for(double r=0.1;r<=15.0;r+=0.2){
        double Meff_exp=M_eff(r,1,0);
        double v_exp_newt=sqrt(fmax(0.0,G*Meff_exp/r));
        double aN_exp=(G*Meff_exp/(r*r))/KPC_TO_KM;
        double v_exp_mond=sqrt(mond_acceleration_numeric(aN_exp,a0_km_s2)*r*KPC_TO_KM);

        double Meff_gauss=M_eff(r,3,0);
        double v_gauss_newt=sqrt(fmax(0.0,G*Meff_gauss/r));
        double aN_gauss=(G*Meff_gauss/(r*r))/KPC_TO_KM;
        double v_gauss_mond=sqrt(mond_acceleration_numeric(aN_gauss,a0_km_s2)*r*KPC_TO_KM);

        double Meff_kuz=M_eff(r,2,0);
        double v_kuz_newt=sqrt(fmax(0.0,G*Meff_kuz/r));
        double aN_kuz=(G*Meff_kuz/(r*r))/KPC_TO_KM;
        double v_kuz_mond=sqrt(mond_acceleration_numeric(aN_kuz,a0_km_s2)*r*KPC_TO_KM);

        double Meff_toomre=M_eff(r,4,n_toomre);
        double v_toomre_newt=sqrt(fmax(0.0,G*Meff_toomre/r));
        double aN_toomre=(G*Meff_toomre/(r*r))/KPC_TO_KM;
        double v_toomre_mond=sqrt(mond_acceleration_numeric(aN_toomre,a0_km_s2)*r*KPC_TO_KM);

        fprintf(fout,"%lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf  %lf\n",
            r,v_exp_newt,v_exp_mond,v_gauss_newt,v_gauss_mond,v_kuz_newt,v_kuz_mond,v_toomre_newt,v_toomre_mond);
    }

    fclose(fout);
    free(K_table);
    printf("Fichier 'vrot_mond_single_a0.txt' généré.\n");
    return 0;
}
