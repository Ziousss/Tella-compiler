.intel_syntax noprefix
.globl main
.section .rodata
   string_0: .asciz "This is a test\n"

.section .text
main:
push rbp
mov rbp, rsp
sub rsp, 32
mov rax, 0
mov [rbp -8], rax
L0:
mov rax, [rbp -8]
push rax
mov rax, 6
pop rbx
cmp rbx, rax
setl al
movzx eax, al
mov [rbp -16], rax
mov rax, [rbp -16]
test rax, rax
je L1
lea rdi, [rip + string_0]
lea rsi, [rip + string_0]
mov rdx, 16
mov rdi, 1
mov rax, 1
syscall
mov rax, [rbp -8]
push rax
mov rax, 1
pop rbx
add rax, rbx
mov [rbp -24], rax
mov rax, [rbp -24]
mov [rbp -8], rax
jmp L0
L1:
mov rax, 0
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
