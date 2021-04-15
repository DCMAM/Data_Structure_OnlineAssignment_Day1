#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_queue 11

/*
	error:
	1. delete library
	2. random
	3. display duration
*/

struct node{
	char title[18];
	char artist[13];
	int total_genre;
	char genre[3][10];
	int year;
	int duration;
	struct node* next;
};

struct node* head = NULL;
struct node* tail = NULL;

int total_song = 0;
int total_queue = 0;

char queue_title[max_queue][18];
char queue_artist[max_queue][13];
int queue_total_genre[max_queue];
char queue_genre[max_queue][3][10];
int queue_year[max_queue];
int queue_duration[max_queue];

struct node* createNewNode(char title[], char artist[], int total_genre, char genre[][10], int year, int duration){
	struct node* createdNode = (struct node*)malloc(sizeof(struct node));

	strcpy(createdNode->title, title);
	strcpy(createdNode->artist, artist);
	createdNode->total_genre = total_genre;
	for(int i=0; i<total_genre; i++){
		strcpy(createdNode->genre[i], genre[i]);	
	}
	createdNode->year = year;
	createdNode->duration = duration;	

	createdNode->next = NULL;
	
	total_song++;
	
	return createdNode;
}

void view_all_node(){
	struct node* curr = head;
	
	if(curr == NULL){
		printf("There's no node!'");
	}
	else{
		printf("+-----------------------------------------------------------------------------------------+\n");
		printf("| %4s | %-15s | %-10s | %-4s | %-24s | %-8s | %-4s |\n", "KEY", "TITLE", "ARTIST", "TGEN", "GENRE", "DURATION", "YEAR");
		printf("+-----------------------------------------------------------------------------------------+\n");
		int i=1;
		while(curr != NULL){
			printf("| %4d | %-15s | %-10s | %-4d | ", i, curr->title, curr->artist, curr->total_genre);
			for(int j=0; j<curr->total_genre; j++){
				printf("%-7s ", curr->genre[j]); 
			}
			for(int j=3; j>curr->total_genre; j--){
				printf("%-7s ", " "); 
			}
			printf(" | %-8d | %-4d |\n", curr->duration, curr->year);
			i++;
			curr = curr->next;
		}
		printf("+-----------------------------------------------------------------------------------------+\n");
	}
}

void pushTail(char title[], char artist[], int total_genre, char genre[][10], int year, int duration){
	struct node* toInsert = createNewNode( title,  artist,  total_genre,  genre,  year,  duration);
	if(tail == NULL){
		head = toInsert;
		tail = toInsert;
	}
	else {
		tail->next = toInsert;
		tail = toInsert;
	}
}

void popHead(){
	if(head != NULL){
		struct node* curr = head;
		
		if(head == tail){
			head == NULL;
			tail == NULL;
		}
		else{
			head = head->next;
		}
		free(curr);
	}
}

void popTail(){
	if(head != NULL){
		struct node* curr = head;
		
		if(head == tail){
			head == NULL;
			tail == NULL;
			
			free(curr);
		}
		else{
			while(curr->next != tail){
				curr = curr->next;
			}
			free(curr->next);
			curr->next = NULL;
			tail = curr;	
		}
	}
}

void popAll(){
	while(head != NULL){
		popTail();
	}
}

void print_menu(){
	printf("SPOTIDZ\n");
	printf("=======\n");
	printf("1. Add\n");
	printf("2. Search\n");
	printf("3. Delete\n");
	printf("4. View\n");
	printf("5. Random Music Queue\n");
	printf("6. Export Music Library to txt\n");
	printf("0. Exit\n");
	printf(">> ");
}

void new_music(){
	char title[18];
	char artist[13];
	int total_genre;
	char genre[3][10];
	int year;
	int duration;
	printf("ADD NEW MUSIC TO THE LIBRARY\n");
	printf("----------------------------\n");
	do{
		printf("Title (max 15 characters) : ");
		scanf("%[^\n]", title); getchar();
	}while(strlen(title) > 15 || strlen(title) < 1);
	do{
		printf("Artist [must be filled] (max 10 characters) : ");
		scanf("%[^\n]", artist); getchar();
	}while(strlen(artist) > 10 || strlen(artist) < 1);
	do{
		printf("Amount of genre [max : 3] : ");
		scanf("%d", &total_genre); getchar();
	}while(total_genre > 3 || total_genre < 1);
	for(int i=0; i<total_genre; i++){
		do{
			printf("Genre %d [must be unique] (max : 5 characters) : ", i+1);
			scanf("%[^\n]", genre[i]); getchar();
		}while(strlen(genre[i]) > 5 || strlen(genre[i]) < 1);
	}
	do{
		printf("Year [1900 - 2021] : ");
		scanf("%d", &year); getchar();
	}while(year > 2021 || year < 1900);
	do{
		printf("Duration [max 3599s] : ");
		scanf("%d", &duration); getchar();
	}while(duration > 3599 || duration < 1);	
	
	pushTail( title,  artist,  total_genre,  genre,  year,  duration);
	
	printf("\nNEW MUSIC DETAIL\n");
	printf("----------------\n");
	printf("Title    : %s\n", title);
	printf("Artist   : %s\n", artist);
	printf("Genre    :");
	for(int i=0; i<total_genre; i++){
		printf(" %s", genre[i]);
	}
	printf("\n");
	printf("Duration : %d\n", duration);
	printf("Year     : %d\n\n", year);
}

void add_to_queue(int loop){
	struct node* curr = head;
	
	if(curr == NULL){
		printf("There's no node!'");
	}
	else{
		int i=1;
		while(curr != NULL){
			if(i == loop){
				strcpy(queue_title[total_queue], curr->title);
				strcpy(queue_artist[total_queue], curr->artist);
				queue_total_genre[total_queue] = curr->total_genre;
				for(int j=0; j<curr->total_genre; j++){
					strcpy(queue_genre[total_queue][j], curr->genre[j]);
				}
				queue_year[total_queue] = curr->year;
				queue_duration[total_queue] = curr->duration;
				
				total_queue++;
			}
			i++;
			curr = curr->next;
		}
	}
}

void music_queue(){
	system("cls");
	if(total_queue == 10) {
		printf("Queue is full!\n");	
		return;
	}
	view_all_node();
	int menu=0;
	do{
		printf("\n0 : EXIT\n");
		printf("Choose music's key to be added to queue : ");
		scanf("%d", &menu); getchar();
		if(menu == 0) break;
		else if(menu <= total_queue || menu >= 1){
			add_to_queue(menu);
			printf("Music has been added to queue !!!\n");
			break;
		}	
		system("pause");
	}while(1);
}

void menu_1(){
	int menu=0;
	do{
		system("cls");
		printf("1. New music to Library\n");
		printf("2. Music Queue\n");
		printf("0. Exit\n");
		printf(">> ");
		scanf("%d", &menu); getchar();
		if(menu == 0) break;
		else if(menu == 1) new_music();
		else if(menu == 2) music_queue();
		system("pause");
	}while(1);
}

void search_by_genre(char genre[]){
	struct node* curr = head;
	
	if(curr == NULL){
		printf("There's no node!'");
	}
	else{
		
		printf("+-----------------------------------------------------------------------------------------+\n");
		printf("| %4s | %-15s | %-10s | %-4s | %-24s | %-8s | %-4s |\n", "KEY", "TITLE", "ARTIST", "TGEN", "GENRE", "DURATION", "YEAR");
		printf("+-----------------------------------------------------------------------------------------+\n");
		int i=1;
		while(curr != NULL){
			for(int j=0;j<3;j++){
				if(strcmp(genre, curr->genre[j]) == 0){
					printf("| %4d | %-15s | %-10s | %-4d | ", i, curr->title, curr->artist, curr->total_genre);
					for(int j=0; j<curr->total_genre; j++){
						printf("%-7s ", curr->genre[j]); 
					}
					for(int j=3; j>curr->total_genre; j--){
						printf("%-7s ", " "); 
					}
					printf(" | %-8d | %-4d |\n", curr->duration, curr->year);
					i++;
				}
			}
			curr = curr->next;
		}
		printf("+-----------------------------------------------------------------------------------------+\n");
		
	}
}

void search_by_artist(char name[]){
	struct node* curr = head;
	
	if(curr == NULL){
		printf("There's no node!'");
	}
	else{
		
		printf("+-----------------------------------------------------------------------------------------+\n");
		printf("| %4s | %-15s | %-10s | %-4s | %-24s | %-8s | %-4s |\n", "KEY", "TITLE", "ARTIST", "TGEN", "GENRE", "DURATION", "YEAR");
		printf("+-----------------------------------------------------------------------------------------+\n");
		int i=1;
		while(curr != NULL){
			if(strcmp(name, curr->artist) == 0){
				printf("| %4d | %-15s | %-10s | %-4d | ", i, curr->title, curr->artist, curr->total_genre);
				for(int j=0; j<curr->total_genre; j++){
					printf("%-7s ", curr->genre[j]); 
				}
				for(int j=3; j>curr->total_genre; j--){
					printf("%-7s ", " "); 
				}
				printf(" | %-8d | %-4d |\n", curr->duration, curr->year);
				i++;
			}
			curr = curr->next;
		}
		printf("+-----------------------------------------------------------------------------------------+\n");
	}
}

void search_by_title(char title[]){
	struct node* curr = head;
	
	if(curr == NULL){
		printf("There's no node!'");
	}
	else{
		
		printf("+-----------------------------------------------------------------------------------------+\n");
		printf("| %4s | %-15s | %-10s | %-4s | %-24s | %-8s | %-4s |\n", "KEY", "TITLE", "ARTIST", "TGEN", "GENRE", "DURATION", "YEAR");
		printf("+-----------------------------------------------------------------------------------------+\n");
		int i=1;
		while(curr != NULL){
			if(strcmp(title, curr->title) == 0){
				printf("| %4d | %-15s | %-10s | %-4d | ", i, curr->title, curr->artist, curr->total_genre);
				for(int j=0; j<curr->total_genre; j++){
					printf("%-7s ", curr->genre[j]); 
				}
				for(int j=3; j>curr->total_genre; j--){
					printf("%-7s ", " "); 
				}
				printf(" | %-8d | %-4d |\n", curr->duration, curr->year);
				i++;
			}
			curr = curr->next;
		}
		printf("+-----------------------------------------------------------------------------------------+\n");
	}
}

void menu_2(){
	int option=0;
	do{
		system("cls");
		printf("SEARCH MUSIC\n");
		printf("------------\n");
		printf("1. Search by Genre\n");
		printf("2. Search by Artist\n");
		printf("3. Search by Title\n");
		printf("0. Exit\n");
		printf(">> ");
		scanf("%d", &option); getchar();
		if(option==0) break;
		else if(option == 1) {
			char genre[10];
			view_all_node();
			do{
				printf("Input the music's genre to be searched (max 5 characters) : ");
				scanf("%[^\n]", genre); getchar();
			}while(strlen(genre) > 5);
			search_by_genre(genre);
		}
		else if(option == 2){
			char artist[10];
			view_all_node();
			do{
				printf("Input the music's artist name to be searched (max 10 characters) : ");
				scanf("%[^\n]", artist); getchar();
			}while(strlen(artist) > 10);
			search_by_artist(artist);
		}
		else if(option == 3){
			char title[10];
			view_all_node();
			do{
				printf("Input the music's title to be searched (max 15 characters) : ");
				scanf("%[^\n]", title); getchar();
			}while(strlen(title) > 15);
			search_by_title(title);
		}
		system("pause");
	}while(1);
}

void delete_library(int index){
	if(head != NULL){
		struct node* curr = head;
		
		int i=1;
		while(curr->next != NULL){
			if(i== index) break;
			i++;
			curr = curr->next;
		}
		
		if(curr->next != NULL){
			struct node* toDelete = curr->next;
			curr->next = toDelete->next;
			free(toDelete);
		}
	}
}

void delete_queue(int index){
	for(int i=0; i<total_queue; i++){
		if(i>index){
			strcpy(queue_title[i-1],  queue_title[i]);
			strcpy(queue_artist[i-1], queue_artist[i]);
			queue_total_genre[i-1] = queue_total_genre[i];
			for(int j=0; j<queue_total_genre[i-1]; j++){
				strcpy(queue_genre[i-1][j], queue_genre[i][j]);
			}
			queue_year[i-1] = queue_year[i];
			queue_duration[i-1] = queue_duration[i];
		}
	}
	total_queue--;
}

void view_all_queue(){
	printf("+-----------------------------------------------------------------------------------------+\n");
		printf("| %4s | %-15s | %-10s | %-4s | %-24s | %-8s | %-4s |\n", "KEY", "TITLE", "ARTIST", "TGEN", "GENRE", "DURATION", "YEAR");
		printf("+-----------------------------------------------------------------------------------------+\n");
		int i=0;
		while(i<total_queue){
			printf("| %4d | %-15s | %-10s | %-4d | ", i+1, queue_title[i], queue_artist[i], queue_total_genre[i]);
			for(int j=0; j<queue_total_genre[i]; j++){
				printf("%-7s ", queue_genre[i][j]); 
			}
			for(int j=3; j>queue_total_genre[i]; j--){
				printf("%-7s ", " "); 
			}
			printf(" | %-8d | %-4d |\n", queue_duration[i], queue_year[i]);
			i++;
		}
		printf("+-----------------------------------------------------------------------------------------+\n");
	
}

void menu_3(){
	int option=0;
	do{
		printf("DELETE\n");
		printf("------\n");
		printf("1. Delete Music from Library\n");
		printf("2. Delete Music from Queue\n");
		printf(">> ");
		scanf("%d", &option);
		if(option == 0) break;
		else if(option == 1){
			int index;
			view_all_node();
			do{
				printf("0 : EXIT\n");
				printf("Choose music's key to be deleted from library : ");
				scanf("%d", &index); getchar();
				if(index == 0 ) break;
				else if(index > total_song) break;
				else {
					if(index == total_song && total_song == 1) popHead();
					else if(index == total_song && total_song >= 1) popTail();
					else if(index > 1 || index < total_song) delete_library(index);
					total_song--;
					break;
				}
			}while(1);
		}
		else if(option == 2){
			int index;
			view_all_queue();
			do{
				printf("0 : EXIT\n");
				printf("Choose music's key to be deleted from queue : ");
				scanf("%d", &index); getchar();
				if(index == 0 ) break;
				else{
					delete_queue(index-1);	
					break;		
				}
			}while(index > total_queue);
		}
	}while(1);
}

void menu_4(){
	system("cls");
	int option=0;
	do{
		printf("VIEW\n");
		printf("----\n");
		printf("1. Music Library\n");
		printf("2. Music Queue\n");
		printf("0. Exit\n");
		printf(">> ");
		scanf("%d", &option);
		if(option==0) break;
		else if(option==1) view_all_node();
		else if(option==2) view_all_queue();
	}while(1);
}

void menu_5(){
	while(total_queue < 10){
		int random = (rand()%total_song)+1;
		if(random != 0){
			add_to_queue(random);
			total_queue++;
		}
	}
}

void menu_6(){
	FILE *fp = fopen("song-list.txt", "a+");
	struct node* curr = head;
	
	if(curr == NULL){
		return;
	}
	else{
		int i=1;
		while(curr != NULL){
			fprintf(fp, "%d - %s - %s - %-d - ", i, curr->title, curr->artist, curr->total_genre);
			for(int j=0; j<curr->total_genre; j++){
				if(j == curr->total_genre-1) fprintf(fp, "%s ", curr->genre[j]);
				else fprintf(fp, "%s ; ", curr->genre[j]); 
			}
			fprintf(fp, "- %d - %d\n", curr->year, curr->duration);
			i++;
			curr = curr->next;
		}
	}
	printf("Music library has been exported into 'song-list.txt'\n");
}


int main(){
	srand(time(NULL));
	
	int menu=0;
	do{
		system("cls");
		print_menu();
		scanf("%d", &menu); getchar();
		if(menu==1) menu_1();
		else if(menu==2) menu_2();
		else if(menu==3) menu_3();
		else if(menu==4) menu_4();
		else if(menu==5) menu_5();
		else if(menu==6) menu_6();
		else if(menu==0) {
//			popAll();	
			break;
		}
		system("pause");
	}while(1);
	return 0;
}
