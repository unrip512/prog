#include <stdio.h>
#include <stdlib.h>


void add(int n, int k) {

    printf("= %d\n", (n + k));
}

void sub(int n, int m) {

    printf("= %d\n", (n - m));
}

void mult(int n, int k) {

    printf("= %d\n", (n * k));
}

void div_(int n, int k) {

    printf("= %d\n", (n/k));
}

void rem(int n, int k) {

    printf("= %d\n", (n % k));
}

void deg(int n, int k) {

    int dg = 1;

    for(int i = 0; i < k; i++) {

        dg = dg * n;
    }

    printf("= %d\n", dg);
}

void or_(int n, int k) {
    printf("= %d\n", (n | k));
}

void and_(int n, int k) {
    printf("= %d\n", (n & k));
}



int calc(char c, int n, int k ) {

    int ind = 0;

    if(c == '+') {
        add(n, k);
    }
    if(c == '-') {
        sub(n, k);
    }
    if(c == '*') {
        mult(n, k);
    }
    if(c == '/') {
        div_(n, k);
    }
    if(c == '%') {
        rem(n, k);
    }
    if(c == '|') {
        or_(n, k);
    }
    if(c == '&') {
        and_(n,k);
    }
    if(c == '^') {
        deg(n, k);
    }
    if((c == 'e')&(n == 0) & (k == 0)) {
        ind = 1;
    }

    return ind;

}

int main()  {

    int n, k, ind = 0;
    char c;

    while (ind == 0) {

        scanf("%d%c%d", &n, &c, &k);

        ind = calc(c, n, k);

    }    
}