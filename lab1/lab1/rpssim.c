#include <stdio.h>
#include <stdlib.h>

#define RNUM 7

typedef enum choice{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

int randchoice(int* cdata){
    int c = rand() % 4;
    cdata[c]++;
    return c;
}

int adaptchoice(int* pdata, int* odata){
if(odata[0] > odata[1] && odata[0] > odata[2]){
    //if favors rock
    pdata[PAPER-1]++;
    return PAPER;
}else if(odata[1]>odata[0] && odata[1]>odata[2]){
    //if favors paper
    pdata[SCISSORS-1]++;
    return SCISSORS;
}else if(odata[2]>odata[0] && odata[2]>odata[1]){
    //if favors scissors
    pdata[ROCK-1]++;
    return ROCK;
}
}

//win mirror, lose stay, tie random
int wmlstr(int* p1data, int* prev, int* ls){
    //won previously
    if(rpswin(prev[0],prev[1],prev,ls,1)==0){
        p1data[prev[1]]++;
        return prev[1];
    //lost previously
    }else if(rpswin(prev[0],prev[1],prev,ls,1)==1){
       /* if(ls[0] > 1){
           return randchoice(p1data);
        }else{} */
        p1data[prev[0]]++;
        return prev[0];
    }else if(rpswin(prev[0],prev[1],prev,ls,1)==2){
        return randchoice(p1data);
    }
}

int rpswin(int p1, int p2, int* prev, int* ls,int cond){
    prev[0]=p1;
    prev[1]=p2;
    if(p1 == ROCK && p2 == SCISSORS){
        if(cond==0){ls[1]++;ls[0]=0;};
        return 0;
    }else if(p1 == PAPER && p2 == ROCK){
        if(cond==0){ls[1]++;ls[0]=0;};
        return 0;
    }else if(p1 == SCISSORS && p2 == PAPER){
        if(cond==0){ls[1]++;ls[0]=0;};
        return 0;
    }else if(p1==p2){
        return 2;
    }else{
        if(cond==0){ls[0]++;ls[1]=0;};
        return 1;
    }
}

int main(){
    //rps data 
    int p1data[3] = {0,0,0};
    int p2data[3] = {0,0,0};
    int wins[3] = {0,0,0};

    //0 index = p1
    //1 index = p2
    //2 index = tie

    //rps strat

    time_t t;

    srand((unsigned) time(&t));
    FILE *fp;
    fp = fopen("C:\\Users\\Owner\\Downloads\\lab1\\lab1\\results.txt","w");

    int p1starting = randchoice(p1data);
    int p2starting = randchoice(p2data);

    int prevm[2] = {0,0};
     int ls[2] = {0,0};

     fprintf(fp, "ROUNDS PLAYED: %d\n", RNUM);

    for(int i=0; i<RNUM;i++){
        if(i<1){
            wins[rpswin(p1starting,p2starting,prevm,ls,0)]++;
        }else{
            wins[rpswin(randchoice(p1data),randchoice(p2data),prevm,ls,0)]++;
        }
        fprintf(fp, "\nP1: %d P2: %d", prevm[0],prevm[1]);
        
    }
    fprintf(fp, "\nP1 wins: %d",wins[0]);
    fprintf(fp, "\nP2 wins: %d",wins[1]);
    fprintf(fp, "\nTies: %d",wins[2]);
    fclose(fp);
    return 0;
    
}