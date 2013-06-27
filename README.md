MEMBRES:
azzouz Hamdi-Cherif   10501819
jean-michel Le		  11210179
houssem Belhadj Ahmed 11107828
hugo Rossetti		  11211559


VERSION DE LA GRAMMAIRE : version entiere.


FORMAT de SORTIE :

le classement de la table des identifiants est sensible à la casse.

REMARQUE : 

les reels sont stocké dans un float.

YYERROR: un appel a cette fonction termine la compilation => car bison ne semble pas interrompre la regle en cours
		 ce qui dans certain cas conduit nécessairement à réaliser une action avec des variable non initialisé(pointeur à null, etc...)
		 
Interval : type suportés=entier(avec ou sans symbole),booleen,char,enum  à condition de passer par un symbole(forcement constante) du à la definition
		   de la grammaire. de plus les char semble etre gerer par la grammaire comme des strings donc on a choisi pour les interval : char = string
		   de taille 1.
		   Les type interval sont afficher sur la sortie standard bien que non éxigée par le sujet.
		   
Tableau : faute d'avoir trouver une doc prouvant le contraire on n'accepte comme identifiant que un symboleType dont le type est un interval.
Enum : les valeurs possible sont considerés et stockés comme des symboles constants ainsi ils peuvent etre "surchargé" localement par une
	   declaration local au meme titre que les autre symboles ne sachant pas si nous devions l'interdire nous l'avons autoriser et avons
	   supposser existant un operateur montant de porter d'identifiant (c++ = ::identifiant).
Pointeur,Structure et Tableaux : on a modifié la grammaire pour distinguer les lvalues des rvalues. On a ajouté une regle pour " x := @y; ".
		Le nil n'est pas geré car ne sachant pas ce qu'il est permit de faire avec.

Tableau: on considere que l'opcode " x = y [z] " ecrit une adresse dans x car dans le cours on fait ensuite "x1 = x [w]". Ainsi "t[5]=3;" se traduit par
		 "x = t [5];  *x = 3;" en code3@.
		
Structure: Pour les record rvalues on copie la structure puis on calcul l'adresse du champ sur cette copie et on renvoie la la valeur du champs copié égale
			au champ d'origine, certe non optimisé mais fonctionnel.
			
OPCODE_NONE: Il se peut que lorsque rien n'est fait on n'est pas explicitement ajouter une action NOP parcontre aucune instruction n'est effectivement
			 ajouter dans ce cas. Nous avons surtout utiliser NOP pour les etiquettes.
Boucle Conditionnelle: On limite les expressions de test a des expressions booleennes , while 5 , est refuser car 5 est entier, while 5 < 2 --> accepté.

MathExpr: On a certainement eu la main lourde sur les types incompatibles entre eux par manque de temps pour réaliser les tests mais un certain nombre
			sont gerés. La fonction decalage ne gere pas tous les type que peut contenir un record.
			On a tenté le mod( commenté dans actionMath.c ) sans succes et le exp n'est pas réaliser par manque de temps.
