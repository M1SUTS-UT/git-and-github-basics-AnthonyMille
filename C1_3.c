#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 10
int main() {

/*int i=20;

i=1; // initialisation
while (1.0/i > 0.1){
        printf("1/%d vaut %lf \n", i, 1.0/i); 
        i=i+1; //avancée du compteur de boucle
}
int tab[n];

for(int j=0; j<n; j++){
       scanf("%d",&tab[j]);
       }
       

for(int j=n-1; j>=0; j--){ //On doit mettre n-1 car on pars de 0 et on veut 9 element d' ou 10-1=9
       printf("%d\n", tab[j]);
       }
    
 // Affiche les valeurs saisies
 
    return 0;

}*/

int u=5;
int res=1;

int i=1;
i=1;
for(i=1;i<=u;i++){
	res = res * i;
	}
	printf("le résultat est : %d\n", res);
	return 0; // Si on le met pas le code ne s'arretera JAMAIS et donc ne s'execute pas 
	
}
