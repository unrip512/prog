global main
extern scanf	
extern printf

section .bss
a: resd 1 
b: resd 1

section .text
main:
	mov rdi, format		
	mov rsi, a	
	mov rax, 0	
	call scanf
  
	mov rdi, format		
	mov rsi, b	
	mov rax, 0	
	call scanf
  
  cqo
  xor rax, rax
  mov rax, [a]
  mov rbx, [a]
  
  mov rcx, [b]
  cmp rcx, 0
  jne L1
  mov rbx, 0 
  jmp L2
  
  L1:
  xor rdx, rdx
  xor rcx, rcx
  mov ecx, [b]
  idiv ecx ; остаток от деления rax  на b будет в edx
  cmp  rdx, 0 ; если числа поделились нацело
  je L2
  
  mov rax, [a]
  add rbx, rax
  mov rax, rbx
  jmp L1
  
	
	L2:  
  mov rdi, format		; 1й аргумент для вызова printf
	mov rsi, rbx; 2й аргумент для вызова printf
	mov rax, 0
	call printf


xor rax, rax
ret

format: db "%d", 10, 0
