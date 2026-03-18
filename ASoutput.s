.intel_syntax noprefix
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 32
mov rax, 0
mov [rbp -8], rax
mov rax, 0
mov [rbp -16], rax
L0:
mov rax, [rbp -16]
push rax
mov rax, 10
pop rbx
cmp rbx, rax
setl al
movzx eax, al
mov [rbp -24], rax
mov rax, [rbp -24]
test rax, rax
je L1
mov rax, [rbp -8]
push rax
mov rax, 1
pop rbx
add rax, rbx
mov [rbp -32], rax
mov rax, [rbp -32]
mov [rbp -8], rax
mov rax, [rbp -16]
push rax
mov rax, 1
pop rbx
add rax, rbx
mov [rbp -40], rax
mov rax, [rbp -40]
mov [rbp -16], rax
jmp L0
L1:
mov rax, [rbp -8]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
