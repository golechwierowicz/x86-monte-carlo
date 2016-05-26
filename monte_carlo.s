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
decisionFlag:		dq		0
zero:				dq		0	
	
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
	
	mov r12, [rsi + rcx*4 + 4]

check_rectangle:
	fld qword [rsi + rcx*4]
	fsub qword [rectangleX]
	fstp qword [decisionFlag]
	fld qword [decisionFlag]
	fld qword [zero]
	fcomip
	jle check_circle

	fld qword [rsi + rcx*4]
	fsub qword [rectangleX]
	fstp qword [decisionFlag]
	fld qword [decisionFlag]
	fld qword [rectangleXSize]
	fcomip
	jge check_circle

	fld qword [rsi + rcx*4]
	fsub qword [rectangleY]
	fstp qword [decisionFlag]
	fld qword [decisionFlag]
	fld qword [zero]
	fcomip
	jle check_circle

	fld qword [rsi + rcx*4]
	fsub qword [rectangleY]
	fstp qword [decisionFlag]
	fld qword [decisionFlag]
	fld qword [rectangleYSize]
	fcomip
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
    
