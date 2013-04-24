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
		MOV AX, [LSR_PORT]	; (1) Wait for THRE = 1
		IN AX, DX		; AX -> DX
		AND DX, 0x20		; Mask that shit piece out
		TEST DX, 0
		JZ SerialPut		; Equal zero yes? then goto backtto
		MOV DX, [THR_PORT]
		MOV AX, [EBP + 4]
		OUT DX, AX     		;
		RET			; Yolo_return

; ---------------------------------------------------------------------
; void interrupt SerialISR(void)
; ---------------------------------------------------------------------
; This is an Interrupt Service Routine (ISR) for
; serial receive interrupts.  Characters received
; are placed in a queue by calling Enqueue(char).

		GLOBAL	SerialISR
		EXTERN	QueueInsert	; (provided by LIBPC)

SerialISR:	STI			; (1) Enable (higher-priority) IRQs 
		PUSHA			; (2) Preserve all registers 

		MOV AX, [LSR_PORT]	; (3) Get character from UART
		IN AX, DX
		AND DX, 0x01		; See if read buffer is full
		TEST DX, 0
		JZ _Eoi		  	; We got no data (false interrupt)

		MOV AX, [RBR_PORT] 	; Fetch data
		IN AX, DX
		MOV [EBP + 4], DX	; (4) Put character into queue 
					; Param #2: address of data
					; Param #1: address of queue
		CALL	QueueInsert
		ADD	ESP,8

_Eoi:		MOV DX, 0x20		; (5) Enable lower priority interrupts
		MOV AX, 0		;       (Send Non-Specific EOI to PIC)
		OUT DX, AX
		POPA		; (6) Restore all registers
	

		RET			; (7) Return to interrupted code
