.intel_syntax noprefix
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 0
mov rax, 99
mov rsp, rbp
pop rbp
ret
