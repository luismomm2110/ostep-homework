#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *data = (int *) malloc(100);
    data[12] = 1;
    free(&data[12]);
    printf("%d\n", data[12]);
    return 0;
}

