.intel_syntax noprefix
.globl main
.section .rodata
   string_0: .asciz "David"

.section .text
myStrlen:
push rbp
mov rbp, rsp
sub rsp, 48
mov [rbp -8], rdi
mov rax, 0
mov [rbp -16], rax
L0:
mov rax, [rbp -16]
imul rax, 1
mov rcx, [rbp -8]
add rcx, rax
movzx rbx, byte ptr [rcx]
mov [rbp -24], rbx
mov rax, [rbp -24]
push rax
mov rax, 0
pop rbx
cmp rbx, rax
setne al
movzx eax, al
mov [rbp -32], rax
mov rax, [rbp -32]
test rax, rax
je L1
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
mov rax, [rbp -16]
mov rsp, rbp
pop rbp
ret
main:
push rbp
mov rbp, rsp
sub rsp, 32
lea rax, [rip + string_0]
mov [rbp -8], rax
mov rdi, [rbp -8]
mov rsi, [rbp -8]
mov rdx, 5
mov rdi, 1
mov rax, 1
syscall
mov rax, 5
push rax
mov rax, 4
pop rbx
add rax, rbx
mov [rbp -16], rax
mov rax, 3
push rax
mov rax, [rbp -16]
pop rbx
imul rax, rbx
mov [rbp -24], rax
mov rax, [rbp -24]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
