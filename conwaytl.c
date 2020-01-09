#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

/*

 Goals:
    Conway simulation.

 Usage example:
	only tested under linux environment.
	compile:
	 		gcc -o conwaytl  -std=c99 -Wall conwaytl.c
	run:
			./conwaytl toad
			./conwaytl glidER
			./conwaytl
	stop:
			press Ctrl-C to exit.
	
 Reference:
	https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
*/


int WD = 1; //neighbor window size
int N = 8; //grid size
enum PATTERN_TYPE { RANDOMT=0, BLINKER =1, TOAD =2, BEACON =4, GLIDER = 5}; // type of pattern
enum PATTERN_TYPE PTYPE = RANDOMT ;
char * whichpattern = 0;
//typedef 	int board_t; // square board 8X8 with toroidal topology.

void generation(int * grids);

void show(int * grids){
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            if (*(grids+(i*N+j)) == 1){
		printf(" X ");
            else
                printf(" . ");
        }
    	printf("\033[0E");  // to new line and print next row        
    }
	
	
}
void display(int * grids){

	printf("\033[2J"); // clear window
	int acc = 0;
	while(acc>=0){
		acc++ ;
		printf("\033[0;0H");  //cursor to top left
		printf(" %s \r", whichpattern);
		printf("\033[5;0H"); // cursor to 5 rows below for pattern display 
		
		show(grids);
	        fflush(stdout);   // roll back to print next generation results at the same lines 
		generation(grids);
		usleep(500000);
	}

}

int circlepos(int abspos, int relpos){
    // for(int i=-WD;i<WD+2;i++){
    //     //printf(" %d ",(pos+i+N)%N);
        
    // }
    return ((abspos+ relpos +N)%N);
}

int dice(int num){
    //srand(time(NULL)); // use current time as seed for random generator
    //int random_variable = rand();
     
    // roll a 6-sided die 20 or 1 times, num==6;
    int x;
    for (int n=0; n != 1; ++n) {
        x = num+1;
        while(x > num) {
            // printf("%d %d \n", 1u, ((RAND_MAX + 1u)/6));
            x = 1 + rand()/((RAND_MAX + 1u)/num); // Note: 1+rand()%6 is biased
        }
    //printf(" what is x: %d ",  x); 
    }
    return x;
}



static void init(int PTYPE, int *grids){

	switch (PTYPE)
	{
		int whatoni, whatonj, whaton, whatond;
		
		case 0: 
		whaton = 0;
	        for(int i=0; i<N; i++)
			for(int i=0; i<N; i++)
	                {
	                    whaton = rand()< (RAND_MAX/10) ? 1: 0;
	                    *(grids++) = whaton;
	                }	
		break;
		
		case 1: 
	        whatoni = dice(N)-1;
	        whatonj = dice(N)-1;
	        whatond = rand()< (RAND_MAX/10) ? 1: 0;
	        if (whatond==1){
	            for(int i=-WD;i<WD+1;i++){
	                int gdpos = circlepos(whatoni, i)*N + circlepos(whatonj,0);
	                *(grids+gdpos) = 1;
	            }
	        }else{
	            for(int j=-WD;j<WD+1;j++){
	                int gdpos = circlepos(whatoni, 0)*N + circlepos(whatonj,j);
	                *(grids+gdpos) = 1;
	            }
	        }
                break;
			
		case 2:
	        whatoni = dice(N)-1;
	        whatonj = dice(N)-1;
	        whatond = rand()< (RAND_MAX/10) ? 1: 0;
	        if (whatond==1){
	            for(int ii=0;ii<2;ii++){
	                for(int i=-WD;i<WD+1;i++){
	                    int gdpos = circlepos(whatoni+ii, i)*N + circlepos(whatonj+ii,0);
	                    *(grids+gdpos) = 1;
	                }
	            }
	        }else{
	            for(int jj=0;jj<2;jj++){
	                for(int j=-WD;j<WD+1;j++){
	                    int gdpos = circlepos(whatoni+jj, 0)*N + circlepos(whatonj+jj,j);
	                    *(grids+gdpos) = 1;
	                }
	            }
	        }
		break;
		
		case 4:
		whatoni = 3;
		whatonj = 3;
	        whatond = 1;
	        if (whatond==1){
	            for(int ii=0;ii<=1;ii++){
	                for(int j=0;j<=1;j++){
	                    int gdpos = circlepos(whatoni+ii , 0)*N + circlepos(whatonj+j,0);
	                    *(grids+gdpos) = 1;
	                }
	            }

	            for(int ii=2;ii<=3;ii++){
	                for(int j=2;j<=3;j++){
	                    int gdpos = circlepos(whatoni+ii , 0)*N + circlepos(whatonj+j,0);
	                    *(grids+gdpos) = 1;
	                }
	            }
	        }
		break;
		
		case 5:
	        whatoni = 3;
	        whatonj = 3;
	        whatond = 1;
	        if (whatond==1){
        	    for(int j=-WD;j<WD+1;j++){
	                    int gdpos = circlepos(whatoni, 0)*N + circlepos(whatonj+j,0);
	                    *(grids+gdpos) = 1;
	                }
	                int gdpos = circlepos(whatoni-1, 0)*N + circlepos(whatonj+1,0);
	                *(grids+gdpos) = 1;
	                gdpos = circlepos(whatoni-2, 0)*N + circlepos(whatonj,0);
	                *(grids+gdpos) = 1;
	            }else{
	                for(int i=-WD;i<WD+1;i++){
	                    int gdpos = circlepos(whatoni+i, 0)*N + circlepos(whatonj,0);
	                    *(grids+gdpos) = 1;
	                }
            
	        }
		break;
		default:
	        whaton = 0;
	        for(int i=0; i<N; i++)
	        {
	            for(int i=0; i<N; i++)
	                {
	                    whaton = rand()< (RAND_MAX/10) ? 1: 0;
	                    *(grids++) = whaton;
	                }
	        }
		break;
		
	} // finish the switch here
	
}

void generation(int * grids){
    int * newgrid;
    newgrid = (int*) calloc((N*N) , sizeof(int));

    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            int lifeval = 0;
            int selfpos = circlepos(i,0)*N + circlepos(j,0);;
            
            int gdpos;
            for(int ii=-WD;ii<WD+1;ii++){
                for(int jj=-WD;jj<WD+1;jj++){
                    gdpos = circlepos(i,ii)*N + circlepos(j,jj);
                    if ( *(grids+gdpos) ==1) lifeval++;                    
                }
            }
            if (*(grids+selfpos)==1) lifeval--;
            if (lifeval==3 || (lifeval==2 && *(grids +selfpos)==1 )) *(newgrid +selfpos) = 1;
    
        }
    }

    // now update the grids from temp memory
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            *(grids+(i*N+j)) = *(newgrid+(i*N+j));
        }
    }
    free(newgrid);
}



char * lowercase2(const char * commd){
    // printf("will check : %s %d\n", commd, strlen(commd));
    char * cmm  = NULL; //[strlen(commd)];
    cmm = (char*) malloc((strlen(commd)+1) * sizeof(char));
    for(int i=0; commd[i]; i++) {
        cmm[i] = tolower(commd[i])  ;
    //printf("%c\n", cmm[i]);
       
    }
    //printf("over\n");
    cmm[strlen(commd)] = '\0';
    //printf("\n new: %d\t%s\n", strlen(cmm), cmm);
    return cmm;
}




int main(int argc, const char* argv[]){

    srand(100000);
    char * command_title ;
    if (argc>2 || argc==1){
        command_title = "Randomt";
	whichpattern = "Random";
    }else{
	command_title = lowercase2(argv[1]);
	whichpattern = (char *) argv[1];
    }

    // set the pattern type:
    if (strcmp(command_title, "blinker") == 0) {
        PTYPE = BLINKER;
    }else if (strcmp(command_title, "toad")==0){
        PTYPE = TOAD;
    }else if (strcmp(command_title, "beacon")==0){
        PTYPE = BEACON;
    }else if (strcmp(command_title, "glider")==0){
        PTYPE = GLIDER;
    }


    int * grids = NULL;
    grids = (int*) malloc((N*N) * sizeof(int));
    init(PTYPE, grids);
	
    // here is main running of code, display all results:
    display(grids);
    free(grids);
    printf("\n end of game\n\n");


    
}






