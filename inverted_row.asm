; Входные данные :  Целое число 0 < N < 10000. Затем N чисел, по модулю не превышающих 2^16-1, через пробел.
; Выходные данные : N чисел в обратном порядке.


;Я представляю решение задачи так: заводим переменную var_2, размер которой равен 4*N байт (т.к. на вход будем получать N целых чисел). Считываем, сколько 
;будет чисел, кладем это число в rax (счетчик цикла), а затем rax раз зовем printf и при каждом считывании кладем считанное число по адресу (var_2 + rcx - 1)
; таким образом образуется массив чисел, которые потом таким же циклом выводим.

; контест показывает, что превышено время выполнения программы. вероятно, каким-то образом зациклился один из циклов, но я не вижу, где ошибка 




global main
extern scanf	
extern printf

section .bss
var: resd 1
var_2: resd 10   ; по моей логике тут должно быть 10000 (ибо N<= 10000), но программа не работает даже на тестах, где всего 3 числа подается, так что проблема точно не тут 

section .text
main:
	mov rdi, format		
	mov rsi, var	
	mov rax, 0	
	call scanf
  
  	xor rcx, rcx
  	mov rcx, [var]
  	mov rdx, [var]
  
	cmp rcx, 0
	je L2

	L:
	mov rdi, format		
	mov rsi, var	
	mov rax, 0			
	call scanf

	sub rcx, 1
	mov rbx, [var]
	mov [var_2 + 4 * rcx], rbx
	add rcx, 1
	loop L

	mov rcx, rdx

	L1:
	mov rbx, rdx
	sub rbx, rcx
	mov rdi, format		
	mov rsi, [var_2 + 4 * rbx]	
	mov rax, 0
	call printf
	loop L1

	L2:


xor rax, rax
ret

format: db "%d", 10, 0
