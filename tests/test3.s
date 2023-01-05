.section .data

.section .text
.globl main

#define MESSAGE "Hello, world!"

main:
mov r0, #1
ldr r1, =MESSAGE
bx lr
