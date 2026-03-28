.intel_syntax noprefix
.globl main

.section .text
main:
push rbp
mov rbp, rsp
sub rsp, 32
mov rax, 5
mov [rbp -8], rax
mov rax, 4
mov [rbp -16], rax
mov rax, [rbp -8]
push rax
mov rax, [rbp -16]
pop rbx
add rax, rbx
mov [rbp -24], rax
mov rax, [rbp -24]
mov [rbp -32], rax
mov rax, [rbp -32]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
