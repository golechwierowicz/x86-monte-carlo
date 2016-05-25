section .text
global _monte_carlo
_monte_carlo:
    push rbp
    mov rbp, rsp

    mov eax, 0
    add eax, 100000

    mov rsp, rbp
    pop rbp

    ret
    
