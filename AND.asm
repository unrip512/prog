global  main						

N equ 10						; это макрос, в тексте программы N везде заменится на 8, аналогично #define N 2 в Си.
							; В программе - это количество символов числа, которое может быть считано, не больше 10,
							; иначе число уже не влезет в реги					; программа работает корректно, только если количество введенных чисел совпадает с N							; и только если нет посторонних символов, например, отрицательные числа дадут непредсказуемый результат
							
code_zero equ 48					; 48 это код нуля в ASCII

section .bss						; аналог секции .data, но позволяющий выделять не инициализированную память
var_read:	resb N					; reserve N bytes, т.е. создали переменную (по сути - массив) var_read состоящую из N ячеек по 1 байту каждая
var_write:	resb N					; reserve N bytes, команда resb N - res - зарезервировать, b - байт, N - N штук
							; вместо b могут быть w - (word) 2 байта, d - (double) 4 байта, q - 8 байт

section .text						; аналог секции .code, тут пишем код
main:							; метка - точка входа, аналог int main() в Си
	call asm_read	
	
	xor ebx, ebx
	xor rcx, rcx
	xor rax, rax
	
	mov rcx, 10
	
	L1:
	
	mov ebx, 10
	mul ebx
	
	xor ebx, ebx
	xor rdx, rdx
	mov rdx, 10
	sub rdx, rcx
	mov bl, [asm_read + rdx]
	cmp bl, 0
	je L2
	
	sub bl, code_zero
	add rax, rbx
	
	loop L1
	
	L2:
	
	xor ebx, ebx
	mov bx, ax
	xor eax, eax
	mov ax, bx         ;теперь в eax лежит остаток от деления
	
	mov rdx, 10
	sub rdx, rcx
	mov rcx, rdx
	
	
	L3:
	xor rdx, rdx
	mov ebx, 10
	div ebx
	
	add rdx, code_zero
	mov rbx, rcx
	dec rbx
	mov [var_write + rbx], dl
	loop L3

	call asm_write
	call asm_exit

asm_read:					
	mov rax, 0					; в rax кладем номер системного вызова, кот
	mov rdi, 0					; определяем, откуда надо считать данные 0 это stdin - т.е. считываем из консоли 			; (она же командная строка/терминал, и т.д.)
	mov rsi, var_read				; считает результат посимвольно в строго определенную переменную var_read
	mov rdx, N					; указывает столько байт, сколько нужно считать, тут он должен заполнить весь массив целиком
	syscall						; делает "системный вызов" (это термин, "system call"), т.е. зовет функцию операционной системы 
	ret						; ret нужен, чтобы корректно выйти из wrapper'a.
	
asm_write:						; wrapper - функция, в которую "завернут" стандартный вызов write
	mov rax, 1					; 1 - номер системного вызова write - считывает посимвольно
	mov rdi, 1					; rdi - откуда считываем, 1 это stdout  - т.е. командная строка
	mov rsi, var_write
	mov rdx, 5 				; rdx - кол-во байт, т.е. в консоль будет выведено N байт начиная с адреса var_write
	syscall						; rax, rdi, rsi, rdx - содержат параметры для этого вызова
	ret

asm_exit:						; wrapper - функция, в которую "завернут" стандартный вызов exit
	mov rax, 60					; 60 - номер системного вызова exit - завершить программу
	xor rdi, rdi					; rdi = 0 - код, с которым завершится исполнение программы
	syscall
	ret
