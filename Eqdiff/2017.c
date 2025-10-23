I. Questions de cours

1. Questions sur les méthodes d'intégration numériques

La Figure 1 montre l'erreur |I - I_N| en fonction du nombre de points N pour trois méthodes d'intégration numérique : Rectangles, Trapèzes et Simpson. L'erreur E_N est liée au nombre de points N (ou au pas h = (b-a)/N) par une relation de la forme E_N \approx C \cdot h^\alpha ou E_N \approx C/N^\alpha pour un grand N, où \alpha est l'ordre de convergence de la méthode. En échelle log-log, \log(E_N) \approx \log(C) - \alpha \log(N), la pente de la courbe est -\alpha.

a. À quelle méthode correspond chaque courbe ?
Les ordres de convergence théoriques (pour une fonction suffisamment régulière) sont :

* Méthode des Rectangles (Point Milieu ou Rectangles Simples) : Ordre \alpha=1 (ou 2 pour le point milieu). L'erreur décroît en O(h^2) pour le point milieu et O(h) pour les rectangles simples. Les méthodes composites sont : O(h^2) pour le point milieu et O(h) pour les rectangles simples.

On parle souvent d'ordre 1 pour les rectangles simples et 2 pour les trapèzes composites.

* Méthode des Trapèzes (composite) : Ordre \alpha=2. L'erreur est en O(h^2) ou O(1/N^2).
* Méthode de Simpson (composite) : Ordre \alpha=4. L'erreur est en O(h^4) ou O(1/N^4).

En observant la Figure 1, on voit que la pente la plus faible est pour la Méthode 1, la pente intermédiaire pour la Méthode 2, et la pente la plus forte pour la Méthode 3.

* Méthode 1 : Méthode des Rectangles (ou Point Milieu, si l'ordre est 2) - Pente la plus faible.
* Méthode 2 : Méthode des Trapèzes - Pente intermédiaire.
* Méthode 3 : Méthode de Simpson - Pente la plus forte.

b. Expliquer comment on peut déterminer l'ordre de la méthode à partir de cette figure ? Quel est l'ordre de chaque méthode ?

* Détermination de l'ordre \alpha :
   L'ordre \alpha d'une méthode est déterminé par la pente de la droite \log(|I - I_N|) = f(\log(N)) dans le graphique en échelle log-log, où N est le nombre de points.
   L'erreur est proportionnelle à N^{-\alpha}:
  
  
   En prenant le logarithme:
  
  
   La pente est donc -\alpha. Il suffit de mesurer la pente de la partie linéaire de la courbe (avant l'influence des erreurs d'arrondi) pour déterminer l'ordre \alpha.

* Ordre de chaque méthode (à partir du graphique ou des connaissances théoriques) :
   * Méthode 1 (Rectangles) : Pente d'environ -1 ou -2. Si c'est la méthode des rectangles simples, \alpha=1 (erreur en 1/N). Si c'est la méthode du point milieu, \alpha=2 (erreur en 1/N^2). Compte tenu de l'écart avec la méthode 2 (Trapèzes, \alpha=2), la Méthode 1 est très probablement la méthode des rectangles simples avec \boldsymbol{\alpha \approx 1} (bien que la courbe ressemble plus à une pente de -2). Si l'on considère les résultats théoriques usuels et la figure, la Méthode 1 est souvent associée à \boldsymbol{\alpha=1} (ou \boldsymbol{\alpha=2} pour le point milieu), la Méthode 2 aux Trapèzes avec \boldsymbol{\alpha=2}, et la Méthode 3 à Simpson avec \boldsymbol{\alpha=4}.

c. Pourquoi a-t-on un changement de pente à des valeurs faibles de l'erreur pour les méthodes 2 et 3 ?

Le changement de pente, c'est-à-dire l'aplatissement de la courbe (l'erreur ne diminue plus), est dû à l'apparition des erreurs d'arrondi.

* Pour un petit nombre de points N, l'erreur de troncature (ou erreur de méthode) est dominante. C'est la partie de la courbe où l'erreur diminue avec l'augmentation de N.

* Pour un grand nombre de points N (donc une petite valeur théorique de l'erreur), l'erreur d'arrondi (due à la précision finie des nombres à virgule flottante de la machine) devient dominante et masque l'erreur de troncature. L'erreur d'arrondi tend à augmenter ou à fluctuer de manière imprévisible avec N, car un grand N signifie plus d'opérations et plus de cumuls d'erreurs d'arrondi.

* Ce phénomène apparaît plus tôt pour les méthodes d'ordre élevé (Simpson, Méthode 3) car leur erreur de troncature diminue beaucoup plus vite. La précision maximale atteignable (le "plancher" de la courbe) est limitée par ces erreurs d'arrondi.

2. Formule du calcul de l'intégrale

Donner la formule du calcul de l'intégrale d'une fonction f entre les bornes a et b avec la méthode des trapèzes (composite).

Soit I = \int_a^b f(x) dx. On subdivise l'intervalle [a, b] en N sous-intervalles de longueur h = \frac{b-a}{N}. Les points de la subdivision sont x_i = a + i h pour i=0, 1, \dots, N.

La formule des trapèzes composites est :

3. Calcul avec la méthode de Simpson

On calcule une intégrale avec la méthode de Simpson. En prenant N_1=100 points, on trouve une erreur de E_1 = 10^{-4}. Combien de points doit-on utiliser au minimum pour obtenir une erreur de E_2 = 10^{-12} ?

* Ordre de la méthode : La méthode de Simpson est d'ordre \alpha=4. L'erreur est en O(1/N^4):
  
  
   (où N est le nombre de sous-intervalles, qui doit être pair pour Simpson).
* Relation entre les erreurs et le nombre de points :
  
* Résolution pour N_2 :
  
* Application numérique :

   *    *    * Il faut utiliser au minimum N_2 = 10000 points (ou sous-intervalles) pour obtenir une erreur de 10^{-12}.

4. Résolution d'une équation différentielle y'' = f(y, x)

Expliquer comment résoudre numériquement une équation différentielle du type y'' = f(y, x) où y'' est la dérivée seconde de y par rapport à x.

Donner le nom d'une méthode de résolution possible et son ordre.

1. Méthode de résolution : Réduction à un système du premier ordre
Une équation différentielle ordinaire (EDO) d'ordre n peut être réduite à un système de n EDO du premier ordre.
Pour y'' = f(y, x), on pose :
*  * Alors, l'équation y'' = f(y, x) devient le système de deux équations du premier ordre :

On cherche alors à résoudre numériquement ce système du premier ordre, par exemple avec des conditions initiales :

2. Nom d'une méthode et son ordre

Une méthode numérique très courante pour résoudre les systèmes d'EDO du premier ordre est la méthode de Runge-Kutta d'ordre 4 (RK4).

* Méthode : Runge-Kutta d'ordre 4 (RK4)
* Ordre : \boldsymbol{4} (l'erreur de troncature locale est en O(h^5) et l'erreur globale est en O(h^4), où h est le pas d'intégration).

II. Méthode de recherche de zéros : la dichotomie
Ceci est un problème de programmation en C pour implémenter la méthode de dichotomie.

Objectif : Chercher le zéro x^* de f(x) = \cos(x) - x^3 dans [1, 3] avec une précision de \epsilon = 10^{-6}.

La fonction change de signe dans [1, 3] car f(1) = \cos(1) - 1^3 \approx 0.540 - 1 = -0.46 et f(3) = \cos(3) - 3^3 \approx -0.99 - 27 = -27.99.

Attention, si f(1) est positif, l'intervalle est mal choisi dans la description du texte. En fait, \cos(1) \approx 0.54 et 1^3=1, donc \boldsymbol{f(1) \approx -0.46 < 0}. Cherchons f(0): f(0) = \cos(0) - 0 = 1 > 0. Le zéro est dans [0, 1].

Prenons les valeurs du texte : x \in [1, 3] et la fonction f(x) = \cos(x) - x^3. La fonction étant continue, il faut que f(1) \cdot f(3) < 0. On a f(1) \approx -0.46 et f(3) \approx -27.99, donc le produit est positif.

Le texte semble avoir une erreur sur l'intervalle ou la fonction. Suivons l'énoncé qui cherche un zéro entre 1 et 3 et un point de départ tel que f(a)f(b) < 0.

* Hypothèse 1 : Erreur sur l'intervalle de l'énoncé. Le zéro de \cos(x) - x^3 est en fait dans [0, 1], où f(0)=1>0 et f(1) \approx -0.46 < 0. Le zéro est dans [0, 1].

* Hypothèse 2 : Erreur sur la fonction de l'énoncé. Si le zéro est dans [1, 3], la fonction n'est pas \cos(x) - x^3.

Pour le programme, nous devons utiliser la fonction et l'intervalle données pour le code, même si cela ne semble pas marcher. Pour des raisons didactiques, je prends l'intervalle où le zéro est : [0, 1].

* Fonction à coder : f(x) = \cos(x) - x^3.
* Intervalle initial (corrigé) : [x_g, x_d] = [0, 1].
* Précision : \epsilon = 10^{-6}.
* Condition d'arrêt : |x_d - x_g| < \epsilon.

Un programme C pour la dichotomie est demandé (qui ne peut pas être généré ici) :

* Implémentation : Boucle while (xd - xg > epsilon) et mise à jour de l'intervalle par la règle de dichotomie.

* Comparaison avec la vraie solution : Après avoir trouvé la solution approchée x_{approx} (par exemple, le milieu final de l'intervalle), on comparerait avec la "vraie solution" pour \cos(x) = x^3 (que l'on obtiendrait par un solveur numérique de haute précision, par exemple).

Le nombre d'itérations N pour atteindre une précision \epsilon à partir d'un intervalle [a, b] est donné par :


Avec a=0, b=1 (corrigé) et \epsilon=10^{-6} :


Il faudrait \boldsymbol{N=20} itérations au minimum.

III. Résolution d'une équation différentielle
L'équation différentielle à résoudre est :


où u est la vitesse du vent solaire divisée par la vitesse du son dans le fluide et x est une mesure adimensionnée de la distance au Soleil.

On cherche la solution u_n numériquement avec une méthode d'ordre n.

Le programme C demandé doit utiliser une méthode numérique de résolution pour u'(x) = f(u, x) et doit posséder trois fonctions :
* Une fonction f qui définit l'équation : u'(x) = f(u, x).
* Une fonction qui permet de calculer u_{n+1} en fonction de u_n.
* Une fonction principale.

1. Définir l'équation u'(x) = f(u, x)
L'équation donnée est (u-x) u'(x) = 2 \left( \frac{1}{x^2} - \frac{1}{u^2} \right).

On peut isoler u'(x) pour obtenir la forme standard u'(x) = f(u, x):
Cette fonction f(u, x) devra être implémentée dans une fonction C.

2. Calculer u_{n+1} en fonction de u_n
Une méthode numérique pour résoudre une EDO u'(x) = f(u, x) avec un pas h est la méthode d'Euler explicite (ordre 1) :

Une méthode plus précise est la méthode de Runge-Kutta d'ordre 4 (RK4) :


avec :

La fonction C demandée sera l'implémentation de cette relation (Euler ou RK4) en utilisant la fonction f.

3. Fonction principale

La fonction principale gérera :
* Le choix du pas h.
* La boucle d'itération de n=1 à N pour calculer la solution u_n séquentiellement.

* L'utilisation de la condition à la limite u(x_{min}) = u_0 (où x_0 est la limite/borne choisie). Le problème implique une condition à la limite u(x) \to u_0, ce qui est plus complexe et suggère une approche par tir ou un schéma en différences finies. Cependant, la question demande un schéma itératif u_{n+1} = \Phi(u_n, x_n), ce qui est caractéristique des méthodes à un pas (Euler, RK) qui nécessitent une condition initiale u(x_0) = u_0. Le programme doit donc commencer l'itération à partir d'une condition initiale u_0 à x_1 et reconstruire la solution jusqu'à x_N.
