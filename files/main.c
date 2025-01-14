#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char s[] = "#include <stdio.h>\n\nint main(int argc, char **argv) {\n\tint x;\n\tprintf(\"Enter a number: \");\n\tscanf(\"\%d\", &x);\n\tprintf(\"The number is: \%d\\n\", x);\n\treturn 0;\n}";
    FILE *fp;
    fp = fopen("C:\\Users\\User\\Downloads\\C-Explorations\\files\\file_test.c", "w");

    if (fp) {
        fwrite(s, 1, strlen(s), fp);
    }

    fclose(fp);
    return 0;
}