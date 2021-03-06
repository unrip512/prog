#include <stdio.h>
#include <string.h>


#define len_of_st 11      // длина заменяемой строчки 

void shift( char A[], int N ) {      // функция, сдвигающая на один влево значения ячек массива
    for (int i = 0; i < N-1; i++) {
        A[i] = A[i+1];
    }
}


int main(int argc, char *argv[]) {
   
   FILE * fd;
   
   char c;   //в эту переменную будем посимвольно считывать текст из файла 


   fd = fopen(argv[1], "r+");  //открываем фаил на чтение и на запись
   char A[len_of_st] = {0};    // массив, в котором будет строчка, считываемая из файла
   int n_read = fread(A, 1, len_of_st, fd);  //считываем символы из файла (считываем в массив А, элементы по 1 байту, len_of_st штук, из файла fd )
    
    while(n_read > 0) {   //n_read = 0 если функция fread при считываении достигнет конца файла. Если считывание прошло успешно, то n_read > 0

        if (strcmp (A,"Hallo world") == 0) {  //сравниваем строку из файла и нужную нам строчку (если они окажутся равны, то strcmp вернет 0)
            printf("\n I FOUND IT!!!\n");
            fseek(fd, -len_of_st, 1); // перемещаем "курсор" на len_of_st символов назад, чтобы она оказался в начале слова, которое мы будем заменять
            break;
        }
        n_read = fread(&c, 1, 1, fd); // считываем (в переменную c, 1 байт(т.е. 1 символ), 1 штуку, из файла fd)
        shift(A, len_of_st); // сдвигаем все символы в массиве на один влево
        A[len_of_st-1] = c; // в конец ставим свежепрочитанный символ из файла
    }

    if (n_read == 0) {
        printf("I didn't find it :(  \n");  // если дойдет до конца файла и не найдет нужный текст, то n_read = 0 и все грустно
    }
    else{
        fputs("Separe aude", fd); // заменяем
    }
    

    fclose(fd);
  
 }
