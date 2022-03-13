#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

/*
Your job is to implement the player() function, so that everytime it returns a column number to play.
In every turn it takes the entire board struct pointer:

typedef struct {
    int rows;
    int columns;
    int** board;
} Board

Board.board is a two dimensional array declared somewhat like this: Board.board[rows][columns]
*/

extern int player_9976_10130(const Board* b){
    //Happy hacking :)
	int rows=b->rows;										//just shorter name
	int columns=b->columns;							//just shorter name
	int **board=b->board;								//just shorter name
	int r, c, turn=0, player=0;					//counter for rows, columns, turn and which player i am
	int move, wrong=1;									//move i am returning and check for validness
	int i, j, max=0;										//just some counters
	int *tempscore;											//		-//-
	srand(time(0));

	for(r=0; r<rows; r++){
		for(c=0; c<columns; c++){
			if(board[r][c]!=0) player++;			//different player different strategies
		}
	}

	if(!(player%2)){ 									//you are player 1
							
		for(r=0; r<rows; r++){
			for(c=0; c<columns; c++){
				if(board[r][c]==1) turn++;								//counts turns
			}
		}								
			
		if(rows!=columns){														//we are playing on an enlogated board

			if(!turn) return move=columns/2;										//just for 1st turn, no strategy behind that

			tempscore=(int *)calloc(columns, sizeof(int));
			for(c=0; c<columns; c++){												//checking diagonally if we have "enough"
				for(r=0; r<rows-1; r++){											//consecutive chips to play there
					if(!board[r][c] && board[r+1][c]!=0){				//first up-right and down-left
						i=r-1;
						j=c+1;
						while(j>-1 && i>-1){
							if(board[i][j]==1) tempscore[c]++;
							else if(board[i][j]==2 || (!board[i][j] && board[i+1][j]!=0)) break;
							i--;
							j++;
						}
						i=r+1;
						j=c-1;
						while(j<columns && i<rows-1){
							if(board[i][j]==1) tempscore[c]++;
							else if(board[i][j]==2 || (!board[i][j] && board[i+1][j]!=0)) break;
							i++;
							j--;
						}
					}					
				}
			}
			for(c=0; c<columns-1; c++){					//plus one would cause segmentation fault in the previous for
				if(!board[rows-1][c]){						//so we are checking the last row separately
					i=rows-2;
					j=c+1;
					while(j>-1 && i>-1){
						if(board[i][j]==1) tempscore[c]++;
						else if(board[i][j]==2 || !board[i][j]) break;
						i--;
						j++;
					}
				}
			}
			for(c=0; c<columns; c++){					//choosing the best tempscore
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			tempscore=(int *)calloc(columns, sizeof(int));
			for(c=0; c<columns; c++){											//checking up-left and down-right
				for(r=0; r<rows-1; r++){
					if(!board[r][c] && board[r+1][c]!=0){
						i=r-1;
						j=c-1;
						while(j>-1 && i>-1){
							if(board[i][j]==1) tempscore[c]++;
							else if(board[i][j]==2 || (!board[i][j] && board[i+1][j]!=0)) break;
							i--;
							j--;
						}
						i=r+1;
						j=c+1;
						while(j<columns && i<rows-1){
							if(board[i][j]==1) tempscore[c]++;
							else if(board[i][j]==2 || (!board[i][j] && board[i+1][j]!=0)) break;
							i++;
							j++;
						}
					}
				}
			}
			for(c=1; c<columns; c++){					//checking last row
				if(!board[rows-1][c]){
					i=rows-2;
					j=c-1;
					while(j>-1 && i>-1){
						if(board[i][j]==1) tempscore[c]++;
						else if(board[i][j]==2 || !board[i][j]) break;
						i--;
						j--;
					}
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			tempscore=(int *)calloc(columns, sizeof(int));
			for(c=0; c<columns; c++){											//checking columns for the same
				if(board[0][c]!=0) continue;								//if it's full, go to the next column
				for(r=1; r<rows; r++){
					if(board[r][c]==1) tempscore[c]++;
					else if(board[r][c]==2) break;						//if opponent has a chip, go to the next column
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			tempscore=(int *)calloc(columns, sizeof(int));
			for(r=0; r<rows-1; r++){																		//checking rows for the same
				for(c=0; c<columns; c++){
					if(!board[r][c] && board[r+1][c]!=0){										//if we find an empty space we check left and right
						j=c+1;
						while(j<columns){
							if(board[r][j]==1)	tempscore[c]++;
							else if(board[r][j]==2 || (!board[r][j] && board[r+1][j]!=0)) break;
							j++;
						}
						j=c-1;
						while(j>-1){
							if(board[r][j]==1)	tempscore[c]++;
							else if(board[r][j]==2 || (!board[r][j] && board[r+1][j]!=0)) break;
							j--;
						}
					}
				}
			}
			for(c=0; c<columns; c++){												//same thing for lowest row
				if(!board[rows-1][c]){
					j=c+1;
					while(j<columns){
						if(board[rows-1][j]==1)	tempscore[c]++;
						else if(board[rows-1][j]==2 || !board[rows-1][j]) break;
						j++;
					}
					j=c-1;
					while(j>-1){
						if(board[rows-1][j]==1)	tempscore[c]++;
						else if(board[rows-1][j]==2 || !board[rows-1][j]) break;
						j--;
					}
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			tempscore=(int *)calloc(columns, sizeof(int));
			for(c=0; c<columns; c++){												//we are checking columns for opponent chips
					if(board[0][c]!=0) continue;								//so that we block him
					for(r=1; r<rows; r++){
					if(board[r][c]==2) tempscore[c]++;
					else if(board[r][c]==1) break;
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			if(move<0 || move>columns-1) wrong=0;
			else if(board[0][move]!=0) wrong=0;

			if(!wrong){																							//if something wrong happened with the code play randomly
				int* moves = (int*)calloc(b->columns, sizeof(int));
    		int counter = 0;
    		for(i = 0; i < b->columns; i++){
        		if(b->board[0][i] == 0){
        	    moves[counter++] = i;
     			 	}
    		}
    		move = rand() % counter;
    		int ret_move =  moves[move];
    		free(moves);
    		return ret_move;
			}

			return move;
		}

		if(rows==columns){														//square board

			if(!turn) return move=0;										//starts with bottom left to top right diagonal

			else{
				r=0;
				c=columns-1;
				while(r<rows-1 && c>0){										//checks for diagonal space
					if(!board[r][c] && board[r+1][c]!=0){
						move=c;
						return move;
					}
					r++;
					c--;
				}

				int* moves = (int*)calloc(b->columns, sizeof(int));						//last resort = random
 				int counter = 0;
				int ret_move;
 				for(i = 0; i < columns; i++){
					r=rows-1-i;
					c=i;
					if(c==1 && !board[rows-1][1])	continue;
					else if(!board[r][c] && board[r+2][c]!=0) continue;					//random moves should not mess diagonal set up
     			else if(board[0][i] == 0){
   		  			moves[counter++] = i;
     			}
   			}
				if(!counter){																//sometimes you HAVE TO mess it up
					for(c = columns-1; c > -1; c--){					//so just mess it up the least possible
						if(!board[0][c]) return move=c;
					}
				}
			    int move = rand() % counter;
    			ret_move =  moves[move];
    			free(moves);	
    			return ret_move;
			}
		}
	}

	if(player%2==1){										//pretty much same for player 2

		for(r=0; r<rows; r++){
			for(c=0; c<columns; c++){
				if(board[r][c]==2) turn++; 				//turns
			}
		}

		if(rows!=columns){														//we are playing on an enlogated board

			if(!turn) return move=columns/2;										//1st turn

			tempscore=(int *)calloc(columns, sizeof(int));
			for(c=0; c<columns; c++){														//checking up-right and down-left
				for(r=0; r<rows-1; r++){
					if(!board[r][c] && board[r+1][c]!=0){
						i=r-1;
						j=c+1;
						while(j>-1 && i>-1){
							if(board[i][j]==2) tempscore[c]++;
							else if(board[i][j]==1 || (!board[i][j] && board[i+1][j]!=0)) break;
							i--;
							j++;
						}
						i=r+1;
						j=c-1;
						while(j<columns && i<rows-1){
							if(board[i][j]==2) tempscore[c]++;
							else if(board[i][j]==1 || (!board[i][j] && board[i+1][j]!=0)) break;
							i++;
							j--;
						}
					}					
				}
			}
			for(c=0; c<columns-1; c++){					//checking last row
				if(!board[rows-1][c]){
					i=rows-2;
					j=c+1;
					while(j>-1 && i>-1){
						if(board[i][j]==2) tempscore[c]++;
						else if(board[i][j]==1 || !board[i][j]) break;
						i--;
						j++;
					}
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			tempscore=(int *)calloc(columns, sizeof(int));
			for(c=0; c<columns; c++){											//checking up-left and down-right
				for(r=0; r<rows-1; r++){
					if(!board[r][c] && board[r+1][c]!=0){
						i=r-1;
						j=c-1;
						while(j>-1 && i>-1){
							if(board[i][j]==2) tempscore[c]++;
							else if(board[i][j]==1 || (!board[i][j] && board[i+1][j]!=0)) break;
							i--;
							j--;
						}
						i=r+1;
						j=c+1;
						while(j<columns && i<rows-1){
							if(board[i][j]==2) tempscore[c]++;
							else if(board[i][j]==1 || (!board[i][j] && board[i+1][j]!=0)) break;
							i++;
							j++;
						}
					}
				}
			}
			for(c=1; c<columns; c++){					//checking last row
				if(!board[rows-1][c]){
					i=rows-2;
					j=c-1;
					while(j>-1 && i>-1){
						if(board[i][j]==2) tempscore[c]++;
						else if(board[i][j]==1 || !board[i][j]) break;
						i--;
						j--;
					}
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			tempscore=(int *)calloc(columns, sizeof(int));
			for(c=0; c<columns; c++){												//checking columns
				if(board[0][c]!=0) continue;
				for(r=1; r<rows; r++){
					if(board[r][c]==2) tempscore[c]++;
					else if(board[r][c]==1) break;
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			tempscore=(int *)calloc(columns, sizeof(int));
			for(r=0; r<rows-1; r++){																		//checking rows
				for(c=0; c<columns; c++){
					if(!board[r][c] && board[r+1][c]!=0){
						j=c+1;
						while(j<columns){
							if(board[r][j]==2)	tempscore[c]++;
							else if(board[r][j]==1 || (!board[r][j] && board[r+1][j]!=0)) break;
							j++;
						}
						j=c-1;
						while(j>-1){
							if(board[r][j]==2)	tempscore[c]++;
							else if(board[r][j]==1 || (!board[r][j] && board[r+1][j]!=0)) break;
							j--;
						}
					}
				}
			}
			for(c=0; c<columns; c++){												//same thing for lowest row
				if(!board[rows-1][c]){
					j=c+1;
					while(j<columns){
						if(board[rows-1][j]==2)	tempscore[c]++;
						else if(board[rows-1][j]==1 || !board[rows-1][j]) break;
						j++;
					}
					j=c-1;
					while(j>-1){
						if(board[rows-1][j]==2)	tempscore[c]++;
						else if(board[rows-1][j]==1 || !board[rows-1][j]) break;
						j--;
					}
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			tempscore=(int *)calloc(columns, sizeof(int));
			for(c=0; c<columns; c++){												//blocking enemy
				if(board[0][c]!=0) continue;
				for(r=1; r<rows; r++){
					if(board[r][c]==1) tempscore[c]++;
					else if(board[r][c]==2) break;
				}
			}
			for(c=0; c<columns; c++){
				if(tempscore[c]>max){
					move=c;
					max=tempscore[c];
				}
			}
			free(tempscore);

			if(move<0 || move>columns-1) wrong=0;
			else if(board[0][move]!=0) wrong=0;

			if(!wrong){																						//wrong, play randomly
				int* moves = (int*)calloc(b->columns, sizeof(int));
    		int counter = 0;
    		for(i = 0; i < b->columns; i++){
        		if(b->board[0][i] == 0){
        	    moves[counter++] = i;
     			 	}
    		}
    		move = rand() % counter;
    		int ret_move =  moves[move];
    		free(moves);
    		return ret_move;
			}

			return move;
		}

		if(rows==columns){									//square board

			if(!turn){																				//player 2 starts with the available diagonal
				if(!board[rows-1][0]  && !board[rows-1][1]){
					move=0;
					return move;
				}
				else{
					move=columns-1;
					return move;
				}
			}

			else if(board[rows-1][0]==2){				//bottom left to top right
				r=0;
				c=columns-1;
				while(r<rows-1 && c>0){										//diagonal space
					if(!board[r][c] && board[r+1][c]!=0){
						move=c;
						return move;
					}
					r++;
					c--;
				}

				int* moves = (int*)calloc(b->columns, sizeof(int));
 				int counter = 0;
				int ret_move;
 				for(i = 0; i < columns; i++){
					r=rows-1-i;
					c=i;
					if(c==1 && !board[rows-1][1])	continue;
					else if(!board[r][c] && board[r+2][c]!=0) continue;		//random but checked moves
     			else if(board[0][i] == 0){
   		  		moves[counter++] = i;
     			}
   			}
				if(!counter){														//(getting away with it) all messed up
					for(c = columns-1; c > -1; c--){
						if(!board[0][c]) return move=c;
					}
				}
			  move = rand() % counter;
    		ret_move =  moves[move];
    		free(moves);
    		return ret_move;
			}

			else if(board[rows-1][columns-1]==2){    	//same thing bottom right to top left (no need for player 1)
				r=0;
				c=0;
				while(r<rows-1 && c<columns-1){
					if(!board[r][c] && board[r+1][c]!=0){
						move=c;
						return move;
					}
					r++;
					c++;
				}

				int* moves = (int*)calloc(b->columns, sizeof(int));
   			int counter = 0;
				int ret_move;
    		for(i = 0; i < columns; i++){
					r=i;
					c=i;
					if(c==columns-2 && !board[rows-1][c]) continue;  
					if(!board[r][c] && board[r+2][c]!=0) continue;
   				else if(board[0][c] == 0){
  	  			moves[counter++] = i;
 					}
    		}
				if(!counter){
					for(c = 0; c < columns; c++){
						if(!board[0][c]) return move=c;
					}
				}
			  move = rand() % counter;
    		ret_move =  moves[move];
    		free(moves);
    		return ret_move;
			}
		}
	}	
}
