#include <stdio.h>
#include <stdlib.h>


void f() {
    int *x = malloc(sizeof(int));
}


int main() {
    f();
    printf("%d", *x);
    return 0;
}