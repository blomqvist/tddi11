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
SerialPut:
		MOV	DX, LSR_PORT	; (1) Wait for THRE = 1
		IN 	AL, DX		; AX -> DX
					; Mask that shit piece out
		TEST 	AL, 0x20
		JZ 	SerialPut		; Equal zero yes? then goto backtto
		MOV 	DX, THR_PORT
		MOV 	AL, [ESP + 4]
		OUT 	DX, AL     		;
		RET			; Yolo_return

; ---------------------------------------------------------------------
; void interrupt SerialISR(void)
; ---------------------------------------------------------------------
; This is an Interrupt Service Routine (ISR) for
; serial receive interrupts.  Characters received
; are placed in a queue by calling Enqueue(char).

		GLOBAL	SerialISR
		EXTERN	QueueInsert		; (provided by LIBPC)

SerialISR:	STI				; (1) Enable (higher-priority) IRQ 
		PUSHA				; (2) Preserve all registers 

		MOV 	DX, LSR_PORT		; (3) Get character from UART
		IN 	AL, DX
						; See if read buffer is full
		TEST 	AL, 0x1
		JZ 	_Eoi		  	; We got no data (false interrupt)

		MOV 	DX, RBR_PORT 		; Fetch data
		IN 	AL, DX
						; (4) Put character into queue
		MOV 	[data], AL
		PUSH 	data			; Param #2: address of data
		PUSH 	dword [inbound_queue]	; Param #1: address of queue
				
				
		CALL	QueueInsert
		ADD	ESP,8

_Eoi:					; (5) Enable lower priority interrupt
		MOV 	AL, 0x20	;(Send Non-Specific EOI to PIC)
		OUT 	0x20, AL
		POPA			; (6) Restore all registers

		IRET			; (7) Return to interrupted code
