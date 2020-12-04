//program ini ga selesai ko, cuma selesai menu 1 sama 8 aja
//yang lain ada yang jalan, tapi pas jalan ada aneh, soalnya programnya gk selesai
//ko saya boleh minta sesi bahas project ko? atau source code nya
//saya masih kurang mengerti 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

////////////////////STRUCT DISH////////////////
struct warung{
	char name[255];
	int qty, price;
	warung *next, *prev;
} *headDish, *tailDish, *currDish;

warung *createdish(char *name, int qty, int price){
	warung *node = (warung*)malloc(sizeof(warung));
	strcpy(node->name, name);
	node->qty = qty;
	node->price = price;
	node->next = node->prev = NULL;
	return node;
}

//push head struct dish
void pushHead(char *name, int qty, int price){
	warung *node = createdish(name, qty, price);
	if(!headDish){
		headDish = tailDish = node;
	}
	else{
		headDish->prev = node;
		node->next = headDish;
		headDish = node;
	}
}

//push tail struct tail
void pushTail(char *name, int qty, int price){
	warung *node = createdish(name, qty, price);
	if(!headDish){
		headDish = tailDish = node;
	}
	else{
		tailDish->prev = node;
		node->next = tailDish;
		tailDish = node;
	}
}

//push mid struct dish
void pushMid(char *name, int qty, int price){
	if(!headDish){
		warung *node = createdish(name, qty, price);
		headDish = tailDish = node;
	}
	else if(qty < headDish->qty){
		pushHead(name, qty, price);
	}
	else if(qty > tailDish->qty){
		pushTail(name, qty, price);
	}
	else{
		warung *node = createdish(name, qty, price);
		currDish = headDish;
		while(currDish->qty < qty){
			currDish = currDish->next;
		}
		node->prev = currDish->prev;
		node->next = currDish;
		currDish->prev->next = node;
		currDish->prev = node;
	}
}

//pop head struct dish
void popHead(){
	if(headDish && headDish == tailDish){
		headDish = tailDish = NULL;
		free(headDish);
	}
	else{
		warung *newHead = headDish->next;
		headDish->next = newHead->prev = NULL;
		free(headDish);
		headDish = newHead;
	}
}

//pop tail struct dish
void popTail(){
	if(headDish && headDish == tailDish){
		headDish = tailDish = NULL;
	}
	else{
		warung *newtail = tailDish->prev;
		tailDish->prev = newtail->next = NULL;
		free(tailDish);
		tailDish = newtail;
	}
}

//pop mid struct dish
void popMid(int qty){
	if(!headDish){
		return;
	}
	else if(headDish->qty == qty){
		popHead();
	}
	else if(tailDish->qty == qty){
		popTail();
	}
	else{
		currDish = headDish;
		while(currDish && currDish->qty != qty){
			currDish = currDish->next;
		}
		currDish->prev->next = currDish->next;
		currDish->next->prev = currDish->prev;
		currDish->prev = currDish->next = NULL;
		free(currDish);
	}
}

//pop all struct dish, kalo udh exit bbrti hapus semua
void popAll(){
	while(headDish){
		popHead();
	}
}
//-----------------------------------------
////////////////STRUCT ORDER////////////////
struct order{
	char name[255];
	int qty, price;
	order *next, *prev;
}*newOrder, *currOrder, *delOrder;

order *createorder(char *name, int qty, int price){
	order *tmp = (order*)malloc(sizeof(order));
	strcpy(tmp->name, name);
	tmp->qty = qty;
	tmp->price = price;
	tmp->next = tmp->prev = NULL;
	return tmp;
}
//-----------------------------------------
////////////////STRUCT CUSTOMER////////////
struct customer{
	char name[255];
	order *headOrder, *tailOrder;
	customer *next, *prev;
} *headcustomer[26], *tailcustomer[26], *currcustomer[26];

customer *createcus(char *name){
	customer *temp = (customer*)malloc(sizeof(customer));
	strcpy(temp->name, name);
	temp->next = temp->prev = NULL;
	return temp;
}

//djb2
unsigned long DJB2(char *name){
	unsigned long hash = 5381;
	int c;
	while((c = *name++))
		hash = ((hash << 5) + hash) + c;
	return hash % 26;
}

//insert nama customer utk menu 3
void insert(char *name){
	int index = DJB2(name);
	
	if(headcustomer[index]){
		customer *temp = createcus(name);
		tailcustomer[index]->next = temp;
		tailcustomer[index] = temp;
	}
	else{
		headcustomer[index] = tailcustomer[index] = createcus(name);
	}
}

customer* search(char* name){
	int index = DJB2(name);
	while(headcustomer[index] != 0){
		if(headcustomer[index]->name == name){
			return headcustomer[index];
		}
		index++;
		index %= 26;
	}
	return NULL;
}

//-----------------------------------------
const char* detectOS(){
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN64
  return "Windows 64-bit";
  #elif __APPLE__ || __MACH__
  return "Mac OSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #elif __unix || __unix__
  return "Unix";
  #else
  return "Other";
  #endif
}

void datetime(){
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	printf("%s", asctime(tm));
}

void clrscr(){
	for (int i = 0; i < 21; ++i){
		puts("");
	}
}

void mainmenu();
void menu1();
int checklower(char *name);
void defaultmenu();
void menu2();
int checkspace(char *name);
void menu3();
void viewall();
void menu4();
void menu5();
void openfile();
void menu8();
/////////////////////////////////MAIN////////////////////////////////
int main(){
	detectOS();
	datetime();
	defaultmenu();
	mainmenu();
}

void mainmenu(){
	int pilihan;
	do{
		clrscr();
		puts("1. Add Dish");
		puts("2. Remove Dish");
		puts("3. Add Customer");
		puts("4. Search Customer");
		puts("5. View Warteg");
		puts("6. Order");
		puts("7. Payment");
		puts("8. Exit Warteg");
		do{
			printf(">> ");
			scanf("%d", &pilihan);
		}while(pilihan < 1 || pilihan > 8);
		switch(pilihan){
			case 1: //jalan
				clrscr();
				menu1();
				break;
			case 2: //bingung nampilin menunya
				clrscr();
				menu2();
				break;
			case 3: //jalan, tapi ada eror sedikit pas dijalankan
				clrscr();
				menu3();
				break;
			case 4: //jalan, tapi menu 3 blm selesai jd aneh
				clrscr();
				menu4();
				break;
			case 5: //jalan, tapi menu 3 blm selesai jd aneh
				clrscr();
				menu5();
				break;
			case 6: //bingung ko 
				clrscr();
				break;
			case 7: //bingung ko
				clrscr();
				break;
			case 8: //jalan
				clrscr();
				menu8();
				popAll();
				break;
		}
	}while(pilihan != 8);
}

//untuk cek huruf kecil semua, dipake di menu 1 sama 2
int checklower(char *name){
	int len = strlen(name), flag = 0;
	for(int i = 0; i < len; i++){
		if(name[i] >= 'a' && name[i] <= 'z'){
			return 1;
		}
		else{
			return 0;
		}
	}
}

//untuk cek spasi, dipake di menu 3
int checkspace(char *name){
	int len = strlen(name), flag = 0;
	for(int i = 0; i < len; i++){
		if(name[i] == ' '){
			return 1;
		}
		else{
			return 0;
		}
	}
}

//menu1 adddish
void menu1(){
	char name[255];
	int flag = 0, price, qty;
	do{
		printf("Insert the name of the dish [Lowercase letters]: "); getchar();
		scanf("%[^\n]", name); getchar();
		if(checklower(name) == 0){
			flag = 1;
		}
		else{
			flag = 0;
			strcpy(name, name);
		}
	}while(flag == 1);
	do{
		printf("Insert the price of the dish[1000..50000]: ");
		scanf("%d", &price); getchar();
	}while(price < 1000 || price > 50000);
	do{
		printf("Insert the quantity of the dish[1..999]: ");
		scanf("%d", &qty);
	}while(qty < 1 || qty > 999);
	pushMid(name, qty, price);
	puts("The dish has been added!");
	printf("Press enter to continue..."); getchar();
}

//ini default menu, di soal selain nambahin telur asin ada tempe sama buncis
//jadi mungkin (menurut saya aja) tempe sama buncis ini dari default
void defaultmenu(){
	pushMid((char*)"tempe orek", 040, 2500);
	pushMid((char*)"buncis", 001, 6000);
}

//menu2 add dish ga selesai karna bingung gimana nambahin default menu dan nampilinnya
void menu2(){
	puts("/tBude's Menu");
	puts("=======================");
	puts("");//no, name, quality, price;
	
	puts("=======================");
	
}

//menu3 addcustomer
void menu3(){
	char name[255];
	int flag = 0;
	do{
		printf("Insert the customer's name [Without space]: "); getchar();
		scanf("%[^\n]", name); getchar();
		if(checkspace(name) == 0){
			flag = 1;
		}
		else{
			strcpy(name, name);
		}
	}while(flag == 1);
	puts("Customer has been added!");
	printf("Press enter to continue...");
}

//menu 4 search customer, masih bingung karna menu 3 belum selesai
void menu4(){
	char name[255];
	printf("Insert the customer's name to be searched: ");
	scanf("%[^\n]", name);
	search(name);
}

//untuk nampilin customer pas menu 5
void viewall(){
	int count = 0;
	for(int i = 0; i < 26; i++){
		if(headcustomer[i]){
			printf("%d. %s", i, headcustomer[i]->name);
			count++;
		}
		printf("\n");
	}
	if(count == 0) printf("There's no data!\n");
}

//view warteg, ga muncul karna menu 3 belum selesai
void menu5(){
	printf("Customer's List\n");
	viewall();
	printf("Press enter to continue..."); getchar();
}

//open file untuk splash-screen.txt
void openfile(){
	char c;
	FILE *fp = fopen("splash-screen.txt", "r");
	if(fp == NULL){
		printf("Cannot open file\n");
		exit(0);
	}
	c = fgetc(fp);
	while(c != EOF){
		printf("%c", c);
		c = fgetc(fp);
	}
	fclose(fp);
}

//menu 8
void menu8(){
	puts("Please expand your terminal to full screen!");
	openfile();
	printf("Press enter to continue...");
	clrscr();
	//clearscreen
}
