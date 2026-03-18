.intel_syntax noprefix
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 0
mov rax, 5
mov [rbp -8], rax
mov rax, [rbp -8]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
