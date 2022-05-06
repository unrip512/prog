;Выведите «YES», если A + B ≥ 264, и «NO» в противном случае.

global main
extern scanf		; указываем, что будем вызывать библиотечные функции
extern printf

section .bss
var_1: resq 1
var_2: resq 1

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
xor rbx, rbx
mov rax, [var_1]
mov rdx, rax
mov rbx, [var_2]

add rax, rbx

cmp rax, rbx
jl L1

cmp rax, rdx
jl L1

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

mov eax, 60
xor rdi, rdi
syscall


xor rax, rax
ret

format: db "%d", 10, 0
message_1: db "YES", 10
message_2: db "NO", 10
