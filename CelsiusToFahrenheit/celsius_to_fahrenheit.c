/*
Something is still weird with the code.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
	short int a;
	do {
	    system("cls");
	    printf("Input 1 for Celsius to Fahrenheit; enter 2 for Fahrenheit to Celsius.\n");
	    short int i;
	    scanf("%hd",&i);
	    if (i==1){
		    printf("Input value of Celsius.\n");
	    	float C;
	    	scanf("%f", &C);
	    	printf("%.2f degrees Celsius is %.2f degrees Fahrenheit.\n",C,(C*1.8)+32);
	    }
	    else if (i==2) {
    		printf("Input value of Fahrenheit.\n");
		    float F;
		    scanf("%f", &F);
		    printf("%.2f degrees Fahrenheit is %.2f degrees Celsius.\n",F,(F-32)*(5.0/9.0));
	    }
	    printf("Would you like to calculate again?\n");
	    printf("1 Yes\t2 No\n");
	    scanf ("%hd", &a);
	} while(a == 1);
    return 0;

}