#include <vectrex.h>

// this is quite a "C" optimized version of print_sync
// it is actually FASTER than
// the "not very optimized" assembler include!
// (-O3 and no_frame_pointer)
void cDraw_synced_list(
signed char *u,
signed int y,
signed int x,
unsigned int scaleMove,
unsigned int scaleList)
{
	#define ZERO_DELAY 5
	
	do
	{
		// resnyc / startsync
		
		dp_VIA_shift_reg = 0;		// all output is BLANK
		dp_VIA_cntl = 0xcc;	// zero the integrators
		dp_VIA_port_a = 0;    		// reset integrator offset
		dp_VIA_port_b = (int)0b10000010;
		
		dp_VIA_t1_cnt_lo = scaleMove;
		// delay, till beam is at zero
		// volatile - otherwise delay loop does not work with -O
		for (volatile signed int b=ZERO_DELAY; b>0; b--);
		dp_VIA_port_b= (int)0b10000011;
		
		// move to "location"
		dp_VIA_port_a = y;			// y pos to dac
		dp_VIA_cntl = 0xce;	// disable zero, disable all blank
		dp_VIA_port_b = 0;			// mux enable, dac to -> integrator y (and x)
		dp_VIA_port_b = 1;			// mux disable, dac only to x
		dp_VIA_port_a = x;			// dac -> x
		dp_VIA_t1_cnt_hi=0;		// start timer
		
		// this can be done before the wait loop
		// since it only fills the latch, not the actual timer!
		dp_VIA_t1_cnt_lo = scaleList;
		u+=3;
		
		// moveing test for yx== 0 into the move delay
		if ((*(u-2)!=0) || (*(u-1)!=0))
		{
			while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
			
			// internal moveTo
			dp_VIA_port_a = *(u-2);	// y pos to dac
			dp_VIA_cntl = 0xce;	// disable zero, disable all blank
			dp_VIA_port_b = 0;			// mux enable, dac to -> integrator y (and x)
			dp_VIA_port_b = 1;			// mux disable, dac only to x
			dp_VIA_port_a = *(u-1);	// dac -> x
			dp_VIA_t1_cnt_hi=0;		// start timer
			while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
		}
		else
		{
			while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
		}
		
		while (1)
		{
			if (*u<0) // draw line
			{
				// draw a vector
				dp_VIA_port_a = *(1+u);	// y pos to dac
				dp_VIA_port_b = 0;			// mux enable, dac to -> integrator y (and x)
				dp_VIA_port_b=1;			// mux disable, dac only to x
				dp_VIA_port_a = *(2+u);	// dac -> x
				dp_VIA_t1_cnt_hi=0;		// start timer
				dp_VIA_shift_reg = 0xff;		// draw complete line
				while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
				dp_VIA_shift_reg = 0;		// all output is BLANK
			}
			else if (*u == 0) // moveTo
			{
				if ((*(u+1)!=0) || (*(u+2)!=0))
				{
					// internal moveTo
					dp_VIA_port_a = *(1+u);	// y pos to dac
					dp_VIA_cntl = 0xce;	// disable zero, disable all blank
					dp_VIA_port_b = 0;			// mux enable, dac to -> integrator y (and x)
					dp_VIA_port_b =1 ;			// mux disable, dac only to x
					dp_VIA_port_a = *(2+u);	// dac -> x
					dp_VIA_t1_cnt_hi=0;		// start timer
					while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
				}
			}
			else
			{
				break;
			}
			u+=3;
		}
	} while (*u != 2);
}

void cMov_Draw_VLc_a(signed char *vList)
{
	register int count = *(vList)-1;	// count in list
	dp_VIA_port_a = *(1+vList);	// y pos to dac
	dp_VIA_cntl = 0xce;	// disable zero, disable all blank
	dp_VIA_port_b = 0;			// mux enable, dac to -> integrator y (and x)
	dp_VIA_port_b = 1;			// mux disable, dac only to x
	dp_VIA_port_a = *(2+vList);	// dac -> x
	dp_VIA_t1_cnt_hi=0;		// start timer
	vList+=3;
	while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
	
	do 
	{
		dp_VIA_port_a = *(vList);	// first y coordinate to dac
		dp_VIA_port_b = 0;				// mux enable, dac to -> integrator y (and x)
		dp_VIA_port_b = 1;				// mux disable, dac only to x
		dp_VIA_port_a = *(vList+1);	// dac -> x
		dp_VIA_shift_reg = 0xff; // full "unblank" output
		dp_VIA_t1_cnt_hi = 0;			// start timer
		vList+=2;
		while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
		dp_VIA_shift_reg = 0;			// output full blank
	} while (--count >=0);			// loop thru all vectors
}
void cDraw_VLc(signed char *vList)
{
	register int count = *(vList++);	// count in list
	do 
	{
		dp_VIA_port_a = *(vList);	// first y coordinate to dac
		dp_VIA_port_b = 0;				// mux enable, dac to -> integrator y (and x)
		dp_VIA_port_b = 1;				// mux disable, dac only to x
		dp_VIA_port_a = *(vList+1);	// dac -> x
		dp_VIA_shift_reg = 0xff; // full "unblank" output
		dp_VIA_t1_cnt_hi = 0;			// start timer
		vList+=2;
		while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
		dp_VIA_shift_reg = 0;			// output full blank
	} while (--count >=0);			// loop thru all vectors
}
// 0 = move
// >1 = draw
// 1 = end
// (-O3 and no_frame_pointer)
void cDraw_VL_mode(signed char *u)
{
	while (1)
	{
		if (*u>1) // draw line
		{
			// draw a vector
			dp_VIA_port_a = *(1+u);	// y pos to dac
			dp_VIA_port_b = 0;		// mux enable, dac to -> integrator y (and x)
			dp_VIA_port_b=1;			// mux disable, dac only to x
			dp_VIA_port_a = *(2+u);	// dac -> x
			dp_VIA_t1_cnt_hi=0;		// start timer
			dp_VIA_shift_reg = 0xff;		// draw complete line
			while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
			dp_VIA_shift_reg = 0;		// all output is BLANK
		}
		else if (*u == 0) // moveTo
		{
			// internal moveTo
			dp_VIA_port_a = *(1+u);	// y pos to dac
			dp_VIA_cntl = 0xce;	// disable zero, disable all blank
			dp_VIA_port_b = 0;		// mux enable, dac to -> integrator y (and x)
			dp_VIA_port_b =1 ;		// mux disable, dac only to x
			dp_VIA_port_a = *(2+u);	// dac -> x
			dp_VIA_t1_cnt_hi=0;		// start timer
			while ((dp_VIA_int_flags & 0x40) == 0); // wait till timer finishes
		}
		else
		{
			break;
		}
		u+=3;
	}
}

