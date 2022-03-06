#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {

    int reg_val[4] = {1, 0, 0, 0};
    char reg[4][4] = {"eax\0", "ebx\0", "ecx\0", "edx\0"};

    char in_com[4];
    char in_reg[5];
    char number[5];

    int i = 0;
    int ind = 0;
    int num = 0;

    while(ind == 0) {   
         
        scanf("%s", in_com);

        if(in_com[0] != 'r') {

            scanf("%s", in_reg);

            for(i = 0; i < 4; i++) {
                if(reg[i][1] == in_reg[1]) {
                    break;
                }                           //теперь в переменной i лежит номер регистра 
            }

            scanf("%s", number);


            if((number[0] >= '0') & (number[0] <= '9')) {
                num = number[0] - '0';
            }
            else {
                switch (number[1]) {
                    case 'a' : num = reg_val[0]; break;
                    case 'b' : num = reg_val[1]; break;
                    case 'c' : num = reg_val[2]; break;
                    case 'd' : num = reg_val[3]; break;
                }
            }    

            

            switch(in_com[0]) {
                case 'm': reg_val[i] = num; break;
                case 'a': reg_val[i] = reg_val[i] + num; break;
                case 's': reg_val[i] -= num; break;
                default: ind = 1; printf("INPUT ERROR");
            }


            for (int j = 0; j < 4; j++) {
                printf("%d ", reg_val[j]);
            }
            printf("\n");
            
        }
        else {
            ind = 1;
        }
    }
    
}


