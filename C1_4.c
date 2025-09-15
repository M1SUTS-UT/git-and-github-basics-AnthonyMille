#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 10

/*int min(int nb1, int nb2);
void affiche_min(int nb1, int nb2); // prototypes des fonctions

int min(int nb1, int nb2){
        if (nb1<=nb2)
                return nb1;
        else
                return nb2;
}

et

void affiche_min(int nb1, int nb2){
        if (nb1<=nb2)
                printf("La fonction affiche_min dit que le min est %d\n",nb1);
        else
                printf("La fonction affiche_min dit que le min est %d\n",nb2);
}

void f(double tab[10]){
     int i;
     for (i=0;i<10;i++){
         tab[i]=i*i;
     }
}

void f(double *tab){ 
     int i;
     for (i=0;i<10;i++){
         *tab[i]=i*i;
     }
}*/

/*
//Fonction Factorielle 

//Def de la fonction
int factorielle(int a){ //Obligé de mettre le type(int, double, float, long..)
	int res=1;
	for(i=1;i<=u;i++){
		res = res * i;
		}
	return res;
	
}

int main(){ //On appelle la fonction dans le terminal
	int a=5 ;//On définit notre variable
	int resultat ; 
	
	resultat = factorielle(a); //ne pas marqué le type!!!
	printf("le résultat est : %d\n", resultat);
	
	return 0; //Retourne rien mais oblier gde return car y'a int
}*/

/*
int exponentiel(int a){ 
	res=exp(a)
	return res;*/
	
//On peut également écrire plus simplement

float exponentiel(int a){ //On met float car une exp est toujours décimale
	return exp(a);
	
}

int main(){ //On appelle la fonction dans le terminal
	int a=5 ;//On définit notre variable
	float resultat ; 
	
	resultat = exponentiel(a); //ne pas marqué le type!!!
	printf("le résultat est : %8.5f\n", resultat); // %8.5f car c'est float (8 caractères en tout et 5 chiffres après la virgule)
	
	return 0; //Retourne rien mais oblier gde return car y'a int
}
	
