.intel_syntax noprefix
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 8
mov rax, 5
mov [rbp -8], rax
mov rax, 4
mov [rbp -8], rax
mov rax, 6
mov rsp, rbp
pop rbp
ret
