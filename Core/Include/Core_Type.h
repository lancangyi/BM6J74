/* ----------------------------------------------------------------------------
 * MODULE Core_Type.h
 *
 *          Copyright (c) 2003 - 2009, All Rights Reserved
 *          Insyde Software Corp.
 *
 * 8051 C Language implementation dependant definitions, global definitions,
 * and processor dependent preprocessor macros for 8051 CPU and Keil Toolset.
 *
 * Revision History (Started Apr 18, 2003 by EDH)
 * (Nov 13, 2003 by MCHT)
 *      - Rename "XBYTE" to "XDATA_BYTE" ("XBYTE" is a reserved word for Keil).
 *      - Rename "DWORD" to "LWORD" ("DWORD" is a reserved word for Keil).
 *      - Remove "BIT0_FIRST" and "BIT_PADDING" (Hardly used it).
 *      - Remove "USE_SBREL"
 * --------------------------------------------------------------------------*/
#ifndef  CORE_TYPES_H
#define CORE_TYPES_H


/*-----------------------------------------------------------------------------
 * Data Parameter definition
 *---------------------------------------------------------------------------*/
#define BIT(X)  (1 << (X))
#define BIT0    0x01
#define BIT1    0x02
#define BIT2    0x04
#define BIT3    0x08
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40
#define BIT7    0x80

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1  // TRUE can be defined as !FALSE but defining
#endif          // it as 1 allows it to fit into a bitfield.

#define MASK_bit0 (1 << 0)
#define MASK_bit1 (1 << 1)
#define MASK_bit2 (1 << 2)
#define MASK_bit3 (1 << 3)
#define MASK_bit4 (1 << 4)
#define MASK_bit5 (1 << 5)
#define MASK_bit6 (1 << 6)
#define MASK_bit7 (1 << 7)
#define CONCAT(a, b) a ## b
#define MASK(x) CONCAT(MASK_, x)

//-----------------------------------------------------------------------------
//  FIELD is used when defining bit-fields within a structure
//  (or union).
//-----------------------------------------------------------------------------
#define FIELD   unsigned char

typedef volatile unsigned char FLAG;
typedef volatile unsigned char xdata XBYTE;     // external ram
typedef volatile unsigned int xdata XWORD;      // external ram
typedef volatile unsigned long xdata  XDWORD;       // external ram
typedef unsigned char BYTE;
typedef volatile unsigned short WORD;
typedef volatile unsigned long DWORD;
typedef volatile unsigned short data IWORD;     // internal ram
typedef volatile unsigned char bdata BBYTE;     // bit addressing ram
typedef volatile unsigned char data  IBYTE;     // internal ram direct
typedef volatile unsigned char idata IIBYTE;    // internal ram indirect
typedef volatile unsigned char xdata *PORT_BYTE_PNTR;
typedef volatile unsigned int xdata *PORT_WORD_PNTR ;//B.J. Chen,2011/06/10
typedef volatile unsigned char xdata ECReg;

typedef volatile unsigned char xdata XU8;
typedef volatile char xdata X8;
typedef volatile unsigned int xdata XU16;
typedef volatile int xdata X16;
typedef volatile unsigned long xdata XU32;
typedef volatile long xdata X32;

typedef volatile unsigned char idata IU8;
typedef volatile char idata I8;
typedef volatile unsigned int idata IU16;
typedef volatile int idata I16;
typedef volatile unsigned long idata IU32;
typedef volatile long idata I32;

#define FU8		unsigned char
#define F8		char
#define FU16		unsigned int
#define F16		int
#define FU32		unsigned long
#define F32		long

//-----------------------------------------------------------------------------
//  MASK operation macros
//-----------------------------------------------------------------------------
#define SET_BIT(reg, bit)           ((reg)|=(0x1<<(bit)))
#define CLR_BIT(reg, bit)           ((reg)&=(~(0x1<<(bit))))
#define CLEAR_BIT(reg, bit)         ((reg)&=(~(0x1<<(bit))))
#define IS_BIT_SET(reg, bit)        (((reg)&(0x1<<(bit)))!=0)
#define IS_BIT_CLEAR(reg, bit)      (((reg)&(0x1<<(bit)))==0)
#define INVERSE_REG(reg, bit)       ((reg)^=(0x1<<(bit)))

#define SET_MASK(reg, bit_mask)     ((reg)|=(bit_mask))
#define READ_MASK(reg, bit_mask)    ((reg)&(bit_mask))
#define CLEAR_MASK(reg, bit_mask)   ((reg)&=(~(bit_mask)))
#define IS_MASK_SET(reg, bit_mask) 	    (((reg)&(bit_mask))!=0)
#define IS_MASK_CLEAR(reg, bit_mask)    (((reg)&(bit_mask))==0)

#define SetFlag(reg, bit)   ((reg)|=(bit))
#define ClearFlag(reg, bit) ((reg)&=(~(bit)))
#define IsFlag1(reg, bit)   (((reg)&(bit))!=0)
#define IsFlag0(reg, bit)   (((reg)&(bit))==0)

#define W_CLR_BIT(reg, bit_mask)		( (reg) = (bit_mask) )

/* ----------------------------------------------------------------------------
   Name: Byte_Mask, Word_Mask, Cpl_Byte_Mask, Cpl_Word_Mask

   Used to create a one-bit mask from a bit number.

    C prototypes:   BYTE Byte_Mask(BYTE bit_number);
                    WORD Word_Mask(BYTE bit_number);
                    BYTE Cpl_Byte_Mask(BYTE bit_number);
                    WORD Cpl_Word_Mask(BYTE bit_number);
   ------------------------------------------------------------------------- */
#define Byte_Mask(x)        (1 << (x))
#define Word_Mask(x)        (1 << (x))
#define Cpl_Byte_Mask(x)    (~(1 << (x)))
#define Cpl_Word_Mask(x)    (~(1 << (x)))


/*-----------------------------------------------------------------------------
 * Data Structure definition
 *---------------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
/* The union of a byte and a structure of bits is used to allow a byte to be
   operated on as well as the bits.  Initialization may be done by operating
   directly on the byte instead of setting or clearing each bit.

   The union must be constructed CAREFULLY so as to enable the bits to line up
   correctly within the byte.  The byte may be sent to the Host which expects
   certain bits to be in certain places within the byte. */
//-----------------------------------------------------------------------------
typedef volatile union _BITS_8
{
    BYTE byte;

    struct
    {
        FIELD bit0: 1;
        FIELD bit1: 1;
        FIELD bit2: 1;
        FIELD bit3: 1;
        FIELD bit4: 1;
        FIELD bit5: 1;
        FIELD bit6: 1;
        FIELD bit7: 1;
    } fbit;
} idata BITS_8;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef union _BITS_16
{
    WORD word;

    struct
    {
        FIELD bit0:  1;
        FIELD bit1:  1;
        FIELD bit2:  1;
        FIELD bit3:  1;
        FIELD bit4:  1;
        FIELD bit5:  1;
        FIELD bit6:  1;
        FIELD bit7:  1;
        FIELD bit8:  1;
        FIELD bit9:  1;
        FIELD bit10: 1;
        FIELD bit11: 1;
        FIELD bit12: 1;
        FIELD bit13: 1;
        FIELD bit14: 1;
        FIELD bit15: 1;
    } fbit;
} BITS_16;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef volatile union _VBITS_8
{
    BYTE byte;

    struct
    {
       FIELD bit0: 1;
       FIELD bit1: 1;
       FIELD bit2: 1;
       FIELD bit3: 1;
       FIELD bit4: 1;
       FIELD bit5: 1;
       FIELD bit6: 1;
       FIELD bit7: 1;
    } fbit;
} idata VBITS_8;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef volatile union _VBITS_16
{
    WORD word;

    struct
    {
       FIELD bit0:  1;
       FIELD bit1:  1;
       FIELD bit2:  1;
       FIELD bit3:  1;
       FIELD bit4:  1;
       FIELD bit5:  1;
       FIELD bit6:  1;
       FIELD bit7:  1;
       FIELD bit8:  1;
       FIELD bit9:  1;
       FIELD bit10: 1;
       FIELD bit11: 1;
       FIELD bit12: 1;
       FIELD bit13: 1;
       FIELD bit14: 1;
       FIELD bit15: 1;
    } fbit;
} VBITS_16;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/* FLAGS are used for general bits. */
typedef volatile struct _FLAGS
{
    FIELD bit0:  1;
    FIELD bit1:  1;
    FIELD bit2:  1;
    FIELD bit3:  1;
    FIELD bit4:  1;
    FIELD bit5:  1;
    FIELD bit6:  1;
    FIELD bit7:  1;
    FIELD bit8:  1;
    FIELD bit9:  1;
    FIELD bit10: 1;
    FIELD bit11: 1;
    FIELD bit12: 1;
    FIELD bit13: 1;
    FIELD bit14: 1;
    FIELD bit15: 1;
} idata FLAGS;

typedef volatile struct _FLAGReg
{
    FIELD bit0:  1;         // BIT0
    FIELD bit1:  1;         // BIT1
    FIELD bit2:  1;         // BIT2
    FIELD bit3:  1;         // BIT3
    FIELD bit4:  1;         // BIT4
    FIELD bit5:  1;         // BIT5
    FIELD bit6:  1;         // BIT6
    FIELD bit7:  1;         // BIT7

} xdata FLAGReg;

typedef volatile union _FLAGReg8
{
    BYTE byte;

    struct
    {
        FIELD bit0: 1;
        FIELD bit1: 1;
        FIELD bit2: 1;
        FIELD bit3: 1;
        FIELD bit4: 1;
        FIELD bit5: 1;
        FIELD bit6: 1;
        FIELD bit7: 1;
    } fbit;

} xdata FLAGReg8;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
union KEY
{
   BYTE byte;
   struct
   {
      FIELD input:            3; /* Bit 0 - 2. Bit address of the KI bit. */
      FIELD debounce_status:  1; /* Bit 3.     Debounce status. */
      FIELD output:           4; /* Bit 4 - 7. Bit address of the KO bit. */
   } field;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
struct Sscan
{
    FIELD kbf_head:  4; /* Keyboard buffer head (0-15). */
    FIELD kbf_tail:  4; /* Keyboard buffer tail (0-15). */
    FIELD kbf_mark:  4; /* Keyboard buffer overflow marker (0-15). */
    FIELD TMscale:   4; /* Typematic scale. */
    FIELD scan_line: 4;
    FIELD saf_make:  1; /* Scan activity flag - make. */
    FIELD saf_break: 1; /* Scan activity flag - break. */
    FIELD saf_keys:  1; /* Scan activity flag - keys active. */
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
union Unew_keyl
{
    BYTE byte;
    struct
    {
        FIELD state: 1; /* Bit[0]   1 means debounce counted out. */
        FIELD trans: 1; /* Bit[1]   1 for BREAK. 0 for MAKE. */
        FIELD intm:  1; /* Bit[2]   */
        FIELD ghost: 1; /* Bit[3]   Ghost key indicator. */
        FIELD same:  1; /* Bit[4]   1 = key activity last time was SAME as
                        /*              this time.                          */
        FIELD count: 3; /* Bit[5:7] Debounce counter. */
    }field;
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/* ----------------------------------------------------------------------------
 * INT_VAR is used for some variables that can be modified by interrupts.
 *
 * Member                  Description
 * Active_Aux_Port         0 = no active aux port, 1 = port 1, etc.
 *                         The port may not actually be active. This could
 *                         signify from which port an ACK is expected.
 *
 * Ticker_10               10 mS timer.
 *
 * Low_Power_Mode          Low power mode flag
 *
 * Scan_Lock               1 = Scanner transmission locked.
 *
 * SMB_Service_Request     When set, 1 mS timer generates a request for service.
 *
 * Ticker_100              100 mS timer.
 * ------------------------------------------------------------------------- */
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef volatile struct _INT_VAR
{
    FIELD Active_Aux_Port:      2;  /* bit[0:1] */
    FIELD Ticker_10:            4;  /* bit[2:5] */
    FIELD Low_Power_Mode:       1;  /* bit[6] */
    FIELD Scan_Lock:            1;  /* bit[7] */
    FIELD SMB_Service_Request:  1;  /* bit[8] */
    FIELD Ticker_100:           7;  /* bit[9:15] or bit[8:14] */
} idata INT_VAR;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef volatile union _TIMER
{
    BYTE byte;
    struct
    {
        FIELD count: 4; /* bit[0:3] */
        FIELD bit4:  1;
        FIELD bit5:  1;
        FIELD bit6:  1;
        FIELD bit7:  1;
    } fbit;
} data TIMER;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef union _KEYPRO_STAT
{
    BYTE byte;
    struct
    {
       FIELD OBreak:   1;   /* Occur Break status */
       FIELD bit1:     1;
       FIELD bit2:     1;
       FIELD bit3:     1;
       FIELD highbits: 4;   /* bit[4:7] */
    } field;
} KEYPRO_STAT;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef union _EXT_CB2
{
    BYTE byte;
    struct
    {
        FIELD bit0 :       1;
        FIELD Break_Count: 3;   /* bit[1:3] */
        FIELD bit4 :       1;
        FIELD Make_Count:  3;   /* bit[5:7] */
    } field;
} idata EXT_CB2;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef volatile struct EC_PORT_IO
{
    FIELD bit0:  1;         // BIT0
    FIELD bit1:  1;         // BIT1
    FIELD bit2:  1;         // BIT2
    FIELD bit3:  1;         // BIT3
    FIELD bit4:  1;         // BIT4
    FIELD bit5:  1;         // BIT5
    FIELD bit6:  1;         // BIT6
    FIELD bit7:  1;         // BIT7

} xdata EC_PORT_IO;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef volatile union _key_state
{
    BYTE byte;
    struct
    {
       FIELD tNUM_LOCK:  1;  /* Bit[0] */
       FIELD tLEFT:      1;  /* Bit[1] */
       FIELD tRIGHT:     1;  /* Bit[2] */
       FIELD tALT:       1;  /* Bit[3] */
       FIELD tCONTROL:   1;  /* Bit[4] */
       FIELD tOVERLAY:   1;  /* Bit[5] */
       FIELD tFN:        1;  /* Bit[6] */
       FIELD tFN_SILENT: 1;  /* Bit[7] */
    } field;
} idata key_state;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef volatile union _IDATA_BITS_8
{
    BYTE byte;
    struct
    {
        FIELD bit0: 1;      // Bit[0]
        FIELD bit1: 1;      // Bit[1]
        FIELD bit2: 1;      // Bit[2]
        FIELD bit3: 1;      // Bit[3]
        FIELD bit4: 1;      // Bit[4]
        FIELD bit5: 1;      // Bit[5]
        FIELD bit6: 1;      // Bit[6]
        FIELD bit7: 1;      // Bit[7]
    } fbit;
} idata IBITS_8;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
typedef volatile union _XDATA_BITS_8
{
    BYTE byte;
    struct
    {
       FIELD bit0:      1;  // Bit[0]
       FIELD bit1:      1;  // Bit[1]
       FIELD bit2:      1;  // Bit[2]
       FIELD bit3:      1;  // Bit[3]
       FIELD bit4:      1;  // Bit[4]
       FIELD bit5:      1;  // Bit[5]
       FIELD bit6:      1;  // Bit[6]
       FIELD bit7:      1;  // Bit[7]
    } field;
} xdata XBITS_8;



typedef struct _tsQstAlgDts
{
	XBYTE	*xAmbTemp;
	XWORD	*xAmbRPMi;
	XWORD	*xAmbRPMe;
} tsQstAlgDts;

//-----------------------------------------------------------------------------
//  Function Pointers
//-----------------------------------------------------------------------------
/* FUNCT_PTR_V_V is a pointer to a function that returns nothing
   (V for void) and takes nothing for a parameter (V for void). */
typedef void (code *FUNCT_PTR_V_V)(void);

/* FUNCT_PTR_V_W is a pointer to a function that returns nothing
   (V for void) and takes a WORD for a parameter (W for WORD). */
typedef void (*FUNCT_PTR_V_W)(WORD);

/* FUNCT_PTR_W_V is a pointer to a function that returns a WORD
   (W for WORD) and takes nothing for a parameter (V for void). */
typedef WORD (*FUNCT_PTR_W_V)(void);

/* FUNCT_PTR_W_W is a pointer to a function that returns a WORD
   (W for WORD) and takes a WORD for a parameter (W for WORD). */
typedef WORD (*FUNCT_PTR_W_W)(WORD);

/* FUNCT_PTR_V_B8 is a pointer to a function that returns nothing
   (V for void) and takes a BITS_8 for a parameter (B8 for BITS_8). */
typedef void (*FUNCT_PTR_V_B8)(BITS_8);

/* FUNCT_PTR_W_B is a pointer to a function that returns a WORD
   (W for WORD) and takes a BYTE for a parameter (B for BYTE). */
typedef WORD (*FUNCT_PTR_W_B)(BYTE);

/* FUNCT_PTR_B_B is a pointer to a function that returns a WORD
   (W for WORD) and takes a BYTE for a parameter (B for BYTE). */
typedef BYTE (code *FUNCT_PTR_B_B)(BYTE);

/* FUNCT_PTR_B_V is a pointer to a function that returns a WORD
   (W for WORD) and takes a BYTE for a parameter (B for BYTE). */
typedef BYTE (code *FUNCT_PTR_B_V)(void);

/* FUNCT_PTR_S_V is a pointer to a function that returns a BYTE
   (S for BYTE) and takes nothing for a parameter (V for void). */
typedef BYTE (*FUNCT_PTR_S_V)(void);

typedef void (*FUNCT_PTR_V_B)(BYTE);

typedef void (*FUNCT_PTR_V_BS)(BYTE,BYTE);

//-----------------------------------------------------------------------------
#endif	// __CORE_TYPES_H__
