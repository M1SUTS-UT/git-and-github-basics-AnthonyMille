/*#include <stdio.h>

int main() {

   printf("Bonjour \n");

}*/

/*Programme Plus complet 


#include <stdio.h>
#include <stdlib.h>

//Prototypes des fonctions
int min(int nb1, int nb2);
void affiche_min(int nb1, int nb2);

int main () {     

        //Déclaration de variables

        int a,b;
	int m;


	printf("Entrez deux entiers a et b:\n");
	scanf("%d %d",&a,&b);


	//Appel à la premiere fonction
	m=min(a,b);
	printf("La fonction min dit que le min est %d\n",m);


	//Appel à la 2ème fonction
	affiche_min(a, b);
}


//Premiere fonction qui renvoie une valeur entiere
int min(int nb1, int nb2){
	if (nb1<=nb2) 
		return nb1;
	else 
		return nb2;
}


//Deuxieme fonction qui ne renvoie rien
void affiche_min(int nb1, int nb2){
	if (nb1<=nb2) 
		printf("La fonction affiche_min dit que le min est %d\n",nb1);
	else 
		printf("La fonction affiche_min dit que le min est %d\n",nb2);*/
		
/*Mise en application*/

/*%1

#include <stdio.h>

int main() {
    int i, j;

    // Demande à l'utilisateur de saisir deux entiers
    printf("Entrez la valeur de i : ");
    scanf("%d", &i);

    printf("Entrez la valeur de j : ");
    scanf("%d", &j);

    // Affiche les valeurs saisies
    printf("Vous avez saisi : i = %d et j = %d\n", i, j);

    return 0;
}*/

/*%2
#include <stdio.h>
#include <stdlib.h>

//Prototypes des fonctions

int main() {     

        //Déclaration de variables

        int a,b;
	int m,n,o,p;


	printf("Entrez deux entiers a et b:\n");
	scanf("%d %d",&a,&b);


	//Calcul de la somme 
	m=a+b;
	
	//Calcul de la différence
	n=a-b;
	
	//Calcul du produit
	o=a * b;
	
	//Calcul du rapport 
	p=a/b;

 // Affiche les valeurs saisies
    printf("Le résultat de la somme est : %d\n", m);
    printf("Le résultat de la différence est : %d\n", n);
    printf("Le résultat du produit est : %d\n", o);
    printf("Le résultat du rapport est : %d\n", p);

    return 0;

}*/

/*//3

#include <stdio.h>
#include <stdlib.h>

//Prototypes des fonctions

int main() {     

        //Déclaration de variables

	float x=1.0/3;
	double y=1./3;
	
	printf("Les valeurs sont : x=%.20f\n et y=%.20lf \n" , x, y);
	
 // Affiche les valeurs saisies
 
    return 0;

}*/

//4

#include <stdio.h>
#include <stdlib.h>

//Prototypes des fonctions

int main() {     

        //Déclaration de variables

	int i=1;
	double x=1./3;
	
	printf("Les valeurs sont : i=%d\n et x=%lf \n" , i, x);
	
 // Affiche les valeurs saisies
 
//6
FILE *fich;

fich = fopen("resultats.txt","w");

fprintf(fich, "Les valeurs sont : i=%d\n et x=%lf \n" , i, x);

fclose(fich);




    return 0;
}

