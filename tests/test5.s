.section .data

.section .text
.globl main

.macro print_message
mov r0, #1
ldr r1, =MESSAGE
.endm

#define MESSAGE "Hello, world!"

        main:
print_message
        bx lr
