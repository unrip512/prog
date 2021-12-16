#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {

    int N, M;

    FILE * in = fopen(argv[1], "r");
    fscanf(in, "%d%d", &M, &N);
    FILE * out = fopen("exp1.txt", "w");

    char c;

    char * p = (char *)malloc((M * N) * sizeof(char));

    for(int i = 0; i < (M*N); i++) {
        c = fgetc(in);
        p[i] = fgetc(in);

    }

    int * p2 = (int *)malloc((M * N) * sizeof(int));

    for (int i = 0; i < (M * N); i++) {
        p2[i] = 0;
    }


    for(int j = 0; j < N; j++) {
       if (p[j] == '#') {
           break;
       }
       else {
           p2[j] = 1;
       }
    }

    for(int j = 0; j < M; j++) {
       if (p[N*j] == '#') {
           break;
       }
       else {
           p2[N*j] = 1;
       }
    }

    for(int k = 1; k < M; k++) {
        for (int l = 1; l < N; l++) {
            if(p[N * k + l] != '#') {
                p2[N * k + l] = p2[(k-1) * N + l] + p2[k * N + (l - 1)];
            }
        }
    }


    fprintf(out, "Number of ways : %d\n", p2[N*M -1]);


    free(p);
    free(p2);

    fclose(in);
    fclose(out);
}