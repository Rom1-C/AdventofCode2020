%define SYS_EXIT 60
%define SYS_WRITE 1
%define STDOUT 1
%define SYS_READ 0
%define SYS_OPEN 2
%define SYS_CLOSE 3
%define STDIN 0

%define BUFFER_SIZE 11000

section .bss
input resb BUFFER_SIZE

section .text
global _start
_start:

	add rsp, 10h
	pop rdi				; Taking file from args
	mov rbp, rsp
	push 2
	push 1
	push 1
	push 7
	push 1
	push 5
	push 1
	push 3
	push 1
	push 1

	mov rax, SYS_OPEN	; Opening file
	mov rsi, 0
	syscall
	mov r13, rax		; File descriptor from rax to r13

_read:

	mov rax, SYS_READ
	mov rdi, r13
	mov rsi, input
	mov rdx, BUFFER_SIZE
	syscall				; Read entire file

	mov rsi, input		; File read in rsi (easier manipulations)
	mov r8, rax			; Number of read bytes
	mov r15, 1			; Counter
	xor r14, r14		; Sub_counter
	xor rbx, rbx		; My x
	xor rcx, rcx		; My y
	pop r10				; x increment
	pop r11				; y increment
	mov rdi, 31			; For the modulo as we loop on a one dimensional array instead of two dimension

_solv:

	xor rdx, rdx
	mov rax, rbx
	div rdi				; x%31 => quotient in rax and remainder in rdx (so our x is already in the pointer)
	mov r12, rcx
	imul r12, 32		; y*32
	add rdx, r12		; rdx is now x%31 + y*32
	add rdx, rsi		; rdx point to the current char
	mov r13, rdx
	sub r13, rsi		; To know how many we read
	cmp r13, r8
	jge .new			; array finished

	cmp byte [rdx], 35	; Compare char to '#'
	jne .add
	inc r14				; inc counter

 .add:
	add rbx, r10		; x+=3
	add rcx, r11		; y++
	jmp _solv

 .new:
 	imul r15, r14
 	xor r14, r14
 	cmp rbp, rsp
 	je _itoa
 	xor rbx, rbx
 	xor rcx, rcx
 	pop r10
 	pop r11
 	jmp _solv


	; Following part from Alicja Piecha, just to print the result, pretty fast and independant from the challenge.
_itoa:
	mov r10, 10
	sub rsp, 22
	                     
	mov byte [rbp-1], 10   
	lea r12, [rbp-2]
	; r12: string pointer
	mov rax, r15

 .loop:
	xor edx, edx
	div r10
	add rdx, 48
	mov [r12], dl
	dec r12
	cmp r12, rsp
	jne .loop

	mov r9, rsp
	mov r11, 22
 .trim:
	inc r9
	dec r11
	cmp byte [r9], 48
	je .trim

	mov rax, 1
	mov rdi, 1
	mov rsi, r9
	mov rdx, r11
	syscall

	mov rax, 60
	mov rdi, 0
	syscall
