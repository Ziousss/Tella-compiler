.intel_syntax noprefix
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 5
mov [rbp -8], rax
mov rbx, 4
mov rax, [rbp -8]
imul rax, 4
lea rcx, [rbp -16]
sub rcx, rax
mov [rcx], rbx
mov rax, 5
imul rax, 4
lea rcx, [rbp -16]
sub rcx, rax
mov rbx, [rcx]
mov [rbp -24], rbx
mov rax, [rbp -24]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
