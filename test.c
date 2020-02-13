#include <stdio.h>
#include <stdlib.h>

void ggg(int *_x) {
    *_x = 20;
}
void f(int *a) {
    int b = 10;
    *a = b;
    ggg(a);
}


int main() {
    int a;
    f(&a);
    printf("%d",a);

    return 0;
}