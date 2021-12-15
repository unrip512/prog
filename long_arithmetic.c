#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Num {
    
    int m;
    int * a;
    char sign;
};

//функция считывания числа
void Read_Num(struct Num * number) {

    scanf("%d", &(number->m));

    number-> a = (int *)malloc((number->m) * sizeof(int));

    for (int i = 0; i < (number -> m); i++) {
        scanf( "%d", &(number->a[i]) );
    }
}

// функция печати числа
void Print_Num(struct Num number) {

    if(number.sign == '-')
        printf("%c", number.sign);
    for (int i = 0; i < number.m; i++) {
        printf("%d", number.a[i]);
    }

    printf("\n");
}


//функция приведения двух чисел к одинаковой длине
void Same_Len (struct Num * num_1, struct Num * num_2) {
    int m1 = num_1->m;
    int m2 = num_2 -> m;

    if ((m1)>(m2)) {
        int *p = (int*)malloc((m1)* sizeof(int));

        for (int i = 0; i < m1; i++) {
            if(i < (m1-m2))
                p[i] = 0;
            else
                p[i] = num_2->a[i-(m1-m2)];
        }

        free(num_2->a);

        num_2->a = p;
        num_2 -> m = m1;
    }

    if ((m1)<(m2)) {
        int *p = (int*)malloc((m2)* sizeof(int));

        for (int i = 0; i < m2; i++) {
            if(i < (m2-m1))
                p[i] = 0;
            else
                p[i] = num_1->a[i-(m2-m1)];
        }

        free(num_1->a);

        num_1->a = p;
        num_1 -> m = m2;
    }

}

// функция сравнения двух чисел
int Comp (struct Num  num_1, struct Num num_2) {

    int n = num_1.m;
    int a = 0;

    for(int i = 0; i < n; i++) {
        if (num_1.a[i] != num_2.a[i]) {
            a = (num_1.a[i] > num_2.a[i])?1:(-1);
            return a;
        }
    }

    return a;
}

// функция сложения двух чисел
struct Num Add(struct Num num_1, struct Num num_2) {

    struct Num add;

    int n = num_1.m;

    add.m = n+1;

    add.a = (int *)malloc((n+1)* sizeof(int));

    for (int i = 0; i <= n; i++)
        add.a[i] = 0;

    for (int i = n; i > 0; i--) {
        int k = add.a[i];
        add.a[i] = (add.a[i]+ num_1.a[i-1]+num_2.a[i-1]) % 10;
        add.a[i-1] = add.a[i-1] + (k + num_1.a[i-1]+num_2.a[i-1]) / 10;
    }

    return add;
}


//функция вычитания двух чисел
struct Num Subt(struct Num num_1, struct Num num_2) {

    struct Num sub;
    int n = num_1.m;
    sub.m = n;
    

    sub.a = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        sub.a[i] = 0;


    if (Comp(num_1, num_2) == 1) {
        for (int i = (n-1); i >= 0; i--) {
            sub.a[i] = sub.a[i] + num_1.a[i]-num_2.a[i];

            if(sub.a[i] < 0) {
                sub.a[i] = sub.a[i] + 10;
                sub.a[i-1] -= 1;
            }
        }
    }

    if (Comp(num_1, num_2) == -1) {
        for (int i = (n-1); i >= 0; i--) {
            sub.a[i] = sub.a[i]+ num_2.a[i]-num_1.a[i];

            if(sub.a[i] < 0) {
                sub.a[i] = sub.a[i] + 10;
                sub.a[i-1] -= 1;
            }
        }

        sub.sign = '-';
    }

    
    return sub;


}

struct Num Mult(struct Num num_1, int num) {

    struct Num mult;
    int n = num_1.m;

    int * p = (int *)malloc((n+1)*sizeof(int));

    mult.m = n + 1;
    mult.a = p;

    for (int i = 0; i <= n; i++)
        mult.a[i] = 0;

    for (int i = n; i > 0; i--) {

        int k = mult.a[i];
        mult.a[i] = (mult.a[i] + (num_1.a[i-1] * num)) % 10;
        mult.a[i-1] = mult.a[i-1]+ ((k + (num_1.a[i-1] * num)) / 10);
    }

    return mult;



}

struct Num NOD(struct Num num_1, struct Num num_2) {

    int n = num_1.m;  
    struct Num help;

    int * p = (int *)malloc(n * sizeof(int));

    help.a = p;

    while (1) {

        if (Comp(num_1, num_2) == 0)
            return num_1;
    
        if(Comp(num_1, num_2) == 1) {
            help = Subt(num_1, num_2);
            memcpy(num_1.a, help.a, n * sizeof(int));
        }

        if(Comp(num_1, num_2) == -1) {
            help = Subt(num_2, num_1);
            memcpy(num_2.a, help.a, n* sizeof(int));
        }


    }  

    printf("plac");

    free(help.a);

    
}


int main() {

    struct Num first_num, second_num, third_num, fourth_num, fifth_num, nod;

    Read_Num(&first_num);                         // считывает первое число
    Read_Num(&second_num);                        // считывает второе число

    Same_Len(&first_num, &second_num);            // приводит два числа к одинаковой длине

    printf("first number a = ");
    Print_Num(first_num);                        // печатает  оба числа с приведенной длинной
    printf("second number b = ");
    Print_Num(second_num);                      

    printf("a > b? : ");
    int a = Comp(first_num, second_num);        // сравнивает первое и второе число, результат сравнения записывает в переменную а
    printf("%d\n", a);                          // выводит переменную a

    third_num = Add(first_num, second_num);    // третье число равняется сумме первых двух

    printf("a + b = ");
    Print_Num(third_num);                       // выводит трертье число

    fourth_num = Subt(first_num, second_num);  // четвертое число равняется разности первого и второго
    
    printf("a - b = ");
    Print_Num(fourth_num);                      //выводит четвертое число

    int mult_num = 1;

    printf("a * n; n = ");
    scanf("%d", &mult_num);

    fifth_num = Mult(first_num, mult_num);

    printf("a * n = ");
    Print_Num(fifth_num);

    printf("NOD = ");
    nod = NOD(first_num, second_num);

    Print_Num(nod);




    
    free(first_num.a);
    free(second_num.a);
    free(third_num.a);
    free(fourth_num.a);
    free(fifth_num.a);
}
