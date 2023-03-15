#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PERSONS 100

typedef struct {
    char nom[50];
    char prenom[50];
    int badge;
    int code;
    char date[20];
    
} Personne;

Personne personnes[MAX_PERSONS];
int nb_personnes = 0;

// Fonction pour afficher le menu principal
void afficherMenu() {
    printf("Menu :\n");
    printf("1. Afficher la liste des personnes enregistrees.\n");
    printf("2. Ajouter une personne a la liste.\n");
    printf("3. Supprimer une personne suivant le numero de badge.\n");
    printf("4. Modifier le code secret d'une personne.\n");
    printf("5. Simuler le controle d'acces via le clavier.\n");
    printf("6. Sauvegarder la liste des personnes dans le fichier 'personnes.txt'.\n");
    printf("7. Quitter le programme.\n\n");
}

// Fonction pour afficher la liste des personnes enregistrees
void afficherListe() {
    printf("Liste des personnes enregistrees :\n");
    for (int i = 0; i < nb_personnes; i++) {
        printf("%s %s (badge %04d) - Date et heure de l'enregistrement : %s\n", personnes[i].prenom, personnes[i].nom, personnes[i].badge, personnes[i].date);
    }
    printf("\n");
}


// Fonction pour ajouter une personne a la liste
void ajouterPersonne() {
    if (nb_personnes == MAX_PERSONS) {
        printf("La liste est pleine.\n");
        return;
    }
    Personne p;
    bool badgeExiste, codeExiste; // Déclaration des variables badgeExiste et codeExiste
    do {
        badgeExiste = false;
        codeExiste = false;
        printf("Ajout d'une nouvelle personne :\n");
        printf("Nom : ");
        scanf("%s", p.nom);
        printf("Prenom : ");
        scanf("%s", p.prenom);
        printf("Numero de badge (4 chiffres) : ");
        scanf("%d", &p.badge);
        printf("Code secret (4 chiffres) : ");
        scanf("%d", &p.code);
        
        // Vérification de l'unicité du badge et du code
        for (int i = 0; i < nb_personnes; i++) {
            if (personnes[i].badge == p.badge) {
                printf("Le numero de badge %04d est deja utilise.\n", p.badge);
                badgeExiste = true;
                break;
            }
            if (personnes[i].code == p.code) {
                printf("Le code secret %04d est deja utilise.\n", p.code);
                codeExiste = true;
                break;
            }
        }
    } while (badgeExiste || codeExiste); // La boucle s'exécute tant que le badge ou le code existe déjà
    
    time_t maintenant = time(NULL);
    strftime(p.date, sizeof(p.date), "%d/%m/%Y %H:%M:%S", localtime(&maintenant));
    personnes[nb_personnes++] = p;
    printf("%s %s a ete ajoute a la liste.\n\n", p.prenom, p.nom);
}


// Fonction pour supprimer une personne suivant le numero de badge
void supprimerPersonne() {
    int badge;
    printf("Suppression d'une personne :\n");
    printf("Numero de badge de la personne a supprimer : ");
    scanf("%d", &badge);
    int index = -1;
    for (int i = 0; i < nb_personnes; i++) {
        if (personnes[i].badge == badge) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Aucune personne n'a ete trouvee avec le numero de badge %04d.\n\n", badge);
    } else {
        printf("%s %s a ete supprime de la liste.\n\n", personnes[index].prenom, personnes[index].nom);
        for (int i = index; i < nb_personnes - 1; i++) {
            personnes[i] = personnes[i + 1];
        }
        nb_personnes--;
    }
}

// Fonction pour modifier le code secret d'une personne
void modifierCode() {
    int badge, code;
    printf("Modification du code secret d'une personne :\n");
    printf("Numero de badge de la personne : ");
    scanf("%d", &badge);
    int index = -1;
    for (int i = 0; i < nb_personnes; i++) {
        if (personnes[i].badge == badge) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Aucune personne n'a ete trouvee avec le numero de badge %04d.\n\n", badge);
    } else {
        printf("Nouveau code secret pour %s %s : ", personnes[index].prenom, personnes[index].nom);
        scanf("%d", &code);
        personnes[index].code = code;
        printf("Le code secret de %s %s a ete modifie.\n\n", personnes[index].prenom, personnes[index].nom);
    }
}

// Fonction pour simuler le controle d'acces via le clavier
void simulerControle() {


 int badge, code;
    printf("Simulation de l'entree d'une personne :\n");
    printf("Numero de badge : ");
    scanf("%d", &badge);
    printf("Code secret : ");
    scanf("%d", &code);
    int index = -1;
    for (int i = 0; i < nb_personnes; i++) {
        if (personnes[i].badge == badge) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Aucune personne n'a ete trouvee avec le numero de badge %04d.\n\n", badge);
    } else if (personnes[index].code != code) {
        printf("Le code secret est incorrect.\n\n");
    } else {
        printf("Bienvenue %s %s !\n\n", personnes[index].prenom, personnes[index].nom);
        // Enregistrement de la visite dans le fichier "visite.txt"
       
        FILE* fichier = fopen("visite.txt", "a");
       // fprintf(fichier, "%s %s est entre(e) a %s\n", personnes[index].prenom, personnes[index].nom, ctime(&maintenant));
       fprintf(fichier, "%s ; %s ; %04d ; %04d ; %s\n", personnes[index].nom, personnes[index].prenom, personnes[index].badge, personnes[index].code, personnes[index].date);
        fclose(fichier);
    }
}

// Fonction pour sauvegarder la liste des personnes dans le fichier 'personnes.txt'
void sauvegarderPersonnes() {
    FILE *f = fopen("personnes.txt", "w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    for (int i = 0; i < nb_personnes; i++) {
        fprintf(f, "%s;%s;%04d;%04d;%s\n", personnes[i].nom, personnes[i].prenom, personnes[i].badge, personnes[i].code, personnes[i].date);
    }
    fclose(f);
    printf("La liste des personnes a été sauvegardée dans le fichier 'personnes.txt'.\n\n");
} 

int main() {
    char choix;
    do {
        afficherMenu();
        printf("Votre choix : ");
        scanf(" %c", &choix);
        switch (choix) {
            case '1':
                afficherListe();
                break;
            case '2':
                ajouterPersonne();
                break;
            case '3':
                supprimerPersonne();
                break;
            case '4':
                modifierCode();
                break;
            case '5':
                simulerControle();
                break;
            case '6':
                sauvegarderPersonnes();
                break;
             case '7':
                 printf("Au revoir !\n");
                  // break;
                   return 0;
             default: 
                    printf("Choix invalide.\n");
                    break;
        }
    } while (choix !=0 );
    
}     
