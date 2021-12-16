#include <stdio.h>
#include <stdlib.h>

typedef int Data;

struct Node {
	struct Node * next;
	struct Node * prev;
	Data data;
};

//next - указатель на следующий элемент списока (для конца списка - сам список)
//prev- указатель на предыдущий элемент списока (для начала списка - сам список)



// функция, принимающая целое число x и возвращающая структуру со значением x
struct Node * ReadEl (Data x) {

    struct Node * k = (struct Node *)malloc(sizeof(struct Node));

    k -> data = x;
    k -> next = NULL;
    k -> prev = NULL;

    return k; 
}


// функция, которая принимает список и новый элемент и вписывает этот элемент в нужное место списка (располагаем в порядке убывания)
struct Node * add_elem(struct Node * list, struct Node * elem) {

    // проверяем, если списк пуст
    if(list == NULL) {
        list = elem;
        elem -> prev = elem;
        elem -> next = elem;
        return list;
    }
    
    Data x = elem -> data;

    struct Node * temp = list;
                                    //т.к. список не пуст, то находим его последний элемент (адрес этого элемента теперь записан в temp)
    while (temp -> next != list) {       
        temp = temp -> next;
    }

    // если новый элемент больше максимального в списке, то новый элемент становится "головой" списка
    if (x >= (list -> data)) {
        
        elem -> next = list;
        elem -> prev = elem;
        temp -> next = elem;
        list -> prev = elem;

        return elem;
    }
    //если новый элемент меньше минимального, то он становится "хвостом" списка
    if (x <= (temp -> data)) { 
        elem -> next = list;
        elem -> prev = temp;
        temp -> next = elem;

        return list;
    }
    // если мы дошли сюда, значит новый элемент не меньше последнего и не больше первого =>
    //=> в списке уже есть как минимум два элемента и новый должен стоять где-то в середине => 
    // => в списке точно найдется элемент, который будет меньше, чем новый
    else {
        struct Node * temp2;
        temp2 = list;

        while((temp2 -> data) > x) {

            temp2 = temp2 -> next;
        }				//теперь в переменной temp2 записан адрес элемента, перед которым мы должны поставить новый элемент

        elem -> next = temp2;
        elem -> prev = temp2 -> prev;
        temp2 -> prev -> next = elem;
        temp2 -> prev = elem;

        return list;

    }




}

// функция, печатающая весь список

void Print_list( struct Node * list) {

    if (list == NULL) {
        printf("the list is empty");
        return;
    }

    struct Node * temp;
    temp = list;

    while((temp -> next) != list) {
        printf("%d ", temp -> data);
        temp = temp->next;
    }

    printf("%d ", temp -> data);
    printf("\n");

}

//функция, которая очищает память от списка

void clean_list (struct Node * list) {

    struct Node * a;
    a = list;

    while (( list -> next) != a ) {
        list = list -> next;
        free(list -> prev);
    }
    free(list);
}

int main() {

    struct Node * list = NULL;

    struct Node * elem;

    elem = ReadEl(5);
    list = add_elem(list, elem); 

    elem = ReadEl(7);
    list = add_elem(list, elem);

    elem = ReadEl(1);
    list = add_elem(list, elem);

    elem = ReadEl(45);
    list = add_elem(list, elem);
    
    Print_list(list);


    clean_list(list);
    
}
