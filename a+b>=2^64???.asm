;Выведите «YES», если A + B ≥ 2^64, и «NO» в противном случае.

;Как я понимаю, 2^64 - это размер регистра  rax. По идее, нужно считатать два действительных числа, сложить их и результат положить в регист rax.
;Если их сумма будет >=2^64, то произойдет переполнение. На это (вроде как) будет указывать флаг OF, поэтому, проверяя его состояние, определяем, 
; сумма больше или меньше 2^64. 
;что то точно идет не так, потому что флаг не меняет своего значения. Из того, какие тесты выводят неправильный результат, можно понять, в каких из них есть переполнение.
;в общем то в двух тестах переполнения нет, а в остальных 8-ми - есть. поэтому контест всегда проходил либо 8, либо 2 теста ...

; есть еще одна идея решения этой задачи
; в rax ложим первое число, в rbx второе. потом от rax отнимаем 2^64, а потом к rax прибавляем rbx. Если сумма входных чисел больше, чем 2^64, в rax окажется положительное
;число, иначе - отрицательное. О чудо!!!! прошлось целых 9 тестов! все кроме одного... 
; по предположениям, либо первое число равно нулю (или вовсе отрицательное) и при вычитании 2^64 там в другую сторону переполняется, либо какое из двух
;чисел изначально больше 2^64 и не помещаются в регистр. Ни то, ни другое пока не представляю как исправлять. Возможно ошибка в чем то другом. 


global main
extern scanf		
extern printf

section .bss
var_1: resd 2
var_2: resd 2

section .text
main:
	mov rdi, format		
	mov rsi, var_1		
	mov rax, 0	
	call scanf

	mov rdi, format	
	mov rsi, var_2		
	mov rax, 0			
	call scanf

	xor rdx, rdx
	xor rax, rax
	xor rbx, rbx
	mov rax, [var_1]
	mov rbx, [var_2]
	
;_________________вариант решения с вычитанием____________
	
	cqo
	sub rax, 18446744073709600000 ; 2^64, простигосподи...
	add rax, rbx
	
	cmp rax, 0
	jge L1 
	jmp L2

	L1: 
	mov rsi, message_1
	mov rdx, 3
	jmp L3

	L2:
	mov rsi, message_2
	mov rdx, 2

	L3:
	mov rax, 1
	mov rdi, 1
	syscall
	
	
;________________ первоначальный вариант решения (с флагом)________

	add rax, rbx
	jo L1
	jmp L2

	L1: 
	mov rsi, message_1
	mov rdx, 3
	jmp L3


	L2:
	mov rsi, message_2
	mov rdx, 2

	L3:
	mov rax, 1
	mov rdi, 1
	syscall

;__________________ниже идет код, общий для обоих вариантов______________


mov eax, 60
xor rdi, rdi
syscall


xor rax, rax
ret

format: db "%d", 10, 0
message_1: db "YES", 10
message_2: db "NO", 10



;итог: если формат считываемых данных сменить с int на long long unsigned,  и использовать флаг переноса CF, то все работает
