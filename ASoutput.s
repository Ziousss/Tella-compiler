.intel_syntax noprefix
.globl main

.section .text
mov rsp, rbp
pop rbp
ret
main:
push rbp
mov rbp, rsp
sub rsp, 32
mov rax, 45
mov [rbp -8], rax
call foo
mov [rbp -16], rax
mov rax, [rbp -16]
push rax
mov rax, [rbp -8]
pop rbx
add rax, rbx
mov [rbp -24], rax
mov rax, [rbp -24]
mov [rbp -32], rax
mov rax, [rbp -32]
mov rsp, rbp
pop rbp
ret
foo:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 5
mov [rbp -8], rax
mov rax, [rbp -8]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
