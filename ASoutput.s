.intel_syntax noprefix
.globl main
.section .rodata
   string_0: .asciz "Hello\n"

.section .text
mov rsp, rbp
pop rbp
ret
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
sub rsp, 0
lea rdi, [rip + string_0]
lea rsi, [rip + string_0]
mov rdx, 7
mov rdi, 1
mov rax, 1
syscall
mov rsp, rbp
pop rbp
ret
foo:
push rbp
mov rbp, rsp
sub rsp, 16
mov rax, 5
mov [rbp -8], rax
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
