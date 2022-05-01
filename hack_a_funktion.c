#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>


void first_f() {
    printf("yes\n");
    return;

}

void second_f(){
    printf("no\n");
    return;

}

int funk_hack() {

    //данная функция находит адрес первой функции first_f и записывет в ее начало безусловный jump на вторую функцию second_f  
    // вообще говоря, мы не можем так просто переписывать данные в памяти процессора, поэтому здесь используется вызов mprotect

    mprotect(&first_f - (unsigned long long) & first_f %0x1000, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC);

    //Системный вызов mprotect () в C использовался для указания или изменения необходимой защиты страниц памяти процесса.
    // Эта страница (страницы) памяти включает долю или весь диапазон адресов в интервале: [addr, addr + len-1]. 


    *((char*)&first_f) = 0xeb;  // ставим сразу после начала first_f jmp.   0xeb - "имя" jmp-а в памяти процессора
    *((char*)(&first_f + 1)) =  &second_f - &first_f - 2; // сразу после вызова jmp указваем, на сколько байт надо прыгать: нужно 
    // перепрыгнуть разницу между функциями и попасть сразу на начало второй функции
    return 0;
}

int main(){

    first_f();
    second_f();

    funk_hack();

    first_f();
    second_f();

    return 0;
}