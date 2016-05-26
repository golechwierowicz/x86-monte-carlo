DEFAULT REL

extern printf

section .data

randomNumberCount:	resd	1
screenWidth:		resd 	1
screenHeight:		resd 	1
rectangleX:			resd	1
rectangleXSize:		resd 	1
rectangleY:			resd	1
rectangleYSize:		resd	1
circleX:			resd 	1
circleY:			resd	1
circleR:			resd 	1
inFigure:			resd	1
	
section .text

global _monte_carlo
_monte_carlo:
    push rbp
    mov rbp, rsp

general:
    mov [randomNumberCount], rdi    
    mov [screenWidth], r8
 	mov [screenHeight], r9

rectangle:
 	mov r10, [rdx]
 	mov [rectangleX], r10

 	mov r10, [rdx+4]
 	mov [rectangleXSize], r10

 	mov r10, [rdx+8]
 	mov [rectangleY], r10

 	mov r10, [rdx+12]
 	mov [rectangleYSize], r10

circle:
	mov r10, [rcx]
 	mov [circleX], r10
 	mov r10, [rcx+4]
 	mov [circleY], r10
 	mov r10, [rcx+8]
 	mov [circleR], r10

 	mov rcx, 1
 	mov rax, 0

loop_trough_random_num:
	
	mov r11, [rsi + rcx*4]
	mov r12, [rsi + rcx*4 + 4]
	
check_rectangle:
	sub r11, [rectangleX]
	cmp r11d, 0
	jle check_circle
	cmp r11d, [rectangleX]
	jge check_circle
	sub r12, [rectangleY]
	cmp r12d, 0
	jle check_circle
	cmp r12d, [rectangleY]
	jge check_circle
	;; means its in rectangle
	add rax, 1
	jmp loop_condition
check_circle:

loop_condition:	
	add rcx, 1
	cmp ecx, [randomNumberCount]
	jle loop_trough_random_num
end:
	; fild dword [rcx]
  	movd xmm0, [rsi]

    mov rsp, rbp
    pop rbp

    ret
    
