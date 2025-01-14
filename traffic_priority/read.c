#include <stdio.h>
#include "tp.h"

int main(int argc, char **argv) {
    FILE *fp = fopen("traffic.dat", "rb");
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    int numRecords = fileSize / sizeof(Traffic);
    Traffic t[numRecords];
    fread(t, sizeof(Traffic), numRecords, fp);
    for (int i = 0; i < numRecords; i++) {
        printf("%s %d\n", t[i].lane, t[i].duration);
    }
    return 0;
}