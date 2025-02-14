/** 
 * @file project.c
 * @author Bohdan Ohorodnykov
 * 
 * This is my project for Introduction to Computer Programming course
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#define DECK_SIZE 40

/**
 * @brief A struct for a Card 
 * @param array of suits
 * @param rank of the card 1-7, J=8, Q=9, K=10
 * 
 */
typedef struct{
	char suit[10]; // Clubs Spades...
	int rank; // 1-7, j=8, Q=9, K=10
	int isFaceUp; // 1 if yes 0 if not
}Card;
/**
 * @brief A struct for a Player
 * @param name of a player in string
 * @param variable to store Life Points of a player
 * @param array fo cards of a player
 * @param variable to see if player is eliminated or not
 */
typedef struct
{
	char name[20];// name
	int LP; //life points
	Card cards[2]; // one face down one face up
	int IsEliminated; //1 if yes 0 if not
}Player;
/**
 * @brief A function to initialize a deck of cards using for loop 
 * 
 * @section DESCRIPTION
 * Outer loop goes through suit, while inner loop goes through rank.
 * For each card we assign suit and then assign rank.
 * 
 * @param Array of cards(Deck)
 */
void InitializeDeck(Card* deck){
	const char* suits[]={"Clubs", "Spades", "Diamonds", "Hearts"};
	int rank, suit, cindex=0;
	for (suit=0 ; suit!=4; ++suit){ //for each suit give a rank from 0 to 10;
		for (rank=1; rank<=10; rank++){
			//Assign suit, rank and initial state
			strcpy(deck[cindex].suit, suits[suit]); //assigning suit
			deck[cindex].rank=rank;// assigning a rank
			deck[cindex].isFaceUp=0; // default face down
			cindex++;// next card
		}
	}
}
/**
 * @brief Function to shuffle a deck of 40 cards using random
 * @param Initialized Deck
 */
void ShuffleDeck(Card* Deck){
	srand(time(0));
	for (int i = 0; i < DECK_SIZE; ++i)
	{
		Card tmp=Deck[i]; // random number between 0 and 40
		int j=rand()%DECK_SIZE;
		Deck[i]=Deck[j];
		Deck[j]=tmp; //usual swap
	}
}
/**
 * @brief Function to deal cards to players using for loop. 
 * @section DESCRIPTION
 * For accesing a player we use players[i] and for accesing a card we use special index that does not depend on a loop.
 * @param Initialized and shuffled Deck of cards
 * @param Array of players
 * @param Amount of players
 */
void dealcards(Card* deck, Player* players, int n){
	//for a player in player assign two cards form deck 
	int index=0;
	//iterate over players
	for (int i=0; i!=n; i++){
		players[i].cards[0]=deck[index++];
		players[i].cards[1]=deck[index++];
		players[i].cards[0].isFaceUp=1;
		players[i].cards[1].isFaceUp=0;
		if (index>DECK_SIZE){
			printf("Error: Deck exhausted while dealing cards\n");
			return;
		}
	}
}
/**
 * @brief Function to find next player in Ascending Rind Order.
 * @section DESCRIPTION
 * Implemented as do{}while() loop. 
 * Loop goes through players and changes currentplayer pointer and in the end returns it. 
 * If currentplayer is bigger or equal to players+n, then next player is the first player in array.
 * 
 * @param Array of players
 * @param Amount of players
 * @param Pointer to a current player
 */
Player* NextPlayerARO(Player* players, int  n ,Player* currentplayer){
	Player* start=currentplayer;
	do{	
		//printf("1111\n");
		currentplayer++;
		if (currentplayer>=players+n){
			currentplayer=players;
		}
		if(!currentplayer->IsEliminated){
			return currentplayer;
		}
	}while (currentplayer!=start);
	return NULL;
}
/**
 * @brief Function to find previous player. Implented similar to a NextPlayerARO but goes backwards.
 * @param Array of players
 * @param Amount of players
 * @param Pointer to a current player
 */
Player* PrevPlayerARO(Player* players, int n, Player* currentplayer){
	Player* start=currentplayer;
	do{
		currentplayer--;
		if (currentplayer<players){
			currentplayer=players+n-1;
		}

		if (!currentplayer->IsEliminated){
			return currentplayer;
		}
	}while (currentplayer!=start);

	return NULL;
}

void revealfacedowncard(Player* currentplayer, int n, int* field, Player* players);
/**
 * @brief Function to apply card's effect.
 * 
 * @section DESCRIPTION
 * Cards from 2 to 6 don't have any effect.
 * Card 7 reveals and applies next player's facedown card.
 * Card 8 increases LP of previous player.
 * Card 9 increases LP of next player.
 * Card 10 Player takes al LP from the field.
 * Card 1 Player gives 1 LP to the field.
 * @param rank of the card.
 * @param pointer to a current player.
 * @param pointer to a field.
 * @param array of players.
 * @param amount of players.
 */
void ApplyCardEffect(int card, Player* currentplayer,  int* field, Player* players, int n){ //n amount of players
	if (card>=2 && card<=6){
		printf("\ncards from 2 to 6 does not have any effect\n");
	}else if(card==7){
		Player* next_player=NextPlayerARO(players, n, currentplayer);
		revealfacedowncard(next_player, n ,field, players);
	}else if(card==8){ //?
		Player* prev_player=PrevPlayerARO(players, n, currentplayer); // i need a pointer to previous player
		if (prev_player->LP>=0 && prev_player->LP<2){
			prev_player->LP++;
		}else if(prev_player->LP==2){
			printf("\nPlayer has full LP\n");
			return;
		}
	}else if(card==9){
		Player* next_player=NextPlayerARO(players, n, currentplayer);
		if (next_player->LP>=0 && next_player->LP<2){
			next_player->LP++;	
		}else if (next_player->LP==2){
			printf("\nPlayer has full LP\n");
			return;
		}
	}else if(card==10){	
		if(currentplayer->LP<2 && currentplayer->LP>=0){
			currentplayer->LP+=*field;
			*field=0;
			if (currentplayer->LP>2)
			{
				currentplayer->LP=2;
			}
		}	
	}else if(card==1){
		if (currentplayer->LP>0){
			currentplayer->LP--;
			(*field)++;
		}else{
			printf("Player can't lose a point he is eliminated\n");
		}
	}
}
/**
 * @brief Function to reveal a facedown card of a Player.
 * 
 * @section DESCRIPTION
 * Reveals a face down card of a player. If player has no face down card does nothing.
 * @param pointer to a current player
 * @param amount of players
 * @param pointer to a field
 * @param array of players
 */
void revealfacedowncard(Player* currentplayer, int n, int* field, Player* players){
	if (currentplayer->cards[1].isFaceUp==0){
		currentplayer->cards[1].isFaceUp=1;
		printf("\nPlayer %s has revealed their face down card: %d of %s\n", currentplayer->name, currentplayer->cards[1].rank, currentplayer->cards[1].suit);
		ApplyCardEffect(currentplayer->cards[1].rank, currentplayer, field, players, n);
	}else{
		printf("\nPlayer %s has no cards to reveal\n", currentplayer->name);
	}
}
/**
 * @brief Function to check and remove if it is needed.
 * 
 * @section  DESCRIPTION
 * Functions checks all players using for all loop and if player has 0 LP it removes him and changes number of players. If the number of players is 1 function return a winner. 
 * 
 * @param array of players
 * @param pinter to number of players
 * 
 */
int checkandremove(Player* players, int* playercount, Player** currentplayer, Player** round_start_player){			
	int activeplayer=0;
	//printf("Initial playercount: %d\n", *playercount);
	for (int i = 0; i < *playercount; ++i)
	{
		if (players[i].LP<=0 && !players[i].IsEliminated)
		{
			players[i].IsEliminated=1;
			printf("\nPlayer %s is eliminated\n", players[i].name);
		}
	}
	for (int i = 0; i < *playercount; ++i)
	{
		if (!players[i].IsEliminated)
		{
			activeplayer++;
		}
	}
	for (int i = 0; i < *playercount; ++i)
	{
		if (!players[i].IsEliminated)
		{
			*round_start_player=&players[i];
			//printf("Round start player %s", (*round_start_player)->name);
			break;
		}
	}

	if (activeplayer==1)
	{
		for (int i = 0; i < *playercount; ++i)
		{
			if (!players[i].IsEliminated){
			printf("\nPlayer %s wins the game!\n", players[i].name);
			return 1;
			}
		}
	}
	return 0;
}

/**
 * @brief Function checks if users input is valid in terms of a game.
 * 
 * @section DESCRIPTION
 * Funcction using while loop checks if input is 0 or 1. If not it asks to input again 1 or 0.
 * @param string with question to user
 */
int get_valid_input(const char* prompt){
	int action=0;
	int valid_input=0;
	while(!valid_input){
		printf("%s", prompt);
		if (scanf("%d", &action)==1  && (action==0 || action==1))
		{
			valid_input=1;
		}else{
			printf("Invalid input! Please enter 1 if yes and 0 if no.\n");
			while(getchar()!='\n');
		}
	}
	return action;
}
/**
 * @brief Function shows warning message before user's action.
 * 
 * @section DESCRIPTION
 * Function shows warning message if the action of a player will cause its loss. 
 * 
 * @param rank of a face down card
 * @param pointer to a currentplayer
 * 
 */
int ShowWarningMessage(int rank, Player* currentplayer);
/**
 * @brief Function asks player on each round if he wants to see his face down card and apply its effect.
 * 
 * @section DESCRIPTION
 * Function at furst applies effect of face up card and then asks usiong printf() and scanf if player wants to reveal and apply its face down card. if not game moves to next player.
 * @param pointer to a current player
 * @param array of players
 * @param amount of players
 * @param pinter to a field
 */
void PromptAction(Player* currentplayer,Player* players, int n, int* field){
    // Always use the face-up card
    int cardtoplay = currentplayer->cards[0].rank;
    printf("Player %s plays face-up card: %d of %s\n", currentplayer->name, currentplayer->cards[0].rank, currentplayer->cards[0].suit);
    ApplyCardEffect(cardtoplay, currentplayer, field,players, n);
    if (currentplayer->cards[1].isFaceUp == 1){
            printf("All your cards are face up.\n");
            return;
        }

    // Ask if the player wants to see the face-down card
    int action=get_valid_input("Do you want to see the face-down card?\n Type 1 if yes or 0 if not\n"); // Variable to store the answer of the player

    if (action == 1){
        // If the second card is face-down
        if (currentplayer->cards[1].isFaceUp == 0){
            printf("This card is %d of %s\n", currentplayer->cards[1].rank, currentplayer->cards[1].suit);

            int action2 = get_valid_input("Do you want to reveal it to apply its effect? 1 if yes or 0 if no\n");
            
            if (action2 == 1){
                if (ShowWarningMessage(currentplayer->cards[1].rank, currentplayer)){
                    revealfacedowncard(currentplayer, n, field, players);
                    return;
                } else {
                    printf("Aborting...\n");
                    return;
                }
            } else {
                printf("Okay, nothing happens then.\n");
                return;
            }
        }
    } else {
        printf("You chose not to reveal your face-down card. Your turn is over.\n");
      	return;
    }
}

/**
 * @brief Function displays current game state(player's name, player's LP and etc.)
 * 
 * @param array of players
 * @param amount of plaayers
 */
void DisplayGameState(Player* players, int n){
	for (int i=0; i!=n;i++){
		if (players[i].IsEliminated==0)
		{
			printf("\nPLayer %s: Life =%d, Cards=[%d %s, ?]\n", players[i].name, players[i].LP, players[i].cards[0].rank, players[i].cards[0].suit);
		}
		//printf("\nPLayer %s: Life =%d, Cards=[%d %s, ?]\n", players[i].name, players[i].LP, players[i].cards[0].rank, players[i].cards[0].suit);
	}
	printf("\n");
}
int ShowWarningMessage(int rank, Player* currentplayer){
	if (rank==1 && currentplayer->LP==1)
	{
		int action=get_valid_input("The move causes you to lose all your life points. Are you sure you want to proceed?\n 1 if yes or 0 if no\n");
		if (action==1)
		{
			printf("okay let's go\n");
			return 1;
		}else if (action==0){
			printf("Okay aborting action\n");
			return 0;
		}
	}
	return 0;
}
/**
 * @brief Main fucntion that contains initalization of players, memory allocation for Deck and for array of Players and game loop. 
 * @section DESCRIPTION
 * 
 * Function stores main variables and arrays, such as number of players,pointer to a current player, LP on a field, array fo Players and Deck of Cards. It also initializes players giving them their stats and names( fore default numbers).
 * 
 * Game loop is implented as a while loop.
 * First step is checking if there are players to bve eliminited by checkandremovefunction. Second step is finction PromptAction with currentplayer. Third step is calculating next player. Fourth step is if current player ==  the first player in array loop reiniliazes the Deck, shuffles it  and redeals the cards to players.
 * Loop breaks if checkandremove function find a winner.
 * In the end main() frees arrays of Players and Cards.
 */
int main()
{
	int field=0; //LP stored on field
	Card* Deck=(Card*)malloc(DECK_SIZE*sizeof(Card));
	InitializeDeck(Deck);

	//initializing players
	printf("Write number of players: ");
	int n=0; // number of players
	scanf("%d", &n);
	if (n>20 || n<2) {printf("MAX NUMBER OF PLAYERS IS 20\n");free(Deck); return 1;} 
	
	Player* players=(Player*)malloc(n*sizeof(Player));
	
	if (!players) { // Check if memory allocation succeeded
    printf("Error: Memory allocation failed.\n");
    return 1;
	}

	for (int i=0; i!=n; i++){
		snprintf(players[i].name, sizeof(players[i].name),"%d",  i+1);
		players[i].LP=2;
		players[i].IsEliminated=0;
	}
	Player* round_start_player=NULL;
	Player* currentplayer=players;
	InitializeDeck(Deck);
	ShuffleDeck(Deck);
	dealcards(Deck, players, n);
	char winner=0;
	int gamerun=1;
	while (gamerun){
		//DisplayGameState(players, n);
		printf("\n-- Player %s's turn --\n", currentplayer->name);
		PromptAction(currentplayer, players, n, &field);
		currentplayer=NextPlayerARO(players, n, currentplayer);	


		if (checkandremove(players,&n, &currentplayer, &round_start_player))
		{
			break;
		}
		if (currentplayer==round_start_player)
		{
			DisplayGameState(players, n);
			InitializeDeck(Deck);
			ShuffleDeck(Deck);
			dealcards(Deck, players, n);
		}
	}	

	free(Deck);
	free(players);
	return 0;
}