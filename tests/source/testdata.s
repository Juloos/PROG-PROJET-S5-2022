.data
buf: .space 40
len: .word 0

.text
.global my_function
my_function:
    ldr r0, =buf
    ldr r1, =len
    add r2, r0, r1
    mov r3, #0
    strb r3, [r2]
    add r1, r1, #1
    str r1, [r1]
    bx lr