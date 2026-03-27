.intel_syntax noprefix
.globl main
.section .rodata
   string_0: .asciz "MyName"

.text
main:
push rbp
mov rbp, rsp
sub rsp, 16
lea rax, [rip + string_0]
mov [rbp -8], rax
mov rax, [rbp -8]
mov [rbp -16], rax
mov rax, 0
mov rsp, rbp
pop rbp
ret
.section .note.GNU-stack,"",@progbits
