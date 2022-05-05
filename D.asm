;Напишите программу, делящую 2 числа.

global main
extern scanf		; указываем, что будем вызывать библиотечные функции
extern printf

section .bss
var_1: resd 2
var_2: resd 2

section .text
main:
	mov rdi, format		; 1й аргумент для вызова scanf
	mov rsi, var_1		; 2й аргумент для вызова scanf
	mov rax, 0			; для функций с переменным кол-вом аргументов в rax кладут число вещественных 
	call scanf

	mov rdi, format		; 1й аргумент для вызова scanf
	mov rsi, var_2		; 2й аргумент для вызова scanf
	mov rax, 0			; для функций с переменным кол-вом аргументов в rax кладут число вещественных аргументов
	call scanf



xor rdx, rdx
xor rax, rax
mov rax, [var_1]
mov rbx, [var_2]
idiv rbx
mov [var_1], rax

        
	
	mov rdi, format		; 1й аргумент для вызова printf
	mov rsi, [var_1]	; 2й аргумент для вызова printf
	mov rax, 0
	call printf
	
	xor rax, rax
	ret

format: db "%d", 10, 0
