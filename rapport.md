# Parallélisme intra-processeur - OpenMP

## Exercice 2 - Premier test

### Écrire un programme C qui se divise en 4 tâches openMP, chacune affichera son numéro de rang
![2_1](assets/2_1.png)


## Exercice 3 - Variable privé

### Modifiez private par firstprivate et observer le résultat – déduction ?
*private* ne donne pas la garantie que la valeur est bien initialisé quand les Thread démarre tandis que la directive *firstprivate* nous assure que la valeur est initialisé

**private clause**
![2_2_1](assets/2_2_1.png)


**firstprivate clause**
![2_2_2](assets/2_2_2.png)

## Exercice 4 - Boucles parallèles
Écrire un programme non parallèle qui compte de 0 à 50 en utilisant une simple boucle, et fait un
printf du compteur à chaque itération.

**Un thread**
![3_1](assets/3_1.png)

Le temps moyen affiché est 0 car 50 est trop petit pour véritablement voir une différence entre threadé et non threadé

### Modifier le code pour passer à 3 puis 4 tâches.

**4 threads**
![3_2](assets/3_2.png)

On peut voir que le comptage est bien répartis entre les 4 threads et mets en moyenne : *Average time 4 threads : 0.000664 seconds* (using WSL)


## Exercice 5 - Calcul de PI

*Note: j'ai réexécuté le calcul de PI en dynamique sur ma machine perso sous WSL et les valeurs obtenues sont incomparables avec les valeurs static sur les machines de l'ESIEE*

1. Valeur de PI obtenue : *3.141592653589971*

2. Temps moyen calculé sur 10 itérations
    - PC ESIEE : 8 secondes

    - WSL 

        ![4_1](assets/4_1.png)

3. Temps moyen calculé sur 10 itérations sur 2 threads


    - PC ESIEE : `Temps d'exec moyen sur 10 essais avec 2 threads : 4.46 secondes`

    - WSL : 
        
        ![4_2](assets/4_2.png)

4. On remarque que la durée d'exécution est divisé par 2 entre mono threadé et 2 threads

5. 12 threads
    - Machine ESIEE moyenne calculé sur 10 itérations :
        
        ![pi_mt_static](assets/pi_mt_static.png)

        On peut voir que le temps moyen se divise par 2 jusqu'à 8 threads et se stabilise ensuite.
        Cela s'explique par le fait que 8 corresponds au nombre de coeur physique de la machine.    
 
    - GNUplot WSL : moyenne calculé sur 10 itérations

        ![pi_mt_static_wsl](assets/pi_mt_static_wsl.png)

        La courbe présente la même allure mais l'intervalles de valeur est plus restreint que sur les machines de l'ESIEE.
        Cela peut s'expliquer par la différence de puissance de CPU.

6. Utilisation stratégie d'ordonnancement dynamic

    - GNUplot WSL : moyenne calculé sur 10 itérations

        ![pi_mt_dynamic](assets/pi_mt_dynamic.png)

        On peut constater que l'efficacité est bien moindre d'une part au vu des intervalles de valeurs.
        Aussi, l'allure de la courbe présentant des hautes amplitudes montrant l'inefficacité de la tâche en dynamic.
        Cela peut s'expliquer par WSL car c'est une VM et aussi à cause de l'homogénéité du calcul de PI. En effet,
        les threads auront une charge de travail similaire étant donné que c'est le même calcul.

## Exercice 6 - Création de fractal, ensemble de Julia

![julia](assets/julia.pgm)

4. Le temps d'exécution monothread, puis pour 2, 3, 4, 5, 6 etc threads en fonction du nombre de cœurs disponibles sur votre machine

    - Static ESIEE

        ![julia_static](assets/julia_mt_static.png)

    - Dynamic ESIEE

        ![julia_dynamic](assets/julia_mt_dynamic.png)


