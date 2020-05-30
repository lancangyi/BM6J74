//-----------------------------------------------------------------------------
//For SW KBC
//-----------------------------------------------------------------------------
#ifndef OEM_SWKBC_H
#define OEM_SWKBC_H


#define KBF_SIZE    			16

extern void Init_SWKBC(void);
extern void Data_To_Host(BYTE data_byte);
extern BYTE Buffer_Key(BYTE bKBData);
extern BYTE Get_KB_Buffer(void);
extern void Clr_KB_Buffer(void);

extern void BTN_VolUpPulse(void);
extern void BTN_VolDownPulse(void);

#endif