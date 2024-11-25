#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char motsPendu[100];

void motpendu(void) {
    FILE *ouvrir_fichier = fopen("words.txt", "r"); //Ouvre le fichier word.txt
    srand(time(NULL));
    const int nombre_aleatoire = rand() % 835; //limite le nombre aléatoire entre 0 et 834 (inclus).
    for (int i = 0; i <= nombre_aleatoire; i++) { // boucle qui permet de s'arreter sur un mot de la liste en fonction du nb aleatoire généré
        fgets(motsPendu, sizeof(motsPendu), ouvrir_fichier); //sizeof permet d'éviter un dépassement de mémoire en se basant sur motsPendu.
    }
    fclose(ouvrir_fichier);//ferme le fichier

    for (int i = 0; motsPendu[i] != '\0'; i++) { //met les lettres du motsPendu en majuscule
        motsPendu[i] = toupper(motsPendu[i]);
    }
    motsPendu[strcspn(motsPendu, "\n")] = '\0';
    printf("%s\n", motsPendu);
}
void jeux(void) {
    motpendu();
    char motUtilisateur[100];
    int maxErreur = 7;
    char lettre[10];
    char lettreUtilise[26];
    int nombreLettreUtilise = 0;
    const char *pendu[] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========",
    "  +---+\n  |   |\n [O] |\n /|\\  |\n / \\  |\n      |\n========="
    };

    char nomJoueur[50];
    printf("Entre ton prenom :\n");
    scanf("%s", nomJoueur);
    printf("=====================================\n");
    printf("Bienvenu dans le jeu du pendu %s\n", nomJoueur);
    printf("=====================================\n");

    int longeurMot = 0;

    longeurMot = strlen(motsPendu);
    for (int i = 0; i < longeurMot; i++) {
        motUtilisateur[i] = '_';
    }
    motUtilisateur[longeurMot] = '\0';

    do {
        //Demande à l'utiliser d'entrer une lettre
        printf("\nEntrez une lettre :");
        scanf(" %s", &lettre); //Stock la lettre dans le tableau lettre

        lettre[0] = toupper(lettre[0]);


        //Permet de restreindre l'utilisateur à utiliser uniquer les lettres
        if (!((lettre[0] >= 'a' && lettre[0] <= 'z') || (lettre[0] >= 'A' && lettre[0] <= 'Z'))) {
            printf("Entrez invalide tu dois entrer uniquement une lettre et pas un chiffre.\n");
            continue;
        }

        //initialise la longueur du tableau dans lequel va être stocké la lettre donné par l'utilisateur
        int longueurEntree = 0;

        while (lettre[longueurEntree] != '\0') {
            longueurEntree++;
        }
        /*
        Tant que qu'on arrive pas au bout du tableau lettre on ajoute 1 a longueurEntree
        ça permet de s'assurer que l'utilisateur entre bien qu'une seul lettre.*/

        if (longueurEntree != 1) { // Si longeurEntree n'est pas égale à 1 alors le message d'erreur s'affiche et on reviens au début du do
            printf("Veuillez entrer une seule lettre, s'il vous plait.\n");
            continue;
        }


        int dejaUtilisee = 0; //false, par défaut, on suppose que la lettre n'a pas encore été proposée.
        for (int i = 0; i < nombreLettreUtilise; i++) { //parcours toutes les lettres déjà utilisé
            if (lettre[0] == lettreUtilise[i]) { //compare la lettre stocké dans le tableau lettre avec les lettres stocké dans lettreUtilise
                dejaUtilisee = 1; //true, Si la lettre est déjà stocké dans lettreUilise alors on met true
                break;
            }
        }

        if (dejaUtilisee) {
            printf("Vous avez deja propose cette lettre");
            continue;
        }

        lettreUtilise[nombreLettreUtilise] = lettre[0];
        nombreLettreUtilise++;

        /*Permet de stocker la lettre donné par l'utilisateur dans le tableau lettreUtilise
         * a l'index donné par nombreLettreUtilise. A chaque fois on incrémente de 1 nombreLettreUtilisé pour
         * stocké la prochaine lettre
         */

        printf("\n");

        int lettreTrouvee = 0; //false

        for (int i = 0; i < longeurMot ; i++) {//Parcours chaque lettre dans le tableau motsPendu
            if (lettre[0] == motsPendu[i]) { //Si l'index 0 de lettre est égale a une lettre dans motsPendu
                motUtilisateur[i] = lettre[0];//Remplace le petit tiret par la bonne lettre et au bon endroit
                lettreTrouvee = 1; //true, si la lettre est dans le motsPendu
            }

        }
        printf("%s", motUtilisateur); //imprime le mot avec la lettre à la place du tiret

        if (!lettreTrouvee) { //Si la lettre n'est pas dans motsPendu imprime une erreur. Donc si letteTrouve = false
            maxErreur--;
            printf("\n%s\n\n", pendu[7 - maxErreur]);
            printf("\nDommage, cette lettre ne se trouve pas dans le mot.\n");
            printf("Il ne te reste plus que %d erreurs\n", maxErreur);
        }

        //parcour les lettres utilise pour les afficher une à une.
        printf("\nlettre utilisee :");
        for (int i = 0; i < nombreLettreUtilise; i++) {
            printf("%c, ", lettreUtilise[i]);
        }
        printf("\n");
    } while (strcmp(motsPendu, motUtilisateur) != 0 && maxErreur > 0);
    //Tant que motsPendu n'est pas égale a motUtilisateur et que le maxErreur est superieur à 0 ça revien au do. Retourne 0 si les chaîne sont identique.

    if (maxErreur > 0) {
        printf("\nBravo, c'est gagne, tu as lu dans mon esprit\n");
    } else {
        printf("\nDesole mais c'est pendu, Retente ta chance !\n");
        printf("Le mot etait : %s\n", motsPendu);
    }
}
int main(){
    char rejouer[1];
    do {
        jeux();
        printf("Veux-tu rejouer o/n ?\n");
        scanf("%s", rejouer);
    } while (strcmp(rejouer, "o") == 0);
    printf("Merci d'avoir joue !");
    return 0;
}


