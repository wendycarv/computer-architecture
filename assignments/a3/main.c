#include <stdlib.h>
#include <stdio.h>

int rfib (int arg);
int ifib (int arg);

int main(void) {
    int results[5], i;
    int data[] = {3, 9, 18, 23, 25};
    int ndata = 5;

    for (i=0; i<ndata; ++i) {
        printf("\ncalling fib with %d\n", data[i]);
        results[i] = rfib(data[i]);
        printf(" called fib with %d, result is %d\n", data [i], results[i]);
    }
    for (i=0; i<ndata; ++i) {
        printf("     FIB of %d\t is %d\n", data[i], results[i]);
    }
    
    return 0;
}

int rfib(int arg) {
    int fn1, fn2;

    if (arg == 0) return 0;
    if (arg == 1) return 1;

    fn1 = rfib(arg - 1);
    fn2 = rfib(arg - 2);

    return (fn1 + fn2);
}

int ifib(int arg) {
    int fm1, fm2, tmp, lpcnt;

    if (arg == 0) return 0;
    if (arg == 1) return 1;

    fm1 = 1;
    fm2 = 0;
    tmp = 0;

    for(lpcnt = (arg - 1); lpcnt > 0; --lpcnt) {
        tmp = fm1 + fm2;
        fm2 = fm1;
        fm1 = tmp;
    }
    return (tmp);
}