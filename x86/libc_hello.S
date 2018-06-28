

.globl main
main:
        push $len
        push $msg
        push $1

        call write

        push $7
        call _exit

.data
msg:
        .asciz "Hello, world!\n"

.set len, . - msg

