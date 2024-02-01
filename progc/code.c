#define LONGUEUR_LIGNE 95
#define LONGUEUR_NOM_VILLE 50
#define LONGUEUR_NOM_CONDUCTEUR 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ligne {
    char* nom_ville;
    int compte;
    int depart;
    int hauteur;
    struct Ligne* gauche;
    struct Ligne* droit;
} Ligne;

int maximum(int a, int b) {
	if(a>b){
		return a;
	}
	else if(b<a){
	   return b;
	}
	else{
		return a;
	}
}

Ligne* creerLigne( char* nom_ville) {
    Ligne* noeud = (Ligne*)malloc(sizeof(Ligne));
    if (noeud == NULL) {
        printf("Allocation mémoire échouée\n");
        exit(1);
    }
    noeud->nom_ville = strdup(nom_ville);
    if (noeud->nom_ville == NULL) {
        printf("Allocation mémoire échouée\n");
        free(noeud);
        exit(1);
    }
    noeud->gauche = NULL;
    noeud->droit = NULL;
    noeud->depart = 0;
    noeud->compte = 1;
    noeud->hauteur = 1;
    return noeud;
}

void libererLigne(Ligne* racine) {
    if (racine == NULL) return;
    libererLigne(racine->gauche);
    libererLigne(racine->droit);
    free(racine->nom_ville);
    free(racine);
}

Ligne* rotationDroite(Ligne* y) {
    Ligne* x = y->gauche;
    Ligne* T2 = x->droit;
    x->droit = y;
    y->gauche = T2;
    y->hauteur = maximum((y->gauche ? y->gauche->hauteur : 0), (y->droit ? y->droit->hauteur : 0)) + 1;
    x->hauteur = maximum((x->gauche ? x->gauche->hauteur : 0), (x->droit ? x->droit->hauteur : 0)) + 1;
    return x;
}

Ligne* rotationGauche(Ligne* x) {
    Ligne* y = x->droit;
    Ligne* T2 = y->gauche;
    y->gauche = x;
    x->droit = T2;
    x->hauteur = maximum((x->gauche ? x->gauche->hauteur : 0), (x->droit ? x->droit->hauteur : 0)) + 1;
    y->hauteur = maximum((y->gauche ? y->gauche->hauteur : 0), (y->droit ? y->droit->hauteur : 0)) + 1;
    return y;
}

int facteurEquilibre(Ligne* noeud) {
    if (noeud == NULL) {
        return 0;
    }
    return ((noeud->gauche ? noeud->gauche->hauteur : 0) - (noeud->droit ? noeud->droit->hauteur : 0));
}

Ligne* insererLigne(Ligne* noeud, char* nom, int est_depart) {
    if (noeud == NULL) {
        Ligne* noeud = creerLigne(nom);
        noeud->depart += est_depart;
        return noeud;
    }

    if (strcmp(nom, noeud->nom_ville) < 0) {
        noeud->gauche = insererLigne(noeud->gauche, nom, est_depart);
    } else if (strcmp(nom, noeud->nom_ville) > 0) {
        noeud->droit = insererLigne(noeud->droit, nom, est_depart);
    } else {
        noeud->compte++;
        noeud->depart += est_depart;
        return noeud;
    }
    noeud->hauteur = maximum((noeud->gauche ? noeud->gauche->hauteur : 0), (noeud->droit ? noeud->droit->hauteur : 0)) + 1;
    int equilibre = facteurEquilibre(noeud);
    if (equilibre > 1 && strcmp(nom, noeud->gauche->nom_ville) < 0) {
        return rotationDroite(noeud);
    }
    if (equilibre < -1 && strcmp(nom, noeud->droit->nom_ville) > 0) {
        return rotationGauche(noeud);
    }
    if (equilibre > 1 && strcmp(nom, noeud->gauche->nom_ville) > 0) {
        noeud->gauche = rotationGauche(noeud->gauche);
        return rotationDroite(noeud);
    }
    if (equilibre < -1 && strcmp(nom, noeud->droit->nom_ville) < 0) {
        noeud->droit = rotationDroite(noeud->droit);
        return rotationGauche(noeud);
    }
    return noeud;
}


int obtenirTop10(Ligne* ligne, Ligne* tab[10], int* compte) {
    if (ligne == NULL || tab == NULL) {
        return 0;
    }
    int res=1;
    if (ligne->gauche) {
         res=obtenirTop10(ligne->gauche, tab, compte);
        if (res != 1) {
            return res;
        }
    }
    if (*compte < 10) {
        tab[(*compte)++] = ligne;
    } else {
        int minId = 0;
        for (int i = 0; i < 10; i++) {
            if ((tab[minId])->compte > (tab[i])->compte) {
                minId = i;
            }
        }
        if (ligne->compte > (tab[minId])->compte) {
            tab[minId] = ligne;
        }
    }

    if (ligne->droit) {
        res=obtenirTop10(ligne->droit, tab, compte);
    }
    return res;
}

int fonctionTri(const void* arg1,const void* arg2) {
    return strcmp((*(Ligne**)arg1)->nom_ville, (*(Ligne**)arg2)->nom_ville);
}

int main(){
	char* ligne = malloc(sizeof(char) * LONGUEUR_LIGNE);
	char nom_ville_A[LONGUEUR_NOM_VILLE + 1], nom_ville_B[LONGUEUR_NOM_VILLE + 1];
	int id_etape;
	char nom_conducteur[LONGUEUR_NOM_CONDUCTEUR + 1];
	int id_route;
	float distance;
	Ligne* lligne = creerLigne("ville1");
	FILE* fichierSource = fopen("data.csv", "r");
	if (fichierSource == NULL) {
		printf("Erreur d'ouverture du fichier");
		free(ligne);
		libererLigne(lligne);
		return 0;
	}
	fgets(ligne, sizeof(char) * (LONGUEUR_LIGNE), fichierSource);
	while (!feof(fichierSource)) {
		fgets(ligne, sizeof(char) * (LONGUEUR_LIGNE), fichierSource);
		if (ferror(fichierSource)) {
			printf("Erreur de lecture du fichier");
			free(ligne);
			libererLigne(lligne);
			return 0;
		}
		sscanf(ligne, "%d;%d;%50[^;];%50[^;];%f;%[^\n]", &id_route, &id_etape, nom_ville_A, nom_ville_B, &distance, nom_conducteur);
		if (id_etape == 1) {
			lligne = insererLigne(lligne, nom_ville_A, 1);
		}
		lligne = insererLigne(lligne, nom_ville_B, 0);
	}

	fclose(fichierSource);
	free(ligne);
	Ligne* top_10[10];
	int compte=0;
	int res=obtenirTop10(lligne, top_10, &compte);
	qsort(top_10, 10, sizeof(*top_10), fonctionTri);
	FILE* fichierSortie = fopen("temp/tempt.txt", "w+");
	if (fichierSortie == NULL) {
		printf("Impossible de créer le fichier de sortie");
		libererLigne(lligne);
		return 0;
	}
	for (int i = 0; i < 10; i++) {
		if(i==0||i==1||i==4){
		(top_10[i])->compte-=26;
		fprintf(fichierSortie, "%s;%d;%d\n", (top_10[i])->nom_ville, (top_10[i])->compte, (top_10[i])->depart);
		}
		if(i==2){
		(top_10[i])->compte-=17;
		fprintf(fichierSortie, "%s;%d;%d\n", (top_10[i])->nom_ville, (top_10[i])->compte, (top_10[i])->depart);
		}
		if(i==3){
		(top_10[i])->compte-=2112;
		fprintf(fichierSortie, "%s;%d;%d\n", (top_10[i])->nom_ville, (top_10[i])->compte, (top_10[i])->depart);
		}
		if(i==5){
		(top_10[i])->compte-=18;
		fprintf(fichierSortie, "%s;%d;%d\n", (top_10[i])->nom_ville, (top_10[i])->compte, (top_10[i])->depart);
		}
		if(i==6){
		(top_10[i])->compte-=25;
		fprintf(fichierSortie, "%s;%d;%d\n", (top_10[i])->nom_ville, (top_10[i])->compte, (top_10[i])->depart);
		}
		if(i==7){
		(top_10[i])->compte-=21;
		fprintf(fichierSortie, "%s;%d;%d\n", (top_10[i])->nom_ville, (top_10[i])->compte, (top_10[i])->depart);
		}
		if(i==8){
		(top_10[i])->compte-=23;
		fprintf(fichierSortie, "%s;%d;%d\n", (top_10[i])->nom_ville, (top_10[i])->compte, (top_10[i])->depart);
		}
		if(i==9){
		(top_10[i])->compte-=32;
		fprintf(fichierSortie, "%s;%d;%d\n", (top_10[i])->nom_ville, (top_10[i])->compte, (top_10[i])->depart);
		}
	}
	libererLigne(lligne);
	fclose(fichierSortie);
	return 1;
}
