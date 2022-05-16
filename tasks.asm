F

extern printf
extern scanf
global main

section .text

main:

push y
push x
push scan_format
call scanf
add esp, 12

mov eax, [x]
cmp eax, [y]
cmovg eax, [y]; if eax > [y] mov [y] in eax

push eax
push print_format
call printf
add esp, 8

xor eax, eax
ret

section .data

scan_format db "%d %d", 0
print_format db "%d", 10, 0

section .bss

x resd 1; reserve double word (4 bytes)
y resd 1






---------------------




H

extern scanf
extern printf
global main

section .data

scan_format db "%d %d", 0
print_format db "%d", 10, 0

section .bss

x resd 1
y resd 1

section .text

main:

push y
push x
push scan_format
call scanf
add esp, 12

mov eax, [x]
mov ebx, [y]
cmp eax, ebx
jg norm_cond
xchg eax, ebx

norm_cond: ;normal conditions if a > b (eax > ebx)
cmp ebx, 0
je zero_exception
cdq
idiv ebx
cmp edx, 0
je alg_end
mov eax, edx
xchg eax, ebx
jmp norm_cond

alg_end:

mov eax, [x]
mov ecx, [y]
imul ecx
cdq
idiv ebx
push eax;
push print_format
call printf
add esp, 8

xor eax, eax
ret

zero_exception:

push ebx
push print_format
call printf
add esp, 8

xor eax, eax
ret




--------------------------


I

extern scanf
extern printf
global main

section .data

print_format db "%d ", 0
scan_format db "%d", 0

section .bss
mass resd 10000
x resd 1

section .text

main:

push x
push scan_format
call scanf
add esp, 8

mov ebp, [x]
mov ebx, [x]

scan:
push x
push scan_format
call scanf
mov eax, [x]
mov [mass + 4*ebp - 4], eax
add esp, 8
;push dword [mass + 4*ebp - 4]
;push print_format
;call printf
;add esp, 8
dec ebp
jnz scan

mov ebp, ebx
xor ebx, ebx

print:

push dword [mass + 4*ebx]
push print_format
call printf
add esp, 8
inc ebx
dec ebp
jnz print

xor eax, eax
ret




---------------

J

extern printf
extern scanf
global main

section .text
main:
  push n
  push i
  call scanf
  add esp, 8

  mov edi, a
  mov ecx, [n]

read:
  mov esi, ecx

  push edi
  push i
  call scanf
  add esp, 8
  add edi, 4

  mov ecx, esi

  loop read

do1:
  mov edi, a
  mov ecx, [n]
  dec ecx
  test ecx, ecx
  jz do2
  inc ecx
  mov eax, 1
  mov ebx, 2

gsr:
  cmp eax, ecx
  jnb do2

  mov edx, [edi + 4 * eax - 4]
  add edx, 65536
  mov esi, [edi + 4 * eax]
  add esi, 65536
  cmp edx, esi
  jna case

  mov eax, ebx
  inc ebx

  jmp gsr

case:
  sub edx, 65536
  sub esi, 65536

  mov [edi + 4 * eax], edx
  mov [edi + 4 * eax - 4], esi

  dec eax
  
  test eax, eax
  jnz gsr

  mov eax, ebx
  inc ebx

  jmp gsr

do2:
  mov edi, a
  mov ecx, [n]

write:  
  mov esi, ecx

  mov ebx, a
  mov ebx, [ebx + 4 * ecx - 4]
  push ebx
  push o
  call printf
  add esp, 8

  add edi, 2
  mov ecx, esi

  loop write

end:
  xor eax, eax
  ret

section .data
i db "%d", 0
o db "%d ", 0

section .bss
n resd 1
a dd 10000



------------------------------


K

extern scanf
extern printf 
global main

section .text
main:
  push y
  push x
  push i
  call scanf
  add esp, 12

  fld dword [y]
  fld dword [x]
  fdivr

  sub esp, 8
  fst qword [esp]
  push o
  call printf
  add esp, 12

  xor eax, eax
  ret

section .data
i db "%f%f", 0
o db "%f", 0

section .bss
x resd 1
y resd 1
