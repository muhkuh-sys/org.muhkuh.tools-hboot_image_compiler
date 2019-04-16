#define NETX90_APP_CPU_BOOTBLOCK_MAGIC        0xf3beaf00U
#define NETX90_APP_CPU_BOOTBLOCK_SIGNATURE    0x41505041U


/* Define a structure for all CM4 vectors. */
typedef struct NETX90_APP_CPU_BOOTBLOCK_STRUCT
{
	unsigned long  ulMagic;               /* The magic value NETX90_APP_CPU_BOOTBLOCK_MAGIC. */
	unsigned long aulReserved01[3];       /* Reserved, should be 0. */
	unsigned long  ulImageSizeInDwords;   /* The size of the image starting after this header, counted in DWORDS. */
	unsigned long  ulReserved05;          /* Reserved, should be 0. */
	unsigned long  ulSignature;           /* The signature NETX90_APP_CPU_BOOTBLOCK_SIGNATURE. */
	unsigned long  ulParameter;           /* A pointer to the parameter block. */
	unsigned long aulHash[7];             /* A SHA384 hash over the CM4 header and the complete image. */
	unsigned long  ulChecksum;            /* A simple checksum over this header. */
} NETX90_APP_CPU_BOOTBLOCK_T;


const NETX90_APP_CPU_BOOTBLOCK_T app_cpu_hboot_header __attribute__ ((section (".app_cpu_hboot_header"))) =
{
	.ulMagic = NETX90_APP_CPU_BOOTBLOCK_MAGIC,
	.aulReserved01 = { 0 },
	.ulImageSizeInDwords = 0,
	.ulReserved05 = 0,
	.ulSignature = NETX90_APP_CPU_BOOTBLOCK_SIGNATURE,
	.ulParameter = 0,
	.aulHash = { 0 },
	.ulChecksum = 0
};
