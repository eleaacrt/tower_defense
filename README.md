# RAPPORT DE PROJET
Eléa CRUNCHANT & Angèle DOUET

## INTRODUCTION
Dans le cadre du deuxième semestre de notre première année à l’IMAC, nous avons à l'occasion de réaliser un projet de jeu. Ce projet alliait les deux modules  Programmation et Algorithmique ainsi que Synthèse d’Image.

Par binôme ou trinôme nous devions réaliser un jeu de Tower Defense dans lequel nous devions : 
- implémenter une MAP de jeu, 
- créer des vagues d’ennemis,
- implémenter un système de tours qui attaquent les ennemis pour les empêcher d’atteindre leur cible,
- créer un système de monnaie pour payer les tours

Nous avons donc décidé de réaliser notre projet autour d’une histoire de fantômes qui chercheraient à dérober un trésor que nous devons protéger. 

## FONCTIONNEMENT DU JEU
Comme expliqué précédemment, le but du jeu est de protéger un trésor. Ce trésor se compose de 5 gemmes bleues qui correspondent aux 5 vies du joueur. Lorsqu’un fantôme atteint le trésor, le joueur perd un gemme. S'il n’a plus de gemme, il perd la partie. 

Il existe deux types de fantômes, les fantômes roses qui possèdent 50 vies, ont une vitesse de 3 et une valeur de 20$
Les bleus, quant à eux, possèdent 20 vies, sont légèrement plus rapides que les roses avec une vitesse de 4 et ont une valeur de 10$.

Lorsqu’un fantôme meurt, la valeur de ce dernier entre dans le porte monnaie du joueur qui gagne de l’argent pour pouvoir ensuite poser ses tours.

Les fantômes cherchent à tout prix à voler le trésor, ils empruntent donc le chemin le plus court jusqu’au trésor à partir de l’endroit où ils apparaissent. 

Il existe deux points d’entrée différents représentés par des portails violets.

Évidemment, le joueur se doit de protéger son trésor et pour ce faire, il peut poser des tours qui vont attaquer les fantômes. Pour pouvoir placer une tour, le joueur doit avoir assez d’argent, sinon elle ne se sélectionne pas . Le prix d’une tour est indiqué sur cette dernière. 

Il y a 5 niveaux. Chacun de ces niveaux correspond à une vague de fantômes. À la fin de chaque niveau, toutes les tours se suppriment MAIS ATTENTION, le porte monnaie garde sa valeur et les gemmes ne se réinitialisent pas. Il faut donc faire attention à bien gérer son argent pour éviter de se retrouver à sec pour les vagues qui suivent…

Le joueur gagne la partie s’il réussit à éliminer tous les fantômes, ou en tous cas, s’il lui reste au moins un gemme dans son trésor à la fin des 5 niveaux.

Un joueur peut à tout moment quitter le jeu en cliquant sur la touche [esc] de son clavier et le mettre en pause en cliquant sur [space].

## ORGANISATION
Pour nous organiser dans notre dossier de projet, nous avons utilisé le template que Enguerrand DESMET nous a fourni : 
/ data : contient tous les fichiers ITD  permettant d’initialiser les tours, la map, les ennemis et les vagues
/ images : contient toutes les textures du jeu
/ lib : contient les librairies utilisées (sil::Image et la librairie de texte)
/ pdf : contient le pdf de consigne du projet
/ src : contient tous les fichiers sources permettant de faire fonctionner le jeu ( .hpp & .cpp)

Pour l’organisation de nos fichiers sources, nous avons essayé de faire au plus simple et au plus clair : 
Les fichiers Config_ servent à lire les fichiers .itd qui configurent les éléments principaux de notre jeu. Nous avons un fichier Config par .itd.

Nous avons créé un fichier Log qui nous permet d’afficher des Erreurs où de nous aider dans le Débug : 
 
C’est dans le fichier App que tout notre jeu est initialisé. Nous y avons importé tous nos éléments et ils y sont appelés les uns après les autres

Les fichiers Target et Wave nous ont permis de gérer les fantômes, les fichiers Tower de gérer les tours, et les fichiers Map et Tile d’initialiser respectivement la Map et les tuiles.

Le fichier ColorRGB est un fichier qui nous permet de gérer les couleurs plus facilement et notamment de pouvoir les afficher dans la console et les comparer entre elles.

Les fichiers Graph et Nodes nous ont permis de gérer le graphe du chemin à suivre pour nos fantômes.

Et enfin, UserInterface nous a permis de réaliser tout le visuel de notre jeu : l’affichage des vies et des textes en général.

## LES DIFFICULTÉS RENCONTRÉES
Durant la réalisation de ce projet, nous avons rencontré de nombreuses difficultés. Presque à chaque fois que nous voulions implémenter une nouvelle fonctionnalité, l’Application nous détectait des problèmes là où il n’y en avait pas auparavant.  

### AFFICHAGE DE LA MAP
La première chose que nous avons implémentée était l’affichage de notre jeu. Mais avant de commencer à réfléchir à comment placer les tuiles, il nous a fallu comprendre : comment faire pour lire le fichier .itd.

Nous avons demandé de l’aide au papa d’Eléa pour qu’il nous explique comment la lecture de fichier fonctionne. Il nous a renvoyé vers un site : udacity.com et nous a aidé pour la lecture du premier fichier itd : ItdMap que nous avons ensuite réutilisé sur les autres fichiers .itd. 

Nous avons ensuite réussi assez facilement à afficher les tuiles correctement et à implémenter les coins et l’orientation des tuiles. Cependant, nous nous sommes rendues compte que lorsqu’on attendait trop longtemps avant de quitter notre jeu, nos ordinateurs se mettaient à souffler fort; on se doutait qu’ils faisaient trop de calculs inutiles. 

Nous nous sommes alors aperçues qu’à chaque appel de la fonction pour afficher la map, notre application créait un tableau de Tuiles qu’il analysait ensuite les unes après les autres. Il faisait toutes les comparaison pour chacune d’entre elles et affichait une tuile, puis recommençait ce même processus. Nous avons alors réalisé que nous pouvions simplement faire ces calculs une seule fois lors du setup de l’Application puis réutiliser ce tableau. Cela a réduit considérablement nos calculs et notre jeu fonctionnait de nouveau correctement.

### LES TEXTURES
Lorsque nous avons voulu commencer à implémenter les fantômes, le terminal nous affichait une erreur nous indiquant que nous étions en manque de mémoire. 

Après avoir discuté de ce problème avec Maxence DUPUIS, il nous a expliqué qu’à chaque fois que nous voulions afficher une tuile, nous générions une nouvelle texture et donc ça nous prenait toute la mémoire de nos ordinateurs. Et évidemment, dès que nous avons souhaité ajouter des ennemis, ces derniers devaient afficher une nouvelle texture à chaque mouvement. La mémoire a donc très vite été saturée. 

Il nous a expliqué qu’il fallait créer une fonction qui se lancerait lors du setup de l’application. Cette fonction nous permettrait de générer un tableau de textures et nous n’aurions plus qu’à aller chercher la texture souhaitée dans ce tableau. 

### FAIRE AVANCER LES FANTÔMES
Il nous a fallu un certain temps avant de comprendre comment faire avancer les ennemis. C’est à force de tâtonnement que nous avons pu arriver à bout de cette fonctionnalité. 

À l’origine, nous avions pensé la fonction Target::move( ) de telle sorte que nous avions un point (x, y) qui correspondait à la position de Target (notre fantôme) et une deuxième position (x, y) qui correspondait à la position de notre noeud d'arrivée. 

Nous voulions faire une comparaison entre les deux positions et tant qu’elles n’étaient pas égales, nous faisions avancer la cible selon x ou y.
Avec cette méthode, nous n’avons pas du tout réussi à faire avancer nos fantômes et nous ne savons toujours pas pourquoi. 

Nous avons donc choisi une nouvelle approche. À la place d’essayer d’atteindre les positions, nous avons implémenté une distance entre le fantôme et le nœud qu’il doit atteindre : 
- tout d’abord, nous vérifions s’il n’est pas mort ou arrivé;
- ensuite, nous récupérons la position du nœud cible;
- nous calculons la distance de notre fantôme par rapport à ce nœud;
- nous orientons notre fantôme;
- enfin, nous regardons si le parcours doit s’effectuer selon les x ou les y.

### SÉLECTIONNER UNE TOUR ET LA PLACER
Pour pouvoir afficher nos tours, nous avons décidé de les afficher avec leur prix sur le côté de notre map. Ensuite, à l’aide de son curseur, le joueur clique sur l’une des tours et celle-ci apparaît alors dans la map. Le joueur n’a plus qu’à placer son curseur à l’endroit où il souhaite placer la tour et à cliquer de nouveau pour la fixer à cet emplacement.

Nous nous sommes vite aperçues que nous avions des problèmes de comparaison. En effet, la _width et la _height de nos fenêtres étaient de 1280 par 720 pixels alors que pour effectuer une translation, cela se faisait à partir de la _viewSize initialisée à 25 (soit 1/25 de la hauteur de nos fenêtres). 

Or le placement des tours se fait à partir de la _viewSize tandis que la position du curseur se fait à partir de la _width et de la _height. Aussi, nous nous sommes rendues compte que pour les fonctions d’openGL comme la translation, l’origine du repère est au centre de l’écran, ce qui n’est pas le cas pour le curseur, qui lui, est en haut à gauche de l’écran.

Enfin, le nombre de pixels dans une fenêtre change selon si l’on est sous MacOS ou sous Windows. Ainsi, si le code marchait sur l’un, il ne fonctionnait plus sur l’autre.

Nous avons de nouveau demandé de l’aide à Maxence DUPUIS pour qu’il nous explique comment lui avait procédé pour pallier ces problèmes. Il nous a alors expliqué qu’il avait normalisé son curseur pour que sa fenêtre soit définie sur (-1, 1), en faisant attention de normaliser sur la taille de la fenêtre et non du Frame Buffer. En effet, cela permet d’éviter les problèmes entre les différences de résolution de pixels entre un écran Windows et un écran Mac. Nous avons donc adapté cela à notre code et à notre _viewSize qui est de 25 contrairement à la sienne qui est à 2.

Actuellement, nous avons toujours un léger décalage entre notre curseur et la tour. Nous ne savons malheureusement pas d’où provient ce problème. Ce décalage n’empêchant pas de jouer correctement à notre jeu, nous avons préféré continuer de développer le reste des fonctionnalités plutôt que de nous attarder sur ce problème.

Cependant, ce petit décalage nous a empêché d’implémenter la fonctionnalité qu’une tour ne puisse pas être posée sur un chemin, un point d’entrée ou de sortie. Nous voulions analyser la position du curseur et vérifier la tuile qui se trouve en dessous. Or la tuile se trouvant en dessous du curseur n'étant pas toujours la bonne, cela ne fonctionnait pas correctement.

### FAIRE PERDRE DES VIES AUX ENNEMIS
Enfin, la dernière principale difficulté que nous avons rencontrée est l'interaction entre les tours et les fantômes. 

En effet, les points de vie des fantômes diminuaient dans la console, mais ces derniers ne mourraient pas et ne disparaissaient pas de la map. 

C’est finalement en créant une fonction qui agit directement sur le fantôme que nous avons réussi à pallier ce problème. À la place que cela soit la tour qui attaque un ennemi, c’est un ennemi qui est attaqué par une tour.

Nous avons finalement fait les vérifications à partir des points de vie de l’ennemi plutôt que de vérifier quel était l’état de la variable isDead( ).

## LES FONCTIONNALITÉS SUPPLÉMENTAIRES
La quantité de travail sur ce projet ayant été très conséquente, nous n’avons malheureusement pas pu implémenter tout ce que nous aurions aimé.
Voici donc une petite liste de fonctionnalités que nous aurions aimé mettre en place si nous avions eu plus de temps pour réaliser ce projet : 
- des tirs visibles pour les tours  : ajouter un visuel d’une texture de tir qui partirait des tours jusqu’à l’ennemi ciblé;
- animation des fantômes : actuellement les fantômes ne bougent pas quand ils avancent, ils ne suivent pas la direction qu’ils prennent, cela ajouterait de la vie au jeu et permettrait une meilleure immersion;
- une jauge de vie qui se déplacerait au-dessus des ennemis : bien que nous ayons ajouté à la droite de la map, une liste avec les points de vie de chaque fantôme, il est difficile de savoir à qui appartient quelle jauge;
- ne pas pouvoir placer des tours sur les chemins : comme expliqué précédemment, nous n’avons pas trouvé de solution à ce décalage avec le curseur.

## BILAN
Bien que nous ayons rencontré de nombreuses difficultés, nous sommes fières du jeu que nous avons réussi à développer. 

Nous avons réussi à faire un jeu fonctionnel et jouable malgré les quelques bugs qui peuvent survenir. Nous avons aussi réussi à créer une ambiance dans le jeu avec une esthétique qui nous parle à toutes les deux. 

Nous avons toutes les deux beaucoup appris tout au long de ce projet et nous sommes surtout très fières du résultat final et nous espérons que le jeu vous plaira tout autant.

*Qu’attendez-vous ? Les fantômes sont déjà en chemin…*
