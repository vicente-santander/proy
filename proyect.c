#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define M 50
#define N 11

typedef struct guardian{
	char nombre[M];
	char tipo[N];
	int vida;
	int p_ataque;
	int p_defensa;
	struct guardian *next;

}guardian;

typedef struct node {
	guardian *data;
	struct node *next;
} node;



void addNode(node **head, guardian *data) {
	node *newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;
	if (*head == NULL) {
		*head = newNode;
	} else {
		node *current = *head;
		while (current->next != NULL) {
			current = current->next;
	}
	current->next = newNode;
	}

}

void init(node **head){
	
	FILE *fp = fopen("personaje_init.txt", "r");
	if (fp == NULL) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	char nombre[M];
	char tipo[N];
	int vida;
	int p_ataque;
	int p_defensa;

	while (fscanf(fp, "%s %s %d %d %d", nombre, tipo, &vida, &p_ataque, &p_defensa) == 5) {
	    guardian *g = malloc(sizeof(guardian));
	    
	    strcpy(g->nombre, nombre);
	   
	    strcpy(g->tipo, tipo);
	   
		g->vida = vida;
	   
	    g->p_ataque = p_ataque;
	    
	    g->p_defensa = p_defensa;
	    
	    addNode(head, g);
	}

	fclose(fp);
}

void addNodeToPlayer(node **playerHead, guardian *selectedGuardian) {
	node *newNode = malloc(sizeof(node));
	newNode->data = selectedGuardian;
	newNode->next = NULL;
	if (*playerHead == NULL) {
		*playerHead = newNode;
	} else {
		node *current = *playerHead;
		while (current->next != NULL) {
			current = current->next;
	}
	current->next = newNode;
	}
}
void printCharacterStatus(node *playerHead) {
	node *current = playerHead;
	printf("estado del equipo\n");
	while(current != NULL) {
		printf("----------------\n");
		printf("%s (%s) - Vida: %d, Ataque: %d, Defensa: %d\n", current->data->nombre, current->data->tipo, current->data->vida, current->data->p_ataque, current->data->p_defensa);
		
		current = current->next;
	}
	printf("----------------\n");
}


void selectCharacter(node *head, node **playerHead) {
	node *current = head;
	int count = 1;
	printf("Personajes disponibles:\n");
	while (current != NULL) {
		printf("%d.- %s (%s) - Vida: %d, Ataque: %d, Defensa: %d\n", count, current->data->nombre, current->data->tipo, current->data->vida, current->data->p_ataque, current->data->p_defensa);
		current = current->next;
		count++;
	}
	int selected;
	printf("Seleccione un personaje por su número en la lista: ");
	scanf("%d", &selected);
	if (selected < 1 || selected >= count) {
		printf("Seleccion no válida\n");
	} else {
		current = head;
	int i = 1;
	while (i < selected) {
		current = current->next;
		i++;
	}
	addNodeToPlayer(playerHead, current->data);
	printf("Personaje seleccionado: %s (%s)\n", current->data->nombre, current->data->tipo);
	
	}
}

void createCharacter(node **playerHead){	//	problema con el \n al final de la cadena
	int op;
	int validar1 = 1;
	int validar2 = 2;
	char nombre[M];
	srand(time(NULL));
	
	guardian *p = malloc(sizeof(guardian)); // Reservar memoria para el struct guardian
	
	printf("Indique su nombre el nobre que desea para su guardian:\n");
	
	fflush(stdin); // Limpiar el buffer de entrada porque fgets no funcionaría después del scanf
	
	fgets(p->nombre, M, stdin);	//	----------------------------------problema con el \n al final de la cadena--------------------------------
	
	while(validar2 == 2)
	{
		printf("¿Que tipo de guardian desea crear?\n");
		printf("[1] mage \t[2] viking\n");
		printf("[3] beast \t[4] nigromante\n\n");
		printf("Eleccion:");
		scanf("%d",&op);
		
		switch (op)
		{
			case 1 :
				strcpy(p->tipo, "mage"); // Copiar la cadena "mage" en p->tipo
				p->vida = (400+((rand()%10+1)*10));
				p->p_ataque = (150+((rand()%3+1)*10));
				p->p_defensa = (((rand()%5+1)*5)+30);
				printf("-%s --vida %d-- ataque %d--def %d\n",p->tipo, p->vida,p->p_ataque, p->p_defensa);
				addNodeToPlayer(playerHead, p);
				validar2++;
				break;
				
			case 2 :
				strcpy(p->tipo, "viking"); // Copiar la cadena "vikingo" en p->tipo
				p->vida = (500+((rand()%10+1)*10));
				p->p_ataque = (100+((rand()%5+1)*10));
				p->p_defensa = (((rand()%5+1)*5)+70);
				printf("-%s --vida %d-- ataque %d--def %d\n",p->tipo, p->vida,p->p_ataque, p->p_defensa);
				addNodeToPlayer(playerHead, p);
				validar2++;	
				break;
				
			case 3 :
				strcpy(p->tipo, "beast"); // Copiar la cadena "beast" en p->tipo
				p->vida = (350+((rand()%10+1)*10));
				p->p_ataque = (170+((rand()%3+1)*10));
				p->p_defensa = (((rand()%5+1)*5)+25);
				printf("-%s --vida %d-- ataque %d--def %d\n",p->tipo, p->vida,p->p_ataque, p->p_defensa);
				addNodeToPlayer(playerHead, p);
				validar2++;	
				break;
				
			case 4 :
				strcpy(p->tipo, "nigromante"); // Copiar la cadena "nigromante" en p->tipo
				p->vida = (390+((rand()%10+1)*10));
				p->p_ataque = (100+((rand()%4+1)*10));
				p->p_defensa = (((rand()%5+1)*5)+80);
				printf("-%s --vida %d-- ataque %d--def %d\n",p->tipo, p->vida,p->p_ataque, p->p_defensa);
				addNodeToPlayer(playerHead, p);
				validar2++;	
				break;
				
			default :
				printf("opcion invalida\n");
				break;
		}
				
	}

	
}
	
	
int menuOptions(){
	int opt;
	int validar1 = 1;

	//node *head = NULL; // Cabeza de la cola de personajes disponibles del juego
	//init(&head); // Generar la cola de personajes disponibles
	//node *playerHead = NULL; // Cabeza de la cola de personajes seleccionados por el jugador
	
	while(validar1 == 1)
	{
		printf("¿Cuantos jugadores participaran?(max.2)\n");//hacer afuera lo de los jugadores 
		scanf("%d",&opt);
		
		switch(opt)
		{
			case 1 :
				
				validar1++;
				return opt;
				break;
				
			case 2 :
				
				validar1++;
				return opt;
				break;
				
			default:
				
				printf("opcion invalida\n");
				break;
		}
		
	}
}

int selectTournament(){

	int mode;
	int i=0;
	while(i==0){
		printf("[1]Principiante\t[2]Intermedio\t[3]Experto\n");
		printf("indique el modo de juego:");
		scanf("%d",&mode);
		
		switch(mode){
			case 1 :
				i++;
				break;
			case 2 :
				i++;
				break;
			case 3 :
				i++;
				break; 
			default:
				printf("opcion invalida\n");
				break;
		}	
	}
	return mode;	
}

void startFight(int mode, guardian **enemies){
	
	srand(time(NULL));
	
	int i, j, k;
	

	
	switch(mode){
		case 1 : //3 enemigos
			
			for(i = 0; i < 3; i++){
				
				//guardian *enemy = malloc(sizeof(guardian));
				j = rand()%26;
				
				for(k = 0; k < 3; k++){	
					if(enemies[j]->nombre == enemies[k]->nombre){
						j = rand()%26;
					}
				}
				
				printf("///%d////",j);
				printf("%s",enemies[j]->nombre);
				
				/*
				strcpy(enemy->nombre, enemies[j]->nombre);
				strcpy(enemy->tipo, enemies[j]->tipo);
				enemy->vida = enemies[j]->vida;
				enemy->p_ataque = enemies[j]->p_ataque;
				enemy->p_defensa = enemies[j]->p_defensa;
				*/
			}
			
			//addEmemy();
			 
			break;
			
		case 2 : //5 ememigos
		
			for(i = 0; i < 5; i++){
				
				guardian *enemy = malloc(sizeof(guardian));
				j = rand()%26;
				
				for(k = 0; k < 5; k++){
					if(enemies[j]->nombre == enemies[k]->nombre){
						j = rand()%26;
					}
				}
				
				printf("///%d////",j);
				printf("%s",enemies[j]->nombre);
				
					/*
				strcpy(enemy->nombre, enemies[j]->nombre);
				strcpy(enemy->tipo, enemies[j]->tipo);
				enemy->vida = enemies[j]->vida;
				enemy->p_ataque = enemies[j]->p_ataque;
				enemy->p_defensa = enemies[j]->p_defensa;
				*/
			
				
			}
			
			break;
			
		case 3 : //7 ememigos
			
			for(i = 0; i < 7; i++){
				
				//guardian *enemy = malloc(sizeof(guardian));
				j = rand()%26;
				
				for(k = 0; k < 7; k++){
					if(enemies[j]->nombre == enemies[k]->nombre){
						printf("##hi##");
						j = rand()%26;
					}
				}
				
				printf("///%d////",j);
				printf("%s",enemies[j]->nombre);
				
				/*
				strcpy(enemy->nombre, enemies[j]->nombre);
				strcpy(enemy->tipo, enemies[j]->tipo);
				enemy->vida = enemies[j]->vida;
				enemy->p_ataque = enemies[j]->p_ataque;
				enemy->p_defensa = enemies[j]->p_defensa;
				*/
				
			}
			break; 
	}
}


void initEnemy(guardian **enemies) {
	FILE *fp = fopen("personaje.txt", "r");
	if (fp == NULL) {
		printf("Error al abrir el archivo\n");
		return;
	}
	char nombre[M];
	char tipo[N];
	int vida;
	int p_ataque;
	int p_defensa;
	int i = 0;
	while (fscanf(fp, "%s %s %d %d %d", nombre, tipo, &vida, &p_ataque, &p_defensa) == 5) {
		guardian *e = malloc(sizeof(guardian));
		
		strcpy(e->nombre, nombre);
		strcpy(e->tipo, tipo);
		e->vida = vida;
		e->p_ataque = p_ataque;
		e->p_defensa = p_defensa;
		
		enemies[i] = e;
		
		//printf("%d-(%s)-",i,enemies[i]->tipo);
		
		i++;
	}
	fclose(fp);
}


int main(){
	int mode;
	int opt;
	int validar2 = 2;
	int creation;
	
	guardian *enemies[26];
	printf("The Guardians Tournament\n");
	

	node *head = NULL; // Cabeza de la cola de personajes disponibles del juego
	init(&head); // Generar la cola de personajes disponibles
	node *playerHead = NULL; // Cabeza de la cola de personajes seleccionados por el jugador	
/*	
	opt = menuOptions();
	//printf("-------%d--------",opt);

	switch(opt)
	{
		
		case 1 :
			while(validar2 == 2)
				{
				
					printf("Desea crear un personaje o usar uno predeterminado?\n");
					printf("[1] Crear\t[2] Predeterminado\n");
					scanf("%d",&creation);
					
					switch(creation)
					{
						case 1 :
							
							createCharacter(&playerHead);
							validar2++;
							break;
							
						case 2 :
							
							selectCharacter(head, &playerHead);
							validar2++;
							break;
		
						default:
						
							printf("opcion invalida");
							break;
					}	
				}
			break;
		case 2 :
			while(validar2 == 2)
			{
				int i;
				for(i=0;i<2;i++)
				{
					printf("Desea crear un personaje o usar uno predeterminado?\n");
					printf("[1] Crear\t[2] Predeterminado\n");
					scanf("%d",&creation);
						
					switch(creation)
					{
						case 1 :
							
							createCharacter(&playerHead);
							validar2++;
							break;
								
						case 2 :
								
							selectCharacter(head, &playerHead);
							validar2++;
							break;
			
						default:
							
							printf("opcion invalida");
							break;
					}	
				}
			}
			break;
	}
	
	printCharacterStatus(playerHead);
	*/
	mode = selectTournament();
	//printf("%d",mode);
	
	initEnemy(enemies); 
	
	startFight(mode,enemies);
	
	return 0;
}
