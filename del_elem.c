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
	struct Elem * most_right; 
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


// функция поиска родителя заданного элемента 

struct Elem * find_parent(int x) {
    struct Elem * par;
    par = root;

    if(x == root->val) {
        return NULL;
	}
   
    while (1) {

        if(x > par->val) {
            if(par->pr == NULL) {
                return NULL;
            }
            if(par->pr->val == x) {
                return par;
            }
            else {
                par = par->pr;
            }
        }
        else {
            if(par->lv == NULL) {
                return NULL;
            }
            if(par->lv->val == x) {
                return par;
            }
            else {
                par = par->lv;
            }
        }
      
    }

}


//функция поиска нового элемента дерева 

struct Elem * det_new_elem(int x, struct Info * A) {

	struct Elem * del = find_elem(x);

	if(del->lv == NULL) {
		if(del->pr == NULL) {
			return NULL;
		}
		else {
			return del->pr;
		}
	}
	else {
		struct Elem * new_elem = del->lv;
		struct Elem * par_new_elem;


		while(new_elem->pr != NULL) {
			par_new_elem = new_elem;
			new_elem = new_elem->pr;
		}

		A->most_right = new_elem;
		A->parent_most_right = &(par_new_elem->pr);

		return new_elem;
		

	}
}

//функция, заполняющая вспомогательную структуру

void fill_in(int x, struct Info * A) {

	struct Elem * del = find_elem(x);
	struct Elem * par_del = find_parent(x);
	struct Elem * new = det_new_elem(x, A);  // хоть сама переменная new не используется в функции, важно ее обозначить, чтобы выполнилась 
						//функция det_new_elem(x, A), которая отчасти заполняет вспомогательную структуру


	A->del_el = del;

	if(par_del != NULL) {
		if(par_del->val > x) {
			A->p_field = &(par_del->lv);
		}
		else {
			A->p_field = &(par_del->pr);
		}
	}
	else {
		A->p_field = NULL;
	}
}


//функция удаления элемента

void waste_elem(int x, struct Info * A) {
	

	if(A->del_el->lv == NULL) {   //если новый элемент - правый потомок старого (т.е. отсутствует левое поддерево)
		if((root->val) == x) {     // если удаляемый элемент окажется корнем
			root = root->pr;
			free(A->del_el);
		}
		else {                        			// если удаляемый элемент все таки не корень, то...
			*(A->p_field) = A->del_el->pr; 		//меняем потомка у родителя удаляемого элемента (теперь там будет значение нового эл-та)
			free(A->del_el);
		}
	}
	else{ // если новый элемент - максимальный в левом поддереве (случай осуществляется, когда левое поддерево есть)

		if((A->most_right) == (A->del_el->lv)) {                //родитель нового элемента -- старый элемент? Если да, то ... 
			A->most_right->pr = A->del_el->pr;      	// ... то правых потомков у нового элемента нет. Тогда его левые потомки остаются при нем. 
		}						 	// Правый потомок старого элемента становится правым потомком у нового
		else {                                           	// если старый элемент не является родителем нового
			*(A->parent_most_right) = A->most_right->lv;    //левых потомков нового элемента прикрепляем к родителю нового элемента  
			A->most_right->pr = A->del_el->pr;              // левых и правых потомков новый элемент забирает у старого элемента
			A->most_right->lv = A->del_el->lv;
		}

		//Проверяем, является ли удаляемый элемент - корнем. Если нет, то меняем потомка у родителя старого элемента. Если да, то меняем значение корня.

		if(A->del_el == root) {   
			root = A->most_right;
			free(A->del_el);
		}
		else {
			*(A->p_field) = A->most_right;
			free(A->del_el);
		}
		 
	}
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

	int x = 12;

	fill_in(x, A);
	waste_elem(x, A);

    print_tree_dfs(root);
    printf("\n");

	free(A);
}

