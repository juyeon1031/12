#include <stdio.h>
#include "bingoBoard.h"

#define BINGONUM_HOLE -1 // 빵꾸 대용 숫자  

static int bingoBoard[N_SIZE][N_SIZE];
static int numberStatus [N_SIZE*N_SIZE];

int bingo_checkNum(int selNum)
{
	if(numberStatus[selNum-1] ==  BINGONUM_HOLE)
		return BINGO_NUMSTATUS_ABSENT; //이 번호가 보드에 존재하지 않는다  
	
	return BINGO_NUMSTATUS_PRESENT; //이 번호가 보드에 존재한다  
}

void bingo_init(void)
{
	int i, j, k;
	int randNum;
	int maxNum = N_SIZE*N_SIZE;
	
	for (i=0;i<N_SIZE*N_SIZE;i++)
		numberStatus[i] = BINGO_NUMSTATUS_ABSENT;
		
	for (i=0;i<N_SIZE;i++)
		for (j=0;j<N_SIZE;j++)
		{
			randNum = rand()%maxNum; //랜덤 숫자 선택  
			
			for (k=0;k<N_SIZE*N_SIZE;k++)//각 숫자에 대해 따져보기  
			{
				if (numberStatus[k] == BINGO_NUMSTATUS_ABSENT ) //숫자 k+1이 아직 할당이 안되어 있다면  
				{
					if (randNum == 0) //k+1 이 randNum번째 숫자이면  
						break;
					else
						randNum--; //그렇지 않으면 하나 줄임  
				}
			}
			//숫자 k+1을 할당 
			numberStatus[k] = i*N_SIZE + j;
			bingoBoard[i][j] = k+1;
			maxNum--;
		}
}
	
	
/*	int i, j, cnt=1;
    for(i=0;i<N_SIZE;i++){
    	for(j=0;j<N_SIZE;j++){
      		if(cnt == 15)
      		{
      			bingoBoard[i][j] = BINGONUM_HOLE;
      			numberStatus[cnt-1] = BINGONUM_HOLE;
      			cnt++;
			}
			else
			{
				numberStatus[cnt-1] = i*N_SIZE+j;
				bingoBoard[i][j] = cnt++;
        	}
        }
    }
*/


void bingo_print(void)
{
	int i, j;
   
   printf("===================================\n");
   for(i=0;i<N_SIZE;i++){
      for(j=0;j<N_SIZE;j++){
         if(bingoBoard[i][j] == BINGONUM_HOLE)
            printf("X\t");
         else
            printf("%i\t", bingoBoard[i][j]);
        }
      printf("\n");
	}
    printf("===================================\n\n");

}

void bingo_inputNum(int sel)
{
	int row, col;
	row = numberStatus[sel-1]/N_SIZE;
	col = numberStatus[sel-1]%N_SIZE;
	
	bingoBoard[row][col] = BINGONUM_HOLE;
	numberStatus[sel-1] = BINGONUM_HOLE;

}

int bingo_countCompletedLine(void)
{
	int i, j;
	int cnt=0;
	int checkBingo;
	
	//check row(행 관점에서 계산) 
	for(i=0;i<N_SIZE;i++){
		checkBingo = 1;
		for(j=0;j<N_SIZE;j++){
			if(bingoBoard[i][j] > 0){
				checkBingo = 0;
				break;
			}
		}
		if (checkBingo == 1){
			cnt++;
		}
	} 
	
	//check column
	for(j=0;j<N_SIZE;j++){
		checkBingo = 1;
		for(i=0;i<N_SIZE;i++){
			if(bingoBoard[i][j] > 0){
				checkBingo = 0;
				break;
			}
		}
		if (checkBingo == 1){
			cnt++;
		}
	} 
	
	//check diagonally 1
	checkBingo = 1;
	for(i=0;i<N_SIZE;i++){
		if(bingoBoard[i][i] > 0){
			checkBingo = 0;
			break;
		}
	}
	if (checkBingo == 1){
		cnt++;
	}
	
	checkBingo = 1;
	for(i=0;i<N_SIZE;i++){
		if(bingoBoard[i][N_SIZE-1] > 0){
			checkBingo = 0;
			break;
		}
	}
	if (checkBingo == 1){
		cnt++;
	}
	
	return cnt;
} 	
	


