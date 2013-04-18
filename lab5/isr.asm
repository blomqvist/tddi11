	SECTION	.data

	EXTERN  _OSIntNesting
	EXTERN  _OSTCBCur
	EXTERN	kybd_queue
	EXTERN	com1_queue

	SECTION	.text
	ALIGN	16
	BITS	32

	GLOBAL	OSKeyboardISR
	GLOBAL	OSSerialISR

	EXTERN  _OSIntEnter
	EXTERN  _OSIntExit
	EXTERN  OSQPost

; --------------------------------------------------------------------
OSKeyboardISR:
; --------------------------------------------------------------------
	PUSHA				; Save interrupted task's context
	CALL	_OSIntEnter		; Notify uC/OS-II of ISR
	CMP	BYTE [_OSIntNesting], 1	; if (OSIntNesting == 1)
	JNE	SHORT _KeyboardISR1             
	MOV	EAX, [_OSTCBCur]	;     OSTCBCur->OSTCBStkPtr = ESP
	MOV	[EAX], ESP
_KeyboardISR1:
	IN	AL,60h			; get scan code
	MOVZX	EAX,AL
	PUSH	EAX
	PUSH	DWORD [kybd_queue]
	CALL	OSQPost
	ADD	ESP,8
	MOV	AL,20H			; Send EOI to PIC
	OUT	20H,AL
	CALL	_OSIntExit		; Notify uC/OS-II of end of ISR
	POPA
	IRET				; Return to interrupted task

; --------------------------------------------------------------------
OSSerialISR:
; --------------------------------------------------------------------
	PUSHA				; Save interrupted task's context
	CALL	_OSIntEnter		; Notify uC/OS-II of ISR
	CMP	BYTE [_OSIntNesting], 1	; if (OSIntNesting == 1)
	JNE	SHORT _SerialISR1
	MOV	EAX, [_OSTCBCur]	;     OSTCBCur->OSTCBStkPtr = ESP
	MOV	[EAX], ESP
_SerialISR1:
	MOV	DX,3F8H
	IN	AL,DX			; get serial byte
	MOVZX	EAX,AL
	PUSH	EAX
	PUSH	DWORD [com1_queue]
	CALL	OSQPost
	ADD	ESP,8
	MOV	AL,20H			; Send EOI to PIC
	OUT	20H,AL
	CALL	_OSIntExit		; Notify uC/OS-II of end of ISR
	POPA
	IRET				; Return to interrupted task

	END
