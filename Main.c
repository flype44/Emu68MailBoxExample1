/********************************************************************
 * Program:  Emu68MailBoxExample.c
 * Purpose:  Test the Emu68 1.1+ mailbox.resource
 * Target:   AmigaOS 3.x
 * Compiler: SAS/C Amiga Compiler 6.59
 ********************************************************************/

#include <dos/dos.h>
#include <exec/exec.h>
#include <resources/mailbox.h>

#include <proto/alib.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/mailbox.h>

#ifndef MB_GET_TEMPERATURE
#define MB_GET_TEMPERATURE (0x00030006)
#endif

#ifndef MB_GET_TEMPERATURE_MAX
#define MB_GET_TEMPERATURE_MAX (0x0003000a)
#endif

APTR MailboxBase;

extern struct ExecBase * SysBase;
extern struct DosLibrary * DOSBase;

static BOOL MB_GetTag(ULONG tag, ULONG arg, ULONG * a)
{
	ULONG cmd[8];
	
	if (!a) return (FALSE);
	
	cmd[0] = 8 * 4;  // Request size in bytes
	cmd[1] = 0;      // Request return code
	cmd[2] = tag;    // Request tag identifier
	cmd[3] = 2 * 4;  // Response size in bytes
	cmd[4] = 0;      // Response code
	cmd[5] = arg;    // Response[0]
	cmd[6] = 0;      // Response[1]
	cmd[7] = 0;      // End of request
	
	MB_RawCommand(cmd);
	
	if (cmd[1] == MB_SUCCESS) // Request successful
	{
		* a = cmd[6];
		return (TRUE);
	}
	
	return (FALSE);
}

BOOL MB_GetTemperature(ULONG id, ULONG * temperature)
{
	return MB_GetTag(MB_GET_TEMPERATURE, id, temperature);
}

BOOL MB_GetTemperatureMax(ULONG id, ULONG * temperature)
{
	return MB_GetTag(MB_GET_TEMPERATURE_MAX, id, temperature);
}

ULONG main(ULONG argc, STRPTR * argv)
{
	if (MailboxBase = OpenResource("mailbox.resource"))
	{
		ULONG a, b;
		
		MB_GetTemperature(0, &a);
		MB_GetTemperatureMax(0, &b);
		
		a = (a + 50) / 100;
		b = (b + 50) / 100;
		
		Printf("Temperature:\n%ld.%ld C (Max: %ld.%ld C)\n", 
			a / 10, a % 10, 
			b / 10, b % 10);
	}
	
	return (RETURN_OK);
}
