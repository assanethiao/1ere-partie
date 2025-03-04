/* Assane Thiao 28/02/2025 */
#include <stdio.h>  /* Pour les entrées/sorties */
#include <stdlib.h> /* Pour les conversions et allocations mémoire */
#include <string.h> /* Pour la manipulation des chaînes de caractères */

/* Définition des constantes */
#define MAX_L_CARAC 80  /* Taille max des noms et prénoms */
#define MAX_L_COURS 3   /* Nombre de matières */

/* Structure représentant une matière avec son nom et sa note */
typedef struct {
    char title[MAX_L_CARAC];
    double score;
} COURSE;

/* Structure représentant une fiche d'étudiant avec nom, prénom, ID et notes */
typedef struct {
    char name[MAX_L_CARAC];
    char surname[MAX_L_CARAC];
    int id;
    COURSE courses[MAX_L_COURS];
} FICHE;

/* Déclaration des fonctions */
void printFiche(FICHE fiche);
void saveFiche(FILE* file, FICHE fiche);
void loadFiche(FICHE* fiche, const char* str);

/* Fonction principale */
int main() {
    /* Initialisation d'une fiche étudiant */
    FICHE etudiant1 = { "Doe", "John", 11300055, {{"Maths", 12.0}, {"Info", 8.5}, {"Physics", 10.0}} };
    printFiche(etudiant1); /* Affichage de la fiche */
    printf("\n");
    /* Téléchargement d'une fiche depuis une chaîne */
    const char* etu = "Thiao;Assane;12410656;Maths;16.71;Info;19.03;Physics;13.23";

    /* Allocation dynamique pour éviter le pointeur NULL */
    FICHE* file1 = (FICHE*)malloc(sizeof(FICHE));
    if (file1 == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return 1;
    }

    loadFiche(file1, etu);
    printFiche(*file1);

    /* Sauvegarde des fiches dans un fichier */
    FILE* file;
    if (fopen_s(&file, "database.csv", "w") == 0) {
        saveFiche(file, etudiant1);
        fclose(file);
    }
    else {
        printf("Erreur d'ouverture du fichier\n");
    }

    /* Libération de la mémoire allouée */
    free(file1);

    return 0;
}

/* Fonction pour afficher une fiche étudiant */
void printFiche(FICHE fiche) {
    printf("Nom: %s\n", fiche.name);
    printf("Prénom: %s\n", fiche.surname);
    printf("Numéro étudiant: %d\n", fiche.id);
    for (int i = 0; i < MAX_L_COURS; i++) {
        printf("%s: %.2f\n", fiche.courses[i].title, fiche.courses[i].score);
    }
}

/* Fonction pour sauvegarder une fiche dans un fichier CSV */
void saveFiche(FILE* file, FICHE fiche) {
    if (file == NULL) return; // Vérification avant d'écrire dans le fichier
    fprintf(file, "%s;%s;%d", fiche.name, fiche.surname, fiche.id);
    for (int i = 0; i < MAX_L_COURS; i++) {
        fprintf(file, ";%s;%.2f", fiche.courses[i].title, fiche.courses[i].score);
    }
    fprintf(file, "\n");
}

/* Fonction pour charger une fiche à partir d'une chaîne formatée CSV */
void loadFiche(FICHE* fiche, const char* str) {
    if (fiche == NULL || str == NULL) return; // Vérification des pointeurs

    char buffer[256];
    strcpy_s(buffer, sizeof(buffer), str);  // Copie sécurisée de la chaîne pour strtok_s

    char* nextValeurRecupere = NULL;
    char* valeurRecupere = strtok_s(buffer, ";", &nextValeurRecupere);
    strcpy_s(fiche->name, MAX_L_CARAC, valeurRecupere);

    valeurRecupere = strtok_s(NULL, ";", &nextValeurRecupere);
    strcpy_s(fiche->surname, MAX_L_CARAC, valeurRecupere);

    valeurRecupere = strtok_s(NULL, ";", &nextValeurRecupere);
    fiche->id = atoi(valeurRecupere);

    /* Extraction des matières et notes */
    for (int i = 0; i < MAX_L_COURS; i++) {
        valeurRecupere = strtok_s(NULL, ";", &nextValeurRecupere);
        strcpy_s(fiche->courses[i].title, MAX_L_CARAC, valeurRecupere);

        valeurRecupere = strtok_s(NULL, ";", &nextValeurRecupere);
        fiche->courses[i].score = atof(valeurRecupere);
    }
}
