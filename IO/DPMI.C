/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
 * $Source: f:/miner/source/bios/rcs/dpmi.c $
 * $Revision: 1.19 $
 * $Author: john $
 * $Date: 1995/02/23 09:02:57 $
 * 
 * Routines that access DPMI services...
 * 
 * $Log: dpmi.c $
 * Revision 1.19  1995/02/23  09:02:57  john
 * Fixed bug with dos_selector.
 * 
 * Revision 1.18  1995/02/02  11:10:22  john
 * Made real mode calls have a 2K stack.
 * 
 * Revision 1.17  1995/01/14  19:20:28  john
 * Added function to set a selector's base address.
 * 
 * Revision 1.16  1994/12/14  16:11:40  john
 * Locked down the memory referenced by GETDS.
 * 
 * Revision 1.15  1994/12/06  16:08:06  john
 * MAde memory checking return better results.
 * 
 * Revision 1.14  1994/12/05  23:34:54  john
 * Made dpmi_init lock down GETDS and chain_intr.
 * 
 * Revision 1.13  1994/11/28  21:19:02  john
 * Made memory checking a bit better.
 * 
 * Revision 1.12  1994/11/28  20:22:18  john
 * Added some variables that return the amount of available 
 * memory.
 * 
 * Revision 1.11  1994/11/15  18:27:21  john
 * *** empty log message ***
 * 
 * Revision 1.10  1994/11/15  18:26:45  john
 * Added verbose flag.
 * 
 * Revision 1.9  1994/10/27  19:54:37  john
 * Added unlock region function,.
 * 
 * Revision 1.8  1994/10/05  16:17:31  john
 * Took out locked down message.
 * 
 * Revision 1.7  1994/10/03  17:21:20  john
 * Added the code that allocates a 1K DOS buffer.
 * 
 * Revision 1.6  1994/09/29  18:29:40  john
 * Shorted mem info printout
 * 
 * Revision 1.5  1994/09/27  11:54:35  john
 * Added DPMI init function.
 * 
 * Revision 1.4  1994/09/19  14:50:43  john
 * Took out mono debug.
 * 
 * Revision 1.3  1994/09/19  14:41:23  john
 * Fixed some bugs with allocating selectors.
 * 
 * Revision 1.2  1994/08/24  18:53:51  john
 * Made Cyberman read like normal mouse; added dpmi module; moved
 * mouse from assembly to c. Made mouse buttons return time_down.
 * 
 * Revision 1.1  1994/08/24  10:22:34  john
 * Initial revision
 * 
 * 
 */

// Probably don't even need this code since we're not DOS anymore
static char rcsid[] = "$Id: dpmi.c 1.19 1995/02/23 09:02:57 john Exp $";
#pragma unused(rcsid)

#define far

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "types.h"
#include "mono.h"
#include "error.h"
#include "dpmi.h"
#include "i86.h"

long dpmi_find_dos_memory()
{
#ifndef __LP64__
	// Since sysconf can overflow on 32-bit
	return LONG_MAX;
#else
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return pages * page_size;
#endif
}

void *dpmi_real_malloc( int size, ushort *selector )
{
	return (void *)malloc(size);
}

void dpmi_real_free( ushort selector )
{
	free(selector);
}

void dpmi_real_int386x( ubyte intno, dpmi_real_regs * rregs ) {
}

int dos_stack_initialized = 0;
ubyte * dos_stack = NULL;
ubyte * dos_stack_top = NULL;
#define DOS_STACK_SIZE (4*1024)			// A big ol' 4K stack!!!

void dpmi_real_call(dpmi_real_regs * rregs)
{
	ushort temp_selector;

	if ( !dos_stack_initialized )	{
		dos_stack_initialized = 1;
		dos_stack = dpmi_real_malloc( DOS_STACK_SIZE, &temp_selector );
		if ( dos_stack == NULL )	{
			printf( "Error allocating real mode stack!\n" );
			dos_stack_top = NULL;
		} else {
			dos_stack_top = &dos_stack[DOS_STACK_SIZE];
		}
	}
	
	// Give this puppy a stack!!!
	if ( dos_stack_top )	{
		rregs->ss = DPMI_real_segment(dos_stack_top);
		rregs->sp = DPMI_real_offset(dos_stack_top);
	}
}

int total_bytes = 0;

int dpmi_unlock_region(void *address, unsigned length)
{
	return 1;
}

int dpmi_lock_region(void *address, unsigned length)
{
	return 1;
}

int dpmi_modify_selector_base( ushort selector, void * address )
{
	return 1;
}

int dpmi_modify_selector_limit( ushort selector, int size  )
{
	return 1;
}

int dpmi_allocate_selector( void * address, int size, ushort * selector )
{
	return 1;
}

static void * dpmi_dos_buffer = NULL;
static ushort dpmi_dos_selector = 0;

void dpmi_close()
{
	if (dpmi_dos_selector!=0)	{
		dpmi_dos_buffer = NULL;
		dpmi_dos_selector = 0;
	}
}

typedef struct mem_data {
	int	largest_block_bytes;
	int	max_unlocked_page_allocation;
	int	largest_lockable_pages;
	int	total_pages;
	int	unlocked_pages;
	int	unused_physical_pages;
	int	total_physical_pages;
	int 	free_linear_pages;
	int	paging_size_pages;
	int	reserved[3];
} mem_data;

unsigned int dpmi_virtual_memory=0;
unsigned int dpmi_available_memory=0;
unsigned int dpmi_physical_memory=0;
long dpmi_dos_memory = 0;

extern void __cdecl _GETDS();
extern void __cdecl cstart_();

int dpmi_init(int verbose)
{
	union REGS regs;
	struct SREGS sregs;
	mem_data mi;

	dpmi_dos_memory = dpmi_find_dos_memory();
	
	dpmi_dos_buffer = dpmi_real_malloc( 1024, dpmi_dos_buffer);
	if (!dpmi_dos_buffer) {
		dpmi_dos_selector = 0;
		printf( "Error allocating 1K of DOS memory\n" );
		exit(1);
	}
	atexit(dpmi_close);

		if (verbose) printf( "MemInfo failed!" );
		dpmi_physical_memory = 16*1024*1024;		// Assume 16 MB
		dpmi_available_memory = 16*1024*1024;		// Assume 16 MB
	
	return 1;
}

void *dpmi_get_temp_low_buffer( int size )
{
	if ( dpmi_dos_buffer == NULL ) return NULL;
	if ( size > 1024 ) return NULL;

	return dpmi_dos_buffer;
}

int dpmi_set_pm_handler(unsigned intnum, void far * isr )
{
	return 1;
}
