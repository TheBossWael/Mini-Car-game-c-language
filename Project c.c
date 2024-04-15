#include <stdio.h>
#include <string.h>
#include <time.h>
#include<stdlib.h>
#include <windows.h>
#include <conio.h>

/*----------------------------------------------------------*/
/*                   global-variables                       */
/*----------------------------------------------------------*/

int i;int j;
int car_position;
int obstacle_position;
int gameover;
#define ROWS 26
#define COLS 29
struct Node* head = NULL;
char track[ROWS][COLS];

/*----------------------------------------------------------*/
/*                   global-variables                       */
/*----------------------------------------------------------*/


/*----------------------------------------------------------*/
/*              data-base part/chained list-file            */
/*----------------------------------------------------------*/

// structure de chaque node dans la liste chainee
struct Node {
    char username[10];  // Assuming a maximum username length of 50 characters
    int score;
    struct Node* next;
};

// create a new node with given username and score
struct Node* createNode(char username[], int score) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    strncpy(newNode->username, username, sizeof(newNode->username) - 1);
    newNode->username[sizeof(newNode->username) - 1] = '\0';  // Ensure null-terminated string
    newNode->score = score;
    newNode->next = NULL;
    
    return newNode;
}

// insert a new node at the end of the linked list
void insertNode(struct Node** head, char username[], int score) {
    struct Node* newNode = createNode(username, score);
    
    if (*head == NULL) {
        // If the list is empty, make the new node the head
        *head = newNode;
    } else {
        // Traverse the list to find the last node
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        
        // Attach the new node to the last node
        temp->next = newNode;
    }
}


void saveListToFile(struct Node* head, const char* filepath) {
    FILE* file = fopen(filepath, "a");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", filepath);
        exit(EXIT_FAILURE);
    }

    while (head != NULL) {
        fprintf(file, "\t\t\t Username: %s, Score: %d\n", head->username, head->score);
        head = head->next;
    }

    fclose(file);
}

void free_memory(){

    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void insertnode_and_savetofile(const char* username,int score){
    
    // Insert nodes with scores and usernames
    insertNode(&head, username, score);

    // save list to file
    saveListToFile(head, "Z:\\Downloads\\output\\Data_Base (Car_Game).txt");
    
    //free the memory when done with the list

    free_memory();
}

void read_Data_Base_file(char* User_Name) {
    FILE *fh = fopen("Z:\\Downloads\\output\\Data_Base (Car_Game).txt", "r");

    if (fh != NULL) {
        char c,input;
        system("cls");
        printf("\n\n\n\n\n\n\n\n");
        while ((c = fgetc(fh)) != EOF) {
           printf("%c",c);
        }
        printf("\n\t\t\t press G and enter to go back to main menu\n\t\t\t  >");
        do {
            scanf(" %c", &input); 
        } while (input != 'g' && input != 'G');

        if (input == 'g' || input == 'G') {
            menu(User_Name);
        }
        fclose(fh);
    } else {
        printf("Error opening file.\n");
    }
}

/*----------------------------------------------------------*/
/*              data-base part/chained list-file            */
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*               windows-terminal fonctions                 */
/*----------------------------------------------------------*/

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
void loading(){
	int i=0;
	printf("\nLOADING");
	for(i=0;i<=6;i++)
	{
	  delay(125);
	  printf(". ");
	 }
	printf("\n");

}

int screen_size(int *rows, int *cols)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Get console screen buffer information
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        // Store rows and columns in the provided pointers
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        return 0;
    }
  }

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void print_text_in_middle(int rows, int cols, const char *text) {
    int len = strlen(text);
    int spaces = (cols - len) / 2;

    for (int i = 0; i < rows / 3; i++) {
        printf("\n");
    }

    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("%s", text);
}

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*----------------------------------------------------------*/
/*               windows-terminal functions                 */
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*                  Game related functions                  */
/*----------------------------------------------------------*/

void remplir_track_rows(int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++) {
					//debut-fin track
            if (j == 0 || j == COLS - 1) {
                track[i][j] = '|';
            } 
						//mid track
						else if (j == COLS / 2 && i%2!=0) {
                track[i][j] = '|';
            } 
						//rest du track
						else {
                track[i][j] = ' ';
            }
        }
    }
}

void print_track(int rows) {
     printf("\n\n\t\t\t\t");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++) {
            
            printf("%c", track[i][j]);
            
        }
     printf("\n\t\t\t\t");
    }
}

void input_control(){
    if (_kbhit()) {

        int input =_getch();
            switch (input) 
            {
                case 'Q':
                case 'q':
                    remove_car();
                    car_left();
                    break;
                case 'd':
                case 'D':
                    remove_car();
                    car_right();
                    break;

                case 'g':
                  printf("\nQuitting the program\n");
                    system('exit');
            } }
}


void car_left(){
    //car wheels
track[ROWS-4][5]='0';
track[ROWS-4][9]='0';
track[ROWS-2][5]='0';
track[ROWS-2][9]='0';
    //car body
track[ROWS-4][6]='-';
track[ROWS-4][7]='-';
track[ROWS-4][8]='-';
track[ROWS-3][6]='|';
track[ROWS-3][8]='|';
track[ROWS-2][6]='-';
track[ROWS-2][7]='-';
track[ROWS-2][8]='-';
car_position=1;
}

void car_right(){
    //car wheels
track[ROWS-4][19]='0';
track[ROWS-4][23]='0';
track[ROWS-2][19]='0';
track[ROWS-2][23]='0';
    //car body
track[ROWS-4][20]='-';
track[ROWS-4][21]='-';
track[ROWS-4][22]='-';
track[ROWS-3][20]='|';
track[ROWS-3][22]='|';
track[ROWS-2][20]='-';
track[ROWS-2][21]='-';
track[ROWS-2][22]='-';
car_position=2;
}

void remove_car(){
    //remove left_car
    //car wheels
track[ROWS-4][5]=' ';
track[ROWS-4][9]=' ';
track[ROWS-2][5]=' ';
track[ROWS-2][9]=' ';
    //car body
track[ROWS-4][6]=' ';
track[ROWS-4][7]=' ';
track[ROWS-4][8]=' ';
track[ROWS-3][6]=' ';
track[ROWS-3][8]=' ';
track[ROWS-2][6]=' ';
track[ROWS-2][7]=' ';
track[ROWS-2][8]=' ';
    //remove right_car
    //car wheels
track[ROWS-4][19]=' ';
track[ROWS-4][23]=' ';
track[ROWS-2][19]=' ';
track[ROWS-2][23]=' ';
    //car body
track[ROWS-4][20]=' ';
track[ROWS-4][21]=' ';
track[ROWS-4][22]=' ';
track[ROWS-3][20]=' ';
track[ROWS-3][22]=' ';
track[ROWS-2][20]=' ';
track[ROWS-2][21]=' ';
track[ROWS-2][22]=' ';    
}

void reprint_car_when_obstacle_is_removed(){

        if (car_position==1){
            car_left();
        }
        if (car_position==2){
            car_right();
        }
}

void car_obstacle_left(int i){
    //car wheels
track[1+i][5]='0';
track[1+i][9]='0';
track[3+i][5]='0';
track[3+i][9]='0';
    //car body
track[1+i][6]='-';
track[1+i][7]='-';
track[1+i][8]='-';
track[2+i][6]='|';
track[2+i][8]='|';
track[3+i][6]='-';
track[3+i][7]='-';
track[3+i][8]='-';
    //car wheels remove
track[0+i][5]=' ';
track[0+i][9]=' ';
track[2+i][5]=' ';
track[2+i][9]=' ';
    //car body remove
track[0+i][6]=' ';
track[0+i][7]=' ';
track[0+i][8]=' ';
track[2+i][7]=' ';
if((i==ROWS-7)){
obstacle_position=1;
}

}

void car_obstacle_right(int i){

    //car wheels
track[1+i][19]='0';
track[1+i][23]='0';
track[3+i][19]='0';
track[3+i][23]='0';
    //car body
track[1+i][20]='-';
track[1+i][21]='-';
track[1+i][22]='-';
track[2+i][20]='|';
track[2+i][22]='|';
track[3+i][20]='-';
track[3+i][21]='-';
track[3+i][22]='-';
    //car wheels remove
track[0+i][19]=' ';
track[0+i][23]=' ';
track[2+i][19]=' ';
track[2+i][23]=' ';
    //car body remove
track[0+i][20]=' ';
track[0+i][21]=' ';
track[0+i][22]=' ';
track[2+i][21]=' ';

if((i==ROWS-7)){
obstacle_position=2;
}

}

void remove_obstacle_in_end_of_track(){
  if (obstacle_position==1 || obstacle_position==2 || obstacle_position==3 ){
   //remove right car
/*................................................................*/
    //car wheels remove

track[ROWS-1][19]=' ';
track[ROWS-1][23]=' ';
track[ROWS-3][19]=' ';
track[ROWS-3][23]=' ';
    //car body remove
track[ROWS-1][20]=' ';
track[ROWS-1][21]=' ';
track[ROWS-1][22]=' ';
track[ROWS-2][20]=' ';
track[ROWS-2][21]=' ';
track[ROWS-2][22]=' ';
track[ROWS-3][20]=' ';
track[ROWS-3][21]=' ';
track[ROWS-3][22]=' ';


   //remove left car
/*................................................................*/
    //car wheels remove
track[ROWS-1][5]=' ';
track[ROWS-1][9]=' ';
track[ROWS-3][5]=' ';
track[ROWS-3][9]=' ';
    //car body remove
track[ROWS-1][6]=' ';
track[ROWS-1][7]=' ';
track[ROWS-1][8]=' ';
track[ROWS-2][6]=' ';
track[ROWS-2][7]=' ';
track[ROWS-2][8]=' ';
track[ROWS-3][6]=' ';
track[ROWS-3][7]=' ';
track[ROWS-3][8]=' ';
    }
}

void car_obstacle_random_choice(int random,int i) {
    if (random == 0) {

        car_obstacle_left(i++);

    } else {
        
        car_obstacle_right(i++);
        
    }
}

void car_obstacle2_random_choice(int random2,int j) {
    if (random2 == 0) {

        car_obstacle_left(j++);

    } else {
        
        car_obstacle_right(j++);
        
    }
}


int Crash(){
    if((car_position==obstacle_position) && (car_position!=0)){
      
      return gameover=1;
    }
}

void gameover_screen(){
    
   //GAMEOVER TEXT
    track[ROWS/2][COLS/2-4]='G';
    track[ROWS/2][COLS/2-3]='A';
    track[ROWS/2][COLS/2-2]='M';
    track[ROWS/2][COLS/2-1]='E';
    track[ROWS/2][COLS/2]='-';
    track[ROWS/2][COLS/2+1]='O';
    track[ROWS/2][COLS/2+2]='V';
    track[ROWS/2][COLS/2+3]='E';
    track[ROWS/2][COLS/2+4]='R';

    //upper line
    track[ROWS/2-2][COLS/2]='|';
    track[ROWS/2-2][COLS/2-1]='_';
    track[ROWS/2-2][COLS/2-2]='_';
    track[ROWS/2-2][COLS/2-3]='_';
    track[ROWS/2-2][COLS/2-4]='_';
    track[ROWS/2-2][COLS/2-5]='_';
    track[ROWS/2-2][COLS/2-6]='_';
    track[ROWS/2-2][COLS/2-7]='_';
    track[ROWS/2-2][COLS/2-8]='_';
    track[ROWS/2-2][COLS/2-9]='_';
    track[ROWS/2-2][COLS/2-10]='_';
    track[ROWS/2-2][COLS/2-11]='_';
    track[ROWS/2-2][COLS/2-12]='_';
    track[ROWS/2-2][COLS/2-13]='_';
    track[ROWS/2-2][COLS/2+1]='_';
    track[ROWS/2-2][COLS/2+2]='_';
    track[ROWS/2-2][COLS/2+3]='_';
    track[ROWS/2-2][COLS/2+4]='_';
    track[ROWS/2-2][COLS/2+5]='_';
    track[ROWS/2-2][COLS/2+6]='_';
    track[ROWS/2-2][COLS/2+7]='_';
    track[ROWS/2-2][COLS/2+8]='_';
    track[ROWS/2-2][COLS/2+9]='_';
    track[ROWS/2-2][COLS/2+10]='_';
    track[ROWS/2-2][COLS/2+11]='_';
    track[ROWS/2-2][COLS/2+12]='_';
    track[ROWS/2-2][COLS/2+13]='_';
        //lower line
    track[ROWS/2+1][COLS/2]='_';
    track[ROWS/2+1][COLS/2-1]='_';
    track[ROWS/2+1][COLS/2-2]='_';
    track[ROWS/2+1][COLS/2-3]='_';
    track[ROWS/2+1][COLS/2-4]='_';
    track[ROWS/2+1][COLS/2-5]='_';
    track[ROWS/2+1][COLS/2-6]='_';
    track[ROWS/2+1][COLS/2-7]='_';
    track[ROWS/2+1][COLS/2-8]='_';
    track[ROWS/2+1][COLS/2-9]='_';
    track[ROWS/2+1][COLS/2-10]='_';
    track[ROWS/2+1][COLS/2-11]='_';
    track[ROWS/2+1][COLS/2-12]='_';
    track[ROWS/2+1][COLS/2-13]='_';
    track[ROWS/2+1][COLS/2+1]='_';
    track[ROWS/2+1][COLS/2+2]='_';
    track[ROWS/2+1][COLS/2+3]='_';
    track[ROWS/2+1][COLS/2+4]='_';
    track[ROWS/2+1][COLS/2+5]='_';
    track[ROWS/2+1][COLS/2+6]='_';
    track[ROWS/2+1][COLS/2+7]='_';
    track[ROWS/2+1][COLS/2+8]='_';
    track[ROWS/2+1][COLS/2+9]='_';
    track[ROWS/2+1][COLS/2+10]='_';
    track[ROWS/2+1][COLS/2+11]='_';
    track[ROWS/2+1][COLS/2+12]='_';
    track[ROWS/2+1][COLS/2+13]='_';



}

void game(char *User_Name) {
        int random2=0;int random=0;
       int score=0;
       int lvl=0;
        int rows=26 ;// Number of rows in the track
		int i=0,j=0;
        int time=500;
    // Call the function to fill the track :
        remplir_track_rows(rows);
		hideCursor();
        car_left(); // call player car at beginning of the game
/*----------------------------------------------------------*/
/*                     game-cycle                           */
/*----------------------------------------------------------*/
        do
        {	
            
          input_control();
          // obsticles part:
		  static int lastUpdateTime = 0;
          int currentTime = GetTickCount();  
          if (currentTime - lastUpdateTime >= (time)) {

/*-----------------------obstical car 2------------------------------*/
                   car_obstacle_random_choice(random,i++);

/*when obstical car*/    if(i==ROWS-3){  
/*reaches end of track*/    i=0;
                            if (time>0){
                                // lvl up + speed up + set position to remove 
                                lvl+=1;time=time-100; 
                            }
                            remove_obstacle_in_end_of_track();obstacle_position=3; 
                            reprint_car_when_obstacle_is_removed();
                            random = rand() % 2;
                        }
/*-----------------------obstical car 2------------------------------*/
/*when obstical car*/      if(i==ROWS-13)   {
/*reaches mid of track*/    j=0;
                            remove_obstacle_in_end_of_track();obstacle_position=3; 
                            reprint_car_when_obstacle_is_removed();
                            random2 = rand() % 2;
                          }
                          car_obstacle2_random_choice(random2,j++);
                          

					lastUpdateTime = currentTime;
				}
          Crash();
        //score+level part :
          score=score+1;
        //  printf("\n\t\t\t\t%d\n",random);
        //  printf("\n\t\t\t\t%d\n",random2);
          printf("\n\t\t\t\tLevel: %i\n",lvl);
          printf("\t\t\t\tscore: %i\n",score);
          printf("\t\t\t\tpress g to exit game");
		  delay(115);
		  system("cls");
          print_track(rows);

          } while(!gameover);
                            

/*----------------------------------------------------------*/
/*                    IF gameover                           */
/*----------------------------------------------------------*/
          if (gameover==1)
        {
          system("cls");
          gameover_screen();
          car_position=0;obstacle_position=0;gameover=0;i=0;j=0; //reset positions
          print_track(rows); //print the track with gameover tag
          insertnode_and_savetofile(User_Name,score); // save score to file
          system("pause");
          main();
         }                             
    

		}

/*----------------------------------------------------------*/
/*                  Game related functions                  */
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*                           MENUS                          */
/*----------------------------------------------------------*/
void menu(char *User_Name)
{
int rows, cols;
char *getUsername();

int choice;
system("cls");
system("color 7");

if (screen_size(&rows, &cols) == 0) {

        print_text_in_middle(rows, cols, "this is Wael's Project ");
        print_text_in_middle(7, cols-10, "\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU "); 
        setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY); //color red
        printf("%s ", User_Name);
        setConsoleColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED); //reset color
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        print_text_in_middle(6,cols-39, "[1] Start");           //START HAS 9 CHAR
        print_text_in_middle(4,cols-29, "[2] Change Username"); //HAS 19 CHAR => 39-10=29
       // print_text_in_middle(4, cols-31, "[3] Game settings");  //HAS 17 CHAR
        print_text_in_middle(4, cols-28, "[3] Check Scoreboard");//HAS 20CHAR
        print_text_in_middle(4, cols-40, "[4] Exit");            //HAS 9 CHAR
        print_text_in_middle(6, cols-21, "Enter your choice: ");

    }
    scanf("%d",&choice);

switch(choice)
  {
    case 1:
         // Start the game and pass the username
            game(User_Name);
        break;
    case 2:
        loading();
        system("cls");
        char *username = getUsername();
    case 3:
        read_Data_Base_file(User_Name);
    case 4:
        system('exit');

   }
}

char *getUsername()
{
    char *User_Name = (char *)malloc(10 * sizeof(char)); // Allocate memory for the username
    int rows, cols;
if (screen_size(&rows, &cols) == 0) {

    if (User_Name == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    print_text_in_middle(rows,cols,"Welcome to the GAME ");
    print_text_in_middle(5,cols,"............. ");
    print_text_in_middle(5,cols,"Enter Username to Play:");
     print_text_in_middle(5, cols-21, "> ");
    scanf("%s",User_Name);

   if (strlen(User_Name) >= 3 && strlen(User_Name) <= 10)
      {
		printf("\n\n Username is Valid!");
		loading(); //call loading fonction
		system("cls");
	    menu(User_Name);    //call menu fonction
      }
else
        {
			printf("\n\nUsername should be between 3 and 10 characters!!\a\a\a");
            printf("\ntry again\n");
            system("pause");
            system("cls");
            free(User_Name);
           	getUsername();

 
}
}
return User_Name;
}



int main(){

    system("cls");
	// get username call
    char *User_Name = getUsername();


    return 0;

 }

