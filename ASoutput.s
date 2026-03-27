.intel_syntax noprefix
.globl main

.section .text
foo:
push rbp
mov rbp, rsp
sub rsp, 0
mov rax, 8
mov rsp, rbp
pop rbp
ret
main:
push rbp
mov rbp, rsp
sub rsp, 0
call foo
mov [rbp -8], rax
mov rax, [rbp -8]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
