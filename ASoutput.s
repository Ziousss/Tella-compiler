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
cool:
push rbp
mov rbp, rsp
sub rsp, 0
mov rax, 6
mov rsp, rbp
pop rbp
ret
main:
push rbp
mov rbp, rsp
sub rsp, 16
call foo
mov [rbp -8], rax
call cool
mov [rbp -16], rax
mov rax, [rbp -8]
push rax
mov rax, [rbp -16]
pop rbx
add rax, rbx
mov [rbp -24], rax
mov rax, [rbp -24]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
