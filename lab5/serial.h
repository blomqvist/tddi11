#define	BASE_PORT	0x3F8

#define	SER_MSK		0x10		/* PIC mask bit for IRQ 4	*/
#define	SER_BASE	0x3F8		/* Base port address for COM1	*/

#define	SER_THR		SER_BASE	/* Transmitter Holding Register	*/
#define	SER_RBR		SER_BASE	/* Receiver Buffer Register	*/
#define	SER_DLO		SER_BASE	/* Baud Rate Divisor Low	*/
#define	SER_DHI		(SER_BASE+1)	/* Baud Rate Divisor High	*/
#define	SER_IER		(SER_BASE+1)	/* Interrupt Enable Register	*/
#define	SER_IIR		(SER_BASE+2)	/* Interrupt Identification Reg	*/
#define	SER_FCR		(SER_BASE+2)	/* FIFO Control Register	*/
#define	SER_LCR		(SER_BASE+3)	/* Line Control Register	*/
#define	SER_MCR		(SER_BASE+4)	/* Modem Control Register	*/
#define	SER_LSR		(SER_BASE+5)	/* Line Status Register		*/
#define	SER_MSR		(SER_BASE+6)	/* Modem Status Register	*/
#define	SER_SCR		(SER_BASE+7)	/* Scratch Register		*/

#define	SER_LSR_THRE	0x20		/* Trans. Hold. Reg. Empty	*/
#define	SER_LSR_RBF	0x01		/* Receiver Buffer Full		*/

#define	SER_LCR_DLAB	0x80		/* Divisor Latch Address Bit	*/

#define	SER_MCR_DTR	0x01		/* Data Terminal Ready		*/
#define	SER_MCR_RTS	0x02		/* Request To Send		*/
#define	SER_MCR_OUT2	0x08		/* Interrupt Enable		*/

void	SerialInit(void) ;
BYTE8	SerialGet(void) ;
void	SerialPut(char) ;
