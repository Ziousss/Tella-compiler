.intel_syntax noprefix
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 32
mov rbx, 7
mov rax, 2
imul rax, 4
lea rcx, [rbp -16]
sub rcx, rax
mov [rcx], rbx
mov rax, 2
imul rax, 4
lea rcx, [rbp -16]
sub rcx, rax
mov rbx, [rcx]
mov [rbp -32], rbx
mov rax, 4
push rax
mov rax, [rbp -32]
pop rbx
add rax, rbx
mov [rbp -24], rax
mov rax, [rbp -24]
mov [rbp -40], rax
mov rax, [rbp -40]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
