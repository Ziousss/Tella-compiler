.intel_syntax noprefix
.globl main
.section .rodata
   string_0: .asciz "hello"

.section .text
mov rsp, rbp
pop rbp
ret
main:
push rbp
mov rbp, rsp
sub rsp, 16
lea rax, [rip + string_0]
mov [rbp -8], rax
mov rax, 0
imul rax, 1
mov rcx, [rbp -8]
add rcx, rax
movzx rbx, byte ptr [rcx]
mov [rbp -16], rbx
mov rax, [rbp -16]
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
