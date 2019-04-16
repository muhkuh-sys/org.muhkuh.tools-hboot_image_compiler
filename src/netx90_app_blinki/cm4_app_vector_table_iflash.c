
/* Define a type for a standard CM4 vector function. */
typedef void (*CM4_VECT_T)(void);


/* Define a structure for all CM4 vectors. */
typedef struct CM4_VECTORS_STRUCT
{
	unsigned long *pulStackTop;          /* 0x00 */

	CM4_VECT_T pfnReset;                 /* 0x04 */
	CM4_VECT_T pfnNMI;                   /* 0x08 */
	CM4_VECT_T pfnHardFault;             /* 0x0C */
	CM4_VECT_T pfnMemManageFault;        /* 0x10 */
	CM4_VECT_T pfnBusFault;              /* 0x14 */
	CM4_VECT_T pfnUsageFault;            /* 0x18 */

	unsigned long aulReserved01C[4];     /* 0x1C - 0x28 */

	CM4_VECT_T pfnSVCall;                /* 0x2C */

	unsigned long ulReserved030;         /* 0x30 */

	unsigned long ulReserved034;         /* 0x34 */

	CM4_VECT_T pfnPendSV;                /* 0x38 */
	CM4_VECT_T pfnSysTick;               /* 0x3C */

	CM4_VECT_T apfnIRQ[96];              /* 0x40 - 0x1BC */
} CM4_VECTORS_T;



extern unsigned long __STACK_TOP_APP_CPU__[];
void start(void);


/* Create an instance of the CM4 vectors. */
const CM4_VECTORS_T cm4_app_vector_table_iflash __attribute__ ((section (".cm4_app_vector_table_iflash"))) =
{
	.pulStackTop = __STACK_TOP_APP_CPU__,
	.pfnReset = start,
	.pfnNMI = 0,
	.pfnHardFault = 0,
	.pfnMemManageFault = 0,
	.pfnBusFault = 0,
	.pfnUsageFault = 0,

	.aulReserved01C = { 0 },

	.pfnSVCall = 0,

	.ulReserved030 = 0,
	.ulReserved034 = 0,

	.pfnPendSV = 0,
	.pfnSysTick = 0,

	.apfnIRQ = { 0 }
};
