#ifndef	_TIMER_H
#define	_TIMER_H

#include	<stdint.h>
#include	<avr/io.h>
#include	"memory_barrier.h"

// time-related constants
#define	US	* (F_CPU / 1000000)
#define	MS	* (F_CPU / 1000)

/*
clock stuff
*/
extern volatile uint8_t	clock_flag;

#define	CLOCK_FLAG_10MS								1
#define	CLOCK_FLAG_250MS							2
#define	CLOCK_FLAG_1S									4

static inline void clear_clock_flag( uint8_t mask )
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		CLI_BUG_MEMORY_BARRIER();
		clock_flag &= ~ mask;
	}
}

// If the specific bit is set, execute the following block exactly once
// and then clear the flag.
#define	ifclock(F)	for (uint8_t i=1; i>0 && clock_flag & (F); --i,clear_clock_flag(F) )

/*
timer stuff
*/
void timer_init(void) __attribute__ ((cold));

void setTimer(uint32_t delay);

void timer_stop(void);

#endif	/* _TIMER_H */
