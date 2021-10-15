
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct mon_contact{
	char nom[16];
	char tel[11];
	char mail[26];
} Contact;

struct elem_arbre {
	Contact info;
	struct elem_arbre *fils;
	struct elem_arbre *frere;
};

struct elem_arbre * ajout(struct elem_arbre *p, Contact e);
char * find_trio(Contact e);
void ajout_trio (struct elem_arbre *r, Contact e,char * trio_lettre);
void ajout_contact (struct elem_arbre *r, Contact e);
struct elem_arbre * creer_contact( struct elem_arbre *r, Contact e);
void supprimer_contact (struct elem_arbre *p, char l[]);
struct elem_arbre * plus_petit(struct elem_arbre *p);
struct elem_arbre * modifier_contact(struct elem_arbre *p, char l[]);
void chercher_contact_par_1_lettre(struct elem_arbre *p, char l[]);
void chercher_contact_par_2_lettre(struct elem_arbre *p, char l[]);
struct elem_arbre * chercher_contact_par_nom(struct elem_arbre *p, char l[]);
void afficher(struct elem_arbre *p);


int main(void)
{
	int choix = 0;
	Contact e;
	struct elem_arbre * p = NULL;
    	Contact rt={"contact",NULL,NULL};
	p=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
    	p->info=rt;
    	p->fils=NULL;
    	p->frere=NULL;
    char ln[16];


/*Afficher le menu à l'utilisateur*/
	system("cls");
    system("COLOR 3F");
    system("COLOR 3f");
    system("cls");
    int choix1;
    printf("\n\n");
    printf("\n\t\t\t\t\t      Bonjour (^_^) !!\n\t\t\t Voici un programme qui permet de gerer votre repertoire telephonique\n ");

    printf("                                 ********************************************************\n");
    printf("                                 |                REPERTOIRE TELEPHONIQUE               |\n");
    printf("                                 |                      ~~ MENU ~~                      |\n");
    printf("                                 ********************************************************\n");
    printf("                                 |              1 . Ajouter un contact                  |\n");
    printf("                                 |              2 . Supprimer un contact                |\n");
    printf("                                 |              3 . Chercher un contact                 |\n");
    printf("                                 |              4 . Afficher le repertoire courant      |\n");
    printf("                                 |              5 . Quitter                             |\n");
    printf("                                 ********************************************************\n");


/*Revenir au menu après chaque instruction jusqu'à ce que l'utilisateur quitte*/
 	while (choix != 6) {

		/*Obtenir l'option de l'utilisateur*/
		printf("\nVeuillez selectionner une option: ");
		scanf("%d", &choix);

        /*Si l'option est 1 (Ajouter):*/
		if (choix == 1) {
                /*Prendre les données de l'utilisateur.*/
			printf("Veuillez saisir votre nom: ");
			scanf("%s", &e.nom);
			printf("Veuillez saisir votre numero de telephone: ");
			scanf("%s", &e.tel);
			printf("Veuillez saisir votre adresse mail: ");
			scanf("%s", &e.mail);
			/*Créez un nouveau nœud*/
			p = ajout(p, e);
			/*Confirmez la création du nœud*/
			printf("------Contact enregistre-----\n\n");

		}
		else if (choix == 2) {

			printf("Veuillez saisir le nom du contact: ");
			scanf("%s", &ln);

			supprimer_contact(p, ln);
		}

		else if (choix == 3) {

			printf("Veuillez saisir le nom du contact: ");
			scanf("%s", &ln);
			if(strlen(ln)==1)
				chercher_contact_par_1_lettre(p, ln);
			else if(strlen(ln)==2)
				chercher_contact_par_2_lettre(p, ln);
			else{ 	chercher_contact_par_nom(p, ln);}

		}
		else if (choix == 4) {
			afficher(p);
		}
		else if (choix == 5) {
            printf("\n\nMerci pour avoir utilise ce programme (^_^) a tres bientot !!\n");
			break;
		}
/*Si l'utilisateur ne choisie pas une option existante*/

		else {
			/*Afficher un message d'erreur.*/
			printf("Ce choix n'existe pas, choisir un numero de 1 a 6\n\n");
			break;
		}
	}
	return 0;
}


struct elem_arbre * ajout(struct elem_arbre *p, Contact e) {
	char lettre0_nom[2];
	lettre0_nom[0] = e.nom[0];
	lettre0_nom[1] = '\0';
	char *tr=find_trio(e);
	if(p->fils==NULL){

	//initialisation des lettres et trios et contacts
		struct elem_arbre *element = NULL;
		element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
		element->info=e;
		element->fils=NULL;
		element->frere=NULL;


		struct elem_arbre *trio = NULL;
		trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
	    	Contact rt2={NULL,NULL,NULL};
		strcpy(rt2.nom,tr);
		trio->info=rt2;
		trio->fils=element;
		trio->frere=NULL;

		struct elem_arbre *lettre_1 = NULL;
		lettre_1=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
	    	Contact rt={NULL,NULL,NULL};
		strcpy(rt.nom,lettre0_nom);
		lettre_1->info=rt;
		lettre_1->fils=trio;
		lettre_1->frere=NULL;

		p->fils=lettre_1;

	}
	else{


	    	if (strcmp(lettre0_nom, p->fils->info.nom)< 0){

			struct elem_arbre *element = NULL;
			element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
			element->info=e;
			element->fils=NULL;
			element->frere=NULL;

			struct elem_arbre *trio = NULL;
			trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
			Contact rt2={NULL,NULL,NULL};
			strcpy(rt2.nom,tr);
			trio->info=rt2;
			trio->fils=element;
			trio->frere=NULL;

			struct elem_arbre *lettre_1 = NULL;
			lettre_1=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
			Contact rt={NULL,NULL,NULL};
			strcpy(rt.nom,lettre0_nom);
			lettre_1->info=rt;
			lettre_1->fils=trio;
			lettre_1->frere=p->fils;

			p->fils=lettre_1;
		}

		else if (strcmp(lettre0_nom, p->fils->info.nom)== 0){
			ajout_trio (p->fils, e,tr) ;
		}
		else if (p->fils->frere== NULL){

			struct elem_arbre *element = NULL;
			element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
			element->info=e;
			element->fils=NULL;
			element->frere=NULL;

			struct elem_arbre *trio = NULL;
			trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
			Contact rt2={NULL,NULL,NULL};
			strcpy(rt2.nom,tr);
			trio->info=rt2;
			trio->fils=element;
			trio->frere=NULL;

			struct elem_arbre *lettre_1 = NULL;
			lettre_1=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
			Contact rt={NULL,NULL,NULL};
			strcpy(rt.nom,lettre0_nom);
			lettre_1->info=rt;
			lettre_1->fils=trio;
			lettre_1->frere=NULL;

			p->fils->frere=lettre_1;
		}
		else {
			struct elem_arbre *element_0 = p->fils;
			while (element_0->frere!=NULL){
				if (strcmp(lettre0_nom, element_0->frere->info.nom)< 0){

					struct elem_arbre *element = NULL;
					element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
					element->info=e;
					element->fils=NULL;
					element->frere=NULL;

					struct elem_arbre *trio = NULL;
					trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
					Contact rt2={NULL,NULL,NULL};
					strcpy(rt2.nom,tr);
					trio->info=rt2;
					trio->fils=element;
					trio->frere=NULL;

					struct elem_arbre *lettre_1 = NULL;
					lettre_1=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
					Contact rt={NULL,NULL,NULL};
					strcpy(rt.nom,lettre0_nom);
					lettre_1->info=rt;
					lettre_1->fils=trio;
					lettre_1->frere=element_0->frere;

					element_0->frere=lettre_1;

					break;
				}
				else if (strcmp(lettre0_nom, element_0->frere->info.nom)== 0){
					ajout_trio (element_0->frere, e,tr) ;
					break;
				}
				element_0=element_0->frere;

				if(element_0->frere==NULL){

					struct elem_arbre *element = NULL;
					element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
					element->info=e;
					element->fils=NULL;
					element->frere=NULL;

					struct elem_arbre *trio = NULL;
					trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
					Contact rt2={NULL,NULL,NULL};
					strcpy(rt2.nom,tr);
					trio->info=rt2;
					trio->fils=element;
					trio->frere=NULL;

					struct elem_arbre *lettre_1 = NULL;
					lettre_1=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
					Contact rt={NULL,NULL,NULL};
					strcpy(rt.nom,lettre0_nom);
					lettre_1->info=rt;
					lettre_1->fils=trio;
					lettre_1->frere=element_0->frere;

					element_0->frere=lettre_1;
					break;
				}
			}
		}
	}
return p;

}




void ajout_trio (struct elem_arbre *r, Contact e,char * trio_lettre) {

	struct elem_arbre *trio = r->fils;
	if (strcmp(trio_lettre, trio->info.nom)< 0){
		struct elem_arbre *element = NULL;
		element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
		element->info=e;
		element->fils=NULL;
		element->frere=NULL;

		struct elem_arbre *new_trio = NULL;
		new_trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
	    	Contact rt={NULL,NULL,NULL};
		strcpy(rt.nom,trio_lettre);
		new_trio->info=rt;
		new_trio->fils=element;
		new_trio->frere=r->fils;

		r->fils=new_trio;
	}
	else if (strcmp(trio_lettre, trio->info.nom)== 0){
		ajout_contact(trio, e);

	}
	else if(trio->frere==NULL){

		struct elem_arbre *element = NULL;
		element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
		element->info=e;
		element->fils=NULL;
		element->frere=NULL;

		struct elem_arbre *new_trio = NULL;
		new_trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
	    	Contact rt={NULL,NULL,NULL};
		strcpy(rt.nom,trio_lettre);
		new_trio->info=rt;
		new_trio->fils=element;
		new_trio->frere=NULL;
		trio->frere=new_trio;
	}
	else{
		while(trio->frere!=NULL){
			if (strcmp(trio_lettre, trio->frere->info.nom)< 0){
				struct elem_arbre *element = NULL;
				element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
				element->info=e;
				element->fils=NULL;
				element->frere=NULL;

				struct elem_arbre *new_trio = NULL;
				new_trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
			    	Contact rt={NULL,NULL,NULL};
				strcpy(rt.nom,trio_lettre);
				new_trio->info=rt;
				new_trio->fils=element;
				new_trio->frere=trio->frere;

				trio->frere=new_trio;

				break;
			}
			else if (strcmp(trio_lettre, trio->frere->info.nom)== 0){
				ajout_contact(trio, e);
				break;
			}
			trio=trio->frere;

			if(trio->frere==NULL){

				struct elem_arbre *element = NULL;
				element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
				element->info=e;
				element->fils=NULL;
				element->frere=NULL;

				struct elem_arbre *new_trio = NULL;
				new_trio=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
			    	Contact rt2={NULL,NULL,NULL};
				strcpy(rt2.nom,trio_lettre);
				new_trio->info=rt2;
				new_trio->fils=element;
				new_trio->frere=NULL;

				trio->frere=new_trio;
				break;
			}
		}
	}
}


void ajout_contact (struct elem_arbre *r, Contact e) {

	struct elem_arbre *contact = r->fils;
	if (strcmp(e.nom, contact->info.nom)< 0){
		struct elem_arbre *element = NULL;
		element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
		element->info=e;
		element->fils=NULL;
		element->frere=contact;


		r->fils=element;
	}
	else if(contact->frere==NULL){

		struct elem_arbre *element = NULL;
		element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
		element->info=e;
		element->fils=NULL;
		element->frere=NULL;


		contact->frere=element;
	}
	else{
		while(contact->frere!=NULL){
			if (strcmp(e.nom, contact->frere->info.nom)< 0){
				struct elem_arbre *element = NULL;
				element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
				element->info=e;
				element->fils=NULL;
				element->frere=contact->frere;

				contact->frere=element;

				break;
			}
			contact=contact->frere;

			if(contact->frere==NULL){

				struct elem_arbre *element = NULL;
				element=(struct elem_arbre*)(malloc(sizeof(struct elem_arbre)));
				element->info=e;
				element->fils=NULL;
				element->frere=NULL;

				contact->frere=element;
				break;

			}
		}
	}
}


char * find_trio(Contact e){
    char T[8][5]={"abc\0","def\0","ghi\0","jkl\0","mno\0","pqr\0","stuv\0","wxyz\0"};
    char l=e.nom[1];
    char *tr=(char*)malloc(4*sizeof(char));
    int i;
    for(i=1;i<8;i++){
	if(T[i][0]>l){
		strcpy(tr,T[i-1]);
		return tr;
	}
    }
    strcpy(tr,T[i-1]);
    return tr;
}

void afficher(struct elem_arbre *r){
	struct elem_arbre *letters = r->fils;
	while (letters!=NULL){
		printf("Lettre : %s\n",letters->info.nom);
		struct elem_arbre *trios = letters->fils;
		while (trios!=NULL){
			printf("\tTrio : %s\n",trios->info.nom);
			struct elem_arbre *contacts = trios->fils;
			while (contacts!=NULL){
				printf("\t\tContact : %s %s %s\n",contacts->info.nom,contacts->info.tel,contacts->info.mail);
				contacts=contacts->frere;
			}
			trios=trios->frere;
		}
		letters=letters->frere;
	}

}

void supprimer_contact (struct elem_arbre *r, char l[]){
	struct elem_arbre *lettres = r->fils;
	struct elem_arbre *lettres_2 = lettres;
	while(l[0]>lettres->info.nom[0] && lettres->frere!=NULL){

		lettres_2=lettres;
		lettres=lettres->frere;
	}

	if (l[0]!=lettres->info.nom[0]){
		printf("le nom saisi n'existe pas 1!! \n");
	}
	else{
		struct elem_arbre *trios = lettres->fils;
		struct elem_arbre *trios_2 = trios;
		do{
			int taille=strlen(trios->info.nom);

			if(trios->info.nom[0]<=l[1] && trios->info.nom[taille-1]>=l[1]){
				if (strcmp(l, trios->fils->info.nom)== 0){
					if(trios->fils->frere!=NULL){
						struct elem_arbre *temp=trios->fils;
						trios->fils=trios->fils->frere;
						free(temp);
					}
					else{
						if(trios_2 == trios && trios->frere==NULL){
							if(lettres_2==lettres && lettres->frere==NULL){
								r->fils=NULL;
								free(lettres);
							}
							else if(lettres_2==lettres && lettres->frere!=NULL){
								r->fils=lettres->frere;
								free(lettres);
							}
							else{
								lettres_2->frere=lettres->frere;
								free(lettres);
							}
						}
						else if(trios_2 == trios && trios->frere!=NULL){
							lettres->fils=trios->frere;
							free(trios);
						}
						else{
							trios_2->frere=trios->frere;
							free(trios);
						}
					}
					break;
				}
				else{
						struct elem_arbre *contacts=trios->fils;

						while(contacts->frere!=NULL && strcmp(l, contacts->frere->info.nom)!= 0){
							contacts=contacts->frere;
						}
						if(strcmp(l, contacts->frere->info.nom)==0){
							struct elem_arbre *temp=contacts->frere;
							contacts->frere=contacts->frere->frere;
							free(temp);
						}
						else{
							printf("le nom saisi n'existe pas!! \n");
						}
						break;
				}

			}
			trios_2 = trios;
			trios=trios->frere;
		}while(trios!=NULL);
		if(trios==NULL)		printf("le nom saisi n'existe pas 2 !! \n");
	}
}

void chercher_contact_par_1_lettre(struct elem_arbre *r, char l[]){
	struct elem_arbre *lettres = r->fils;
	while(l[0]>lettres->info.nom[0] && lettres->frere!=NULL){
		lettres=lettres->frere;
	}

	if (l[0]!=lettres->info.nom[0]){
		printf("Aucun nom ne commance par %s!! \n",l);
	}
	else{
		printf("Les noms commançant pas %s sont: \n",l);

		struct elem_arbre *trios = lettres->fils;
		while (trios!=NULL){

			struct elem_arbre *contacts = trios->fils;
			while (contacts!=NULL){
				printf("\t- Contact : %s %s %s\n",contacts->info.nom,contacts->info.tel,contacts->info.mail);
				contacts=contacts->frere;
			}
			trios=trios->frere;
		}
	}

}

void chercher_contact_par_2_lettre(struct elem_arbre *r, char l[]){
	struct elem_arbre *lettres = r->fils;
	while(l[0]>lettres->info.nom[0] && lettres->frere!=NULL){
		lettres=lettres->frere;
	}

	if (l[0]!=lettres->info.nom[0]){
		printf("Aucun nom ne commance par %s!! \n",l);
	}
	else{
		struct elem_arbre *trios = lettres->fils;
		do{
			int taille=strlen(trios->info.nom);

			if(trios->info.nom[0]<=l[1] && trios->info.nom[taille-1]>=l[1]){
				printf("Les noms commançant pas %s sont: \n",l);
				struct elem_arbre *contacts = trios->fils;
				while(contacts!=NULL && contacts->info.nom[1]<=l[1]){
					if(contacts->info.nom[1]==l[1]){
						printf("\t- Contact : %s %s %s\n",contacts->info.nom,contacts->info.tel,contacts->info.mail);
					}
					contacts=contacts->frere;
				}
				break;
			}
			trios=trios->frere;
		}while(trios!=NULL);
		if(trios==NULL){		printf("Aucun nom ne commance par %s!! \n",l);	}
	}

}

struct elem_arbre * chercher_contact_par_nom(struct elem_arbre *r, char l[]){
	struct elem_arbre *lettres = r->fils;
	while(l[0]>lettres->info.nom[0] && lettres->frere!=NULL){
		lettres=lettres->frere;
	}

	if (l[0]!=lettres->info.nom[0]){
		printf("Aucun contact avec le nom %s!! \n",l);
	}
	else{
		struct elem_arbre *trios = lettres->fils;
		do{
			int taille=strlen(trios->info.nom);

			if(trios->info.nom[0]<=l[1] && trios->info.nom[taille-1]>=l[1]){
				struct elem_arbre *contacts = trios->fils;
				while(contacts!=NULL && strcmp(contacts->info.nom, l)< 0){
					contacts=contacts->frere;
				}
				if(contacts!=NULL && strcmp(contacts->info.nom, l)== 0){
					printf("\tContact existant : %s %s %s\n",contacts->info.nom,contacts->info.tel,contacts->info.mail);
					return contacts;
				}
				else		printf("Aucun contact avec le nom %s!! \n",l);
				break;
			}
			trios=trios->frere;
		}while(trios!=NULL);
		if(trios==NULL){		printf("Aucun contact avec le nom %s!! \n",l);	}
	}
	return NULL;
}
