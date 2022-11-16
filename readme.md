# Présentation
  Le but de ce TP est de découvrir le parallélisme à travers la création de processus sous UNIX.
  Cette possibilité offerte par le système se révèle utile lorsqu’on cherche à implanter des algorithmes parallèles. On se propose de générer un graphe de précédences à partir d’une expression arithmétique complètement parenthèsée.  

  Exemple : 
   (( A + B) * (C - (D / E)))   aura pour graphe :					
   T1 : M1 :=M2*M3 
   T2 : M2 := A+B 
   T3 : M3 :=C-M4												
   T4 : M4 := D/E 
 
T2<T1 ; T3<T1 ; T4<T3. 

# Génération mono processus 

  La première version du programme générateur  sera basée sur une analyse descendante de l’expression par un seul processus, par un appel d’une fonction récursive génère (). L’un de ses arguments est la chaîne de caractères définissant la sous expression à traiter. Elle aura donc pour rôle de travailler à chaque fois sur une sous expression comme suit : 

  Cherche son opérateur central. Dans l’exemple ci-dessus et pour l’expression entière, l’opérateur principal est ‘*’. 

  Puis génère le nœud (ou tache) correspondante. Dans l’exemple ci-dessus et pour l’expression entière, le nœud est T1. 

  Puis appelle la même fonction pour travailler sur la sous expression de gauche si celle-ci n’est pas un simple opérande (variable ou constante). 

  Puis appelle la même fonction pour travailler sur la sous expression de droite si celle-ci n’est pas un simple opérande (variable ou constante). 

  Puis génère le contenu de la tache. Dans l’exemple ci-dessus et pour l’expression entière, la tache est :  

  T1 : M1 := M2*M3 

  Puis génère la précédence avec la tache générée dans la fonction appelante s’il y a lieu. Dans l’exemple ci-dessus et pour l’expression entière, la tache correspondante à l’opération ‘*’ (T1) n’a pas de tache qui la précède. Par contre, lors du traitement concernant l’opération ‘+’, sa tache correspondante (i.e. T2) précède T1 (i.e. T2<T1 est donc générée). 

  En conclusion, il y a autant d’appels à la fonction génère () que d’opérations dans l’expression. 

# Génération parallèle  

  Dans les appels récursifs précédents, les deux appels sur les sous formules sont logiquement indépendants. Ils peuvent donc être réalisés par deux processus différents, ce qui fournit un schéma de parallélisation de notre générateur. Donc, pour réaliser le travail demandé, le processus père crée deux processus fils dont chacun se charge d’une sous expression, attend leurs terminaisons, achève son travail et conclue. Finalement, il y a autant de processus que d’opération dans l’expression. 