#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct Elem {
	int val;
	struct Elem * lv, * pr; 
};
struct Elem * root; 

struct Info {
	struct Elem ** p_field;
	struct Elem * del_el;
	struct Elem * rookie; 
    struct Elem ** parent_most_right;
};


void print_tree_dfs(struct Elem * p){ 
	if (p == NULL){
		return;
	}
	
	print_tree_dfs(p->lv); 	
	printf("%d ", p->val); 
	print_tree_dfs(p->pr); 
	
	return;
}


void add_elem(int x){ 
	struct Elem * p = (struct Elem *)malloc(sizeof(struct Elem)); 
	p->val = x; // заполнить его поля
	p->lv = NULL;
	p->pr = NULL;
	
	// ищем для него подходящее место в дереве
	// если дерево пусто
	if (root == NULL){
		root = p;
		return;
	}
	
	// если дерево не пусто, ищем для него родительский элемент (вставляем только как лист)
	struct Elem * q = root;
	while(1){
		if (x < q->val){ // если x меньше, чем значение текущего элемента, то вставляем в левое поддерево
			if (q->lv != NULL){
				q = q->lv; // переходим в левого потомка текущего элемента
			}
			else{
				q->lv = p; // вставляем новый элемент, если левого потомка не было
				break;
			}
		}
		else{ // если x больше или равно, то - в правое поддерево
			if (q->pr != NULL){
				q = q->pr; // переход в правого потомка
			}
			else{
				q->pr = p; // вставка в качестве правого потомка
				break;
			}
		}
	}

	return;
}



 
struct Elem * find_elem(int x){ // проход по дереву в этом случае аналогичен add_elem

	if (root == NULL){
		printf("Empty tree");
		return NULL;
	}
	
	struct Elem * p = root; // p - будет указателем на текущий элемент на каждой итерации
	while(1){
		if(x == p->val) // если значение совпало - мы нашли нужный элемент
			return p;
		if(x < p->val){ // если x меньше, идем искать в левом поддереве
			if(p->lv != NULL)
				p = p->lv; // если левое поддерево есть - переходим левого потомка
			else
				return NULL; // если левого поддерева нет - значит не нашли нужный элемент
		}
		if(x > p->val){ // если x больше, идем искать в правом поддереве
			if(p->pr != NULL)
				p = p->pr;
			else
				return NULL;
		}
	}
	
	return NULL;
}


// Функция поиска родителя заданного элемента 
// Ищет родителя некоторого элемента и записывает в элемент структуры указатель на поле внутри радительского элемента 
// возвращает 0, если родитель найден 
// возвращает -1, если элемент - корень (т.е. родителя нет)
// возвращает -2, если в дереве такого элемента не нашлось

int find_parent(int x, struct Elem *** a)  {
    struct Elem * par;
    par = root;

    if(x == root->val) {
        *a = NULL;
		return -1;
	}
   
    while (1) {

        if(x > par->val) {
            if(par->pr == NULL) {
                *a = NULL;
				return -2;
            }
            if(par->pr->val == x) {
                *a = &(par->pr);
				return 0;
            }
            else {
                par = par->pr;
            }
        }
        else {
            if(par->lv == NULL) {
                *a = NULL;
				return -2;
            }
            if(par->lv->val == x) {
				*a = &(par->lv);
                return 0;
            }
            else {
                par = par->lv;
            }
        }
      
    }

}


//Функция поиска нового элемента дерева 
// rookie - элемент структуры Info, в котором хранится адрес нового элемента (вне зависимости от того, какой именно эл-т явл. новым)
// функция ищет новый элемент и записывает в структуру Info как адрес нового эл-та, так и указатель на поле внутри родителя новогоэлемента
// возвращает 0, если новый эл-т - крайний правый в левом поддереве
// возвращает 1, если новый эл-т - правый потомок удаляемого  (в случ., когда нет левого поддерева)
// возвращает -1, если у удаляемого эл-та нет потомков
// возвращает -2, если в дереве не нашлось заданного эл-та.



int det_new_elem(int x, struct Info * A) {

	struct Elem * del = find_elem(x);

	if(del == NULL) {
		return -2;
	}
	A -> del_el = del;

	if(del->lv == NULL) {
		if(del->pr == NULL) {
			return -1;
			A->rookie = NULL; 
		}
		else {
			return 1;
			A -> rookie = del->pr;;
		}
	}
	else {
		struct Elem * new_elem = del->lv;
		struct Elem * par_new_elem;


		while(new_elem->pr != NULL) {
			par_new_elem = new_elem;
			new_elem = new_elem->pr;
		}

		A->rookie = new_elem;
		A->parent_most_right = &(par_new_elem->pr);

		return 0;
		

	}
}

//Функция удаления элемента
//собственно, удаляет
//возвращает 0, если все прошло нормально
//возвращает -1, если в дереве не нашлось удаляемого эл-та

int waste_elem(int x, struct Info * A) {

	int X = find_parent(x, &(A->p_field));
	int Y = det_new_elem(x, A);

	if(Y == -2) {
		return -1 ;
	}

	if(Y != 0) {   //если новый элемент - правый потомок старого (т.е. отсутствует левое поддерево)
		if(X == -1) {     // если удаляемый элемент окажется корнем
			root = root->pr;
			free(A->del_el);
		}
		else {  // если удаляемый элемент все таки не корень, то...
			*(A->p_field) = A->del_el->pr; //меняем потомка у родителя удаляемого элемента (теперь там будет значение нового эл-та)
			free(A->del_el);
		}
	}
	else{ // если новый элемент - максимальный в левом поддереве (случай осуществляется, когда левое поддерево есть)

		if((A->rookie) == (A->del_el->lv)) { //родитель нового элемента -- старый элемент? Если да, то ... 
			A->rookie->pr = A->del_el->pr; // ... то правых потомков у нового элемента нет. Тогда его левые потомки остаются при нем. 
		}										// Правый потомок старого элемента становится правым потомком у нового
		else {    // если старый элемент не является родителем нового
			*(A->parent_most_right) = A->rookie->lv;  //левых потомков нового элемента прикрепляем к родителю нового элемента  
			A->rookie->pr = A->del_el->pr;  // левых и правых потомков новый элемент забирает у старого элемента
			A->rookie->lv = A->del_el->lv;
		}

		//Проверяем, является ли удаляемый элемент - корнем. Если нет, то меняем потомка у родителя старого элемента. Если да, то меняем значение корня.

		if(X == -1) {   
			root = A->rookie;
			free(A->del_el);
		}
		else {
			*(A->p_field) = A->rookie;
			free(A->del_el);
		}
		 
	}
	return 0;
}




int main () {

    root = NULL;
	int num = 15;

	int a[15] = {9, 25, 40, 45, 32, 15, 18, 12, 5, 7, 3, 4, 1, 16, 13};

	struct Info * A = (struct Info *)malloc(sizeof(struct Info));

	for (int i = 0; i < num; i++) {
		add_elem(a[i]);
	}

	print_tree_dfs(root);
	printf("\n");

	int x = 0;
	scanf("%d", &x);

	int k = waste_elem(x, A);

    if(k == 0) {
		print_tree_dfs(root);
	}
	else {
		printf("Элемент отсутствует.");
	}
	
    printf("\n");

	free(A);
}

