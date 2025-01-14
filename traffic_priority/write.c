#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp.h"

// Copy the contents of input.txt and paste after the command to run the executable
int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Enter a number as a command line argument.");
        return 1;
    }
    int i;
    for (i = 0; i < strlen(argv[1]) && isdigit(argv[1][i]); i++) {}
    if (i == strlen(argv[1]) && i > 0) {
        int size = atoi(argv[1]);
        printf("%d\n", size);
        Traffic t[size];
        for (i = 0; i < size; i++) {
            printf("Enter lane %d (main/alt): ", i + 1);
            scanf(" %s", t[i].lane);
            printf("Enter duration of the lane %d in seconds: ", i + 1);
            scanf("%d", &t[i].duration);
        }
        FILE *fp = fopen("traffic.dat", "wb");
        fwrite(t, sizeof(Traffic), size, fp);
        fclose(fp);
    } else {
        printf("Please enter a number as a command line argument.\n");
    }
    return 0;
}