// Doesn't print every word in a space-separated string

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
	char s[100], longest[46], buffer[46];
	printf("Enter a string: ");
	scanf(" %[^\n]", s);
	int i = 0, count = 0;
	while (i < strlen(s) + 1) {
		if (isspace(s[i]) || iscntrl(s[i])) {
			buffer[count] = '\0';
			if (strlen(buffer) > strlen(longest)) {
				strcpy(longest, buffer);
			}
			count = 0;
		}
		buffer[count++] = s[i++];
	}
	
	if (!strlen(longest)) {
		printf("%s\n", buffer);
	} else {
		printf("%s\n", longest);
	}
	
	return 0;
}
