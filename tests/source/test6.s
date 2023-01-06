.section .data

.section .text
.globl main

#define MESSAGE "Hello, world!"

.globl array
array:
.long 1, 2, 3, 4, 5

main:
cmp r0, #2
bne .Lskip
        mov r0, #1
ldr r1, =MESSAGE
.Lskip:
bx lr
