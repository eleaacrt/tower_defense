# OpenGLTemplate

## TODO :


déplacer les classes ColorRGB, Tower, Target, ... dans leur propre fichier

renommer variables et fonctions en utilisant CamelCase

renommer les membres de classe en m_...

"supprimer" les fichier qui ne servent pas

mettre les noms de variable en anglais

# -----------------------------------------------------------------------

créer une classe target / tower

utiliser le "::update" comme dans l'App pour faire avancer les ennemis 

créer une fonction "shot" dans  la tour qui vérifie l'ennemis le plus proche && la portée du tir

# ---------------------------------------------------------------------

## ENNEMIES

-> lors de la création d'un ennemi :

- il s'affiche au point d'entrée 
- tant qu'il n'est pas mort :
  - il avance le long des noeuds
  - jusqu'à la sortie où il disparait
  
SOUCIS DE :
segmentation fault  /Users/elea/Documents/IMAC/cpp/tower_defense/bin/Debug/OpenGL-Template
-> PROBABLEMENT DANS LE GET IN DE LA MAP 
-> OU DANS LE INIT TARGET