// 1) создать массив на n элементов, (m, n - вводит пользователь), заполнить его; и в регистр rdx положить значение элемента c номером m
//2) массив - это строка, и во всей строке (кроме символа конца строки) нужно поменять регист у букв (A -> a, z -> Z)

#include<stdio.h>
#include<stdlib.h>
#include <string.h>


int main() {

    int n = 100;

    char A[100] = {};
    char * A_ = A;
    char c, i = 0;

    while( (c = getchar()) != '\n' ) {
        A[i] = c;
        i++;
    }

    printf("%d\n", i);

    

    long long  key = 'a';
    long long dlta = 'a'-'A'; // = 32


    asm volatile(

        ".intel_syntax noprefix \n"

        "L:;\n"
            "mov rdx, [rax + (rcx-1)];\n"
            "cmp rbx, rdx;\n"
            "JG L2;\n"                                                // k > A[i] => буква большая

            "L1:;\n" //буква была маленькой, должна стать большой
                "sub rdx, 32;\n"
                
                "mov [rax + (rcx -1)], rdx;\n"
                "jmp L3;\n"



            "L2:;\n" //буква была большая, должна стать маленькой
                "add rdx, 32;\n"
                
                "mov [rax + (rcx-1)], rdx;\n"
                "xor zf, zf;\n"


            "L3:;\n"
        "loop L;\n"

        ".att_syntax noprefix"
        :"=d"(c)
        : "c"(i), "a"(A_), "b"(key)
    ); 

    printf("%s", A);


    

}

