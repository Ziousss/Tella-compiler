.intel_syntax noprefix
.globl main
.section .rodata
   string_0: .asciz "David"

.section .text
main:
push rbp
mov rbp, rsp
sub rsp, 32
lea rax, [rip + string_0]
mov [rbp -8], rax
mov rax, 5
mov [rbp -16], rax
mov rdi, [rbp -16]
mov rax, 5
push rax
mov rax, 4
pop rbx
add rax, rbx
mov [rbp -24], rax
mov rax, 3
push rax
mov rax, [rbp -24]
pop rbx
imul rax, rbx
mov [rbp -32], rax
mov rax, [rbp -32]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
