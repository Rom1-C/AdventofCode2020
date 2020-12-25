%define SYS_EXIT 60
%define SYS_WRITE 1
%define STDOUT 1
%define SYS_READ 0
%define SYS_OPEN 2
%define SYS_CLOSE 3
%define STDIN 0

%define BUFFER_SIZE 20

section .bss
input resb BUFFER_SIZE

section .text
global _start
_start:

	add rsp, 10h
	pop rdi				; Taking file from args
	mov rbp, rsp

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
	mov rdi, rsi
	add rdi, r8

_atoi:					; Convert input to int

 .setup:
 	xor eax, eax

 .inner:
 	imul rax, 10
	movzx rbx, byte [rsi]
	add rax, rbx
	sub rax, 48
	inc rsi
	cmp byte [rsi], 10
	jne .inner
	push rax			; Save number in the stack
	inc rsi
	cmp rsi, rdi
	jne .setup
	pop r10				; Put card's code in r10
	pop r15				; and door's code in r15
	mov r14, 7			; The subject number
	mov rdx, 1			; Thue value
	xor rcx, rcx		; Counter of loops
	mov rdi, 20201227	; Thde divider

_solv:

 .first:
	mov rax, rdx
	mul r14
	div rdi
	inc rcx
	cmp rdx, r15
	jne .first
	mov rdx, 1

 .second:
 	mov rax, rdx
 	mul r10
 	div rdi
 	dec rcx
 	cmp rcx, 0
 	jne .second


	; Following part from Alicja Piecha, just to print the result, pretty fast and independant from the challenge.
_itoa:
	mov r10, 10
	sub rsp, 22
	                     
	mov byte [rbp-1], 10   
	lea r12, [rbp-2]
	; r12: string pointer
	mov rax, rdx

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
