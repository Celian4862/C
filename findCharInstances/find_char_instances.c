// The algorithm is actually still flawed. Will require some tweaking.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

int main()
{
    char c[MAX], instances[MAX];
    int i, j, *count = (int*) calloc (MAX, 4), x = 0;
    printf("Enter a string: ");
    scanf(" %[^\n]", c);
    for (i = 0; i < strlen(c); i++) {
        for (j = 0; j < strlen(instances) && c[i] != instances[j]; j++);
        if (j == strlen(instances)) {
            instances[x] = c[i];
            count[x++]++;
        }
        else {
            count[j]++;
        }
    }
    
    for (i = 0; i < strlen(instances); i++) {
        int index = i;
        for (j = i + 1; j < strlen(instances); j++) {
            if (instances[index] > instances[j]) {
                index = j;
            }
        }
        char temp = instances[i];
        instances[i] = instances[index];
        instances[index] = temp;
    }
    
    for (i = 0; i < strlen(instances); i++) {
        printf("%c %d\n", instances[i], count[i]);
    }
    
    free(count);

    return 0;
}