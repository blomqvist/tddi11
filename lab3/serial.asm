		SECTION	.data
		EXTERN	inbound_queue	; (defined in LAB6.C)
data		DB	0		; put rcvd byte here

		SECTION	.text
		ALIGN	16
		BITS	32

BASE_PORT	EQU	3F8h		; we have this in our lab

LSR_PORT	EQU	BASE_PORT+5
RBR_PORT	EQU	BASE_PORT
THR_PORT	EQU	BASE_PORT

; ---------------------------------------------------------------------
; void SerialPut(char ch)
; ---------------------------------------------------------------------
; This function uses programmed waiting loop I/O
; to output the ASCII character 'ch' to the UART.

		GLOBAL	SerialPut

SerialPut:	; <your code here>	; (1) Wait for THRE = 1
		; <your code here>	; (2) Output character to UART
		; <your code here>	; (3) Return to caller

; ---------------------------------------------------------------------
; void interrupt SerialISR(void)
; ---------------------------------------------------------------------
; This is an Interrupt Service Routine (ISR) for
; serial receive interrupts.  Characters received
; are placed in a queue by calling Enqueue(char).

		GLOBAL	SerialISR
		EXTERN	QueueInsert	; (provided by LIBPC)

SerialISR:	; <your code here>	; (1) Enable (higher-priority) IRQs 
		; <your code here>	; (2) Preserve all registers 
		; <your code here>	; (3) Get character from UART
		; <your code here>	; (4) Put character into queue 
		; <your code here>	; Param #2: address of data
		; <your code here>	; Param #1: address of queue
		CALL	QueueInsert
		ADD	ESP,8

_Eoi:		; <your code here>	; (5) Enable lower priority interrupts
		; <your code here>	;       (Send Non-Specific EOI to PIC)
		; <your code here>	; (6) Restore all registers
		; <your code here>	; (7) Return to interrupted code
