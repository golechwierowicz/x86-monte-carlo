DEFAULT REL

section .data

randomNumberCount:	dd		0	
screenWidth:		dd 		0	
screenHeight:		dd 		0	
rectangleX:			dd		0	
rectangleXSize:		dd 		0	
rectangleY:			dd		0	
rectangleYSize:		dd		0	
circleX:			dd 		0	
circleY:			dd		0	
circleR:			dd 		0	
inFigure:			dd		0	
decisionFlag:		dq		0
zero:				dq		0	
value:				dq		0
pitch:				dd 		0
colour:				dd 		127
four:				dd 		4
y:					dd 		0
x: 					dd 		0
	
section .text

global _monte_carlo
_monte_carlo:
    push rbp
    mov rbp, rsp

general:
	shl rdi, 1
    mov [randomNumberCount], rdi
    push rax
    mov rax, [rbp + 16]
    mov [pitch], rax
    pop rax
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

 	mov rcx, 0
 	mov rax, 0

loop_trough_random_num:
	; mov r10, [rbp+16]
	; mov dl, 0xCC
	; mov [r10d], dl

check_rectangle:
	movss xmm0, [rsi + rcx*4] 
	subss xmm0, [rectangleX]
	movss xmm1,  [zero]
	comiss xmm0, xmm1

	jb check_circle
	movss xmm1, [rectangleXSize]
	comiss xmm0, xmm1
	ja check_circle

	movss xmm0, [rsi + rcx*4 + 4] 
	subss xmm0, [rectangleY]
	movss xmm1, [zero]
	comiss xmm0, xmm1
	jb check_circle

	movss xmm1, [rectangleYSize]
	comiss xmm0, xmm1
	ja check_circle

	;; means its in rectangle
	inc rax
set_pixel:
	mov bl, 0	
	cvtsi2ss xmm1, [pitch]
	movss xmm2, [rsi+4*rcx + 4] ; y
	mulss xmm1, xmm2 ; y * offset
	cvtsi2ss xmm3, [four]
	movss xmm2, [rsi+4*rcx]
	mulss xmm2, xmm3 ; x*4
	addss xmm1, xmm2
	mov r10, [rbp+24]
	cvtss2si r11, xmm1
	; conver to int
	add r10, r11
	inc r10
	mov byte [r10], bl
	inc r10
	mov byte [r10], bl
	inc r10
	mov byte [r10], bl
	jmp loop_condition
check_circle:

	movss xmm0, [rsi + rcx*4]
	subss xmm0, [circleX]
	mulss xmm0, xmm0
	movss xmm1, [rsi + rcx*4 + 4]
	subss xmm1, [circleY]
	mulss xmm1, xmm1
	addss xmm0, xmm1
	movss xmm1, [circleR]
	mulss xmm1, xmm1
	comiss xmm0, xmm1
	ja loop_condition
	inc rax
set_pixell:
	mov bl, 0	
	cvtsi2ss xmm1, [pitch]
	movss xmm2, [rsi+4*rcx + 4] ; y
	mulss xmm1, xmm2 ; y * offset
	cvtsi2ss xmm3, [four]
	movss xmm2, [rsi+4*rcx]
	mulss xmm2, xmm3 ; x*4
	addss xmm1, xmm2
	mov r10, [rbp+24]
	cvtss2si r11, xmm1
	; conver to int
	add r10, r11
	inc r10
	mov byte [r10], bl
	inc r10
	mov byte [r10], bl
	inc r10
	mov byte [r10], bl

loop_condition:
	add ecx, 2
	cmp ecx, [randomNumberCount]
	jl loop_trough_random_num
end:
	mov [inFigure], eax
	movss xmm1, [inFigure]
	fild dword [screenWidth]
	fstp dword [screenWidth]
	mulss xmm1, [screenWidth]
	fild dword [screenHeight]
	fstp dword [screenHeight]
	mulss xmm1, [screenHeight]
	fild dword [randomNumberCount]
	fstp dword [randomNumberCount]
	divss xmm1, [randomNumberCount]
	movd [value], xmm1
	fild dword [value]
	fstp dword [value]

  	movd xmm0, [value]

    mov rsp, rbp
    pop rbp

    ret
    
