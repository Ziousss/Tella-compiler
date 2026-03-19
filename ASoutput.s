.intel_syntax noprefix
.globl main
main:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 0
mov [rbp -8], rax
L0:
mov rax, [rbp -8]
push rax
mov rax, 1
pop rbx
cmp rbx, rax
sete al
movzx eax, al
mov [rbp -16], rax
mov rax, [rbp -16]
test rax, rax
je L1
mov rax, 6
mov rsp, rbp
pop rbp
ret
jmp L2
L1:
mov rax, 10
mov rsp, rbp
pop rbp
ret
L2:
.section .note.GNU-stack,"",@progbits
