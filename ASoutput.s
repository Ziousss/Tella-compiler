.intel_syntax noprefix
.globl main
.section .rodata
   string_0: .asciz "hello"

.section .text
main:
push rbp
mov rbp, rsp
sub rsp, 16
lea rax, [rip + string_0]
mov [rbp -8], rax
mov rax, 4
imul rax, 1
lea rcx, [rbp -8]
sub rcx, rax
mov rbx, [rcx]
mov [rbp -16], rbx
mov rax, [rbp -16]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
