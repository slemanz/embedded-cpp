#include "mcal_reg.h"
#include "uart.h"

int main(void)
{
    uart_init();
    printf("Init the board!\n");

    int _size, itr;
	int *all_scores;
	
	printf("How many scores would you like to enter? ");
	scanf("%d" ,&_size);
	
	all_scores =  new int[_size];
	
	if(all_scores == NULL)
    {
		printf("Error:  no memory available.");
	}else{
	    for(itr=0; itr < _size; itr++)
        {
            printf("Enter a score: ");
            scanf("%d", &all_scores[itr]);
		}
		 
        printf("You entered theses sores: ");
        for(itr = 0; itr < _size; itr++)
        {
            printf("%d ,",all_scores[itr]);
        }
		 
		 delete[] all_scores;
		 
	}

    while(1)
    {
        
    }
}

