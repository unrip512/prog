#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct Elem {
	int val; // значение, которое хранится в элементе ((!) может быть указателем на строку, например)
	struct Elem * lv, * pr; // указатели на левого и правого потомков
};
struct Elem * root; // глобальная переменная, хранящая указатель на начало дерева

void print_tree_dfs(struct Elem * p){ // рекурсивный обход дерева в глубину
	if (p == NULL){
		return;
	}
	
	print_tree_dfs(p->lv); // распечатать левое поддерево все целиком
	printf("%d ", p->val); // распечатать значение текущего элемента
	print_tree_dfs(p->pr); // распечатать правое поддерево все целиком
	
	return;
}


void add_elem(int x){ // это нерекурсивная реализация, но можете и рекурсивную сделать тоже, по аналогии с print_tree_dfs
	struct Elem * p = (struct Elem *)malloc(sizeof(struct Elem)); // выделить под элемент память
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



 // это нерекурсивная реализация, но можете и рекурсивную делать тоже, по аналогии с print_tree_dfs
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




//Функция, определяющяя, по какому принципу будет выбираться новый элемент: 

//если есть правый потомок, то новым будет являться самый "левый" лист среди правого поддерева
//если правого потомка нет, то самый "правый" лист из левого поддерева
//если потомков нет, то нового элемента не будет, функция вернет NULL

int det_way(struct Elem * el) {

	if(el->pr != NULL) {
		return 1;
	}
	if(el->lv != NULL) {
		return 2;
	}

	return 0;

}



// функция поиска родителя заданного элемента 
struct Elem * find_parent(int x) {
    struct Elem * par;
    par = root;

    if(x == root->val)
        return NULL;
   
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

        if(x < par->val) {
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

struct Elem * find_nel(struct Elem * del) {

	int way = det_way(del);
	struct Elem * new_el;

	if(way == 1) {
		new_el = del->pr;

		while(1) {
			if(new_el->lv == NULL) {
				return new_el;
			}
			else {
				new_el = new_el->lv;
			}
		}

	}
	if(way == 2) {
		new_el = del->lv;

		while(1) {
			if(new_el->pr == NULL) {
				return new_el;
			}
			else {
				new_el = new_el->pr;
			}
		}

	}

	return NULL;

}



//функция удаления элемента дерева

void just_do_it(int p) {

	struct Elem * del_el = find_elem(p);
	int del_el_val = del_el->val;
	struct Elem * prt_del = find_parent(p);
	int prt_del_val = prt_del->val;
	struct Elem * new_el = find_nel(del_el);
	int new_el_val = new_el->val;

	struct Elem * prt_new;
	
	if(new_el != NULL) {
		prt_new = find_parent(new_el->val);
	}

	int prt_new_val = prt_new->val;
	

	//если у СТАРОГО элемента нет потомков

	if(new_el == NULL) {
		if(prt_del != NULL) {
			if(prt_del->val > p) {
				prt_del->lv = NULL;
			}
			else {
				prt_del->pr = NULL;
			}
		}
	}

	//если  у старого элемента потомки есть, то в игру вступает новый элемент. 


	//если родитель нового элемента есть старый элемент 
	if(prt_new == del_el) {
		if(new_el > del_el) {
			new_el->lv = del_el->lv;
		}
		else {

		}

		if(del_el < prt_del) {
			prt_del->lv = new_el;
		}
		else {
			prt_del->pr = new_el;
		}
	}
	else {  //если старый элемент не является родителем нового 
		if(new_el < prt_new) {
			prt_del->lv = NULL;
		}
		else {
			prt_del->pr = NULL; 
		}

		new_el->pr = del_el->pr;
		new_el->lv = del_el->lv;

		if(prt_del != NULL) {
			if(del_el > prt_del) {
				prt_del->pr = new_el;
			}
			if(del_el < prt_del) {
				prt_del->lv = new_el;
			}
		}
	}

	free(del_el);

}




int main () {
    root = NULL;

	int a[18] = {40, 80, 90, 100, 85, 50, 60, 45, 48, 42, 20, 30, 35, 25, 15, 18, 12, 8};

	for (int i = 0; i < 18; i++) {
		add_elem(a[i]);
	}


    print_tree_dfs(root);
    printf("\n");

	int k = 808888;


	just_do_it(k);

	print_tree_dfs(root);



}

