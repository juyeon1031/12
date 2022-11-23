#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bingoBoard.h"
#define BINGO_RES_FINISHED 0
#define BINGO_RES_UNFINISHED -1

//int selNum;
int check_gameEnd(void)
{
	int res = BINGO_RES_UNFINISHED;
	if(bingo_countCompletedLine() >= N_LINE)
		res = BINGO_RES_FINISHED;
	
	return res;
}

int get_number(void)
{
	int selNum=0;
	
	do{
		printf("select a number: ");
		scanf("%d", &selNum);
		fflush(stdin);
		
		if (selNum < 1 || selNum > N_SIZE*N_SIZE || bingo_checkNum(selNum) == BINGO_NUMSTATUS_ABSENT);
		{
			printf("%i is not on the board! select other one.\n", selNum);
		}
	} while (selNum < 1 || selNum > N_SIZE*N_SIZE || bingo_checkNum(selNum) == BINGO_NUMSTATUS_ABSENT);
	
	return selNum;
}

int main(int argc, char *argv[]) {
	int selNum;	

   srand((unsigned)time(NULL));
   
   printf("=====================================\n");
   printf("*************************************\n");
   printf("              BINGO GAME             \n");
   printf("*************************************\n");
   printf("=====================================\n\n\n");
  
   //game
   bingo_init();   
   //initialize bingo board
   
   while (check_gameEnd() == BINGO_RES_UNFINISHED) //줄수가 N_BINGO 보다 작음 
   {
		//bingo board print
		bingo_print();
   		//print no.of completed line
   		printf("Number of completed line : %i\n", bingo_countCompletedLine());
   		//select a number
   		selNum = get_number();
   		//update the board status
		bingo_inputNum(selNum);
   }
   
   
   //ending
   printf("\n\n\n\n\n\n\n");
   printf("=====================================\n");
   printf("*************************************\n");
   printf("         CONGRATULATIONS             \n");
   printf("             BINGO!!!!!              \n");
   printf("             YOU WIN!!!!             \n");
   printf("*************************************\n");
   printf("=====================================\n\n");   

	return 0;
	
}
