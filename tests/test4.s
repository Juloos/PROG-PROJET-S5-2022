.section .data

.section .text
.globl main

.globl array
array:
  .long 1, 2, 3, 4, 5

main:
  mov r0, #1
  ldr r1, =array
  bx lr
