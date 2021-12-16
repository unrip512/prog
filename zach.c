#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);


    float * p = (float *)malloc((n + 1) * sizeof(float));
    p[0] = 1;
    p[1] = 0;
    p[2] = 0.5;

    for (int i = 3; i <= n; i++) {
        p[i] = p[i-1] - p[i-2] + p[i-3]; 
    }

    printf("%f", p[n]);

    free(p);
}