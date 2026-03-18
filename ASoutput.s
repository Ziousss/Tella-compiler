.intel_syntax noprefix
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 0
mov rax, 4
mov [rbp -8], rax
mov rax, 4
mov rsp, rbp
pop rbp
ret
