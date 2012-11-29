#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"

/* Constants for VBE 0x105 mode */

#define VRAM_PHYS_ADDR    0xD0000000
#define H_RES             1024
#define V_RES		  	  768
#define BITS_PER_PIXEL	  8

/* Private global variables */
char *ptr ;
static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void * vg_init(unsigned long mode) {

	struct reg86u reg;


	  sef_startup();

	reg.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
	reg.u.w.bx = 1<<14|0x105; // set bit 14: linear framebuffer
	reg.u.b.intno = 0x10;
	sys_int86(&reg);

	if( sys_int86(& reg) != OK ) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return NULL;
	}

	h_res = H_RES;
	v_res = V_RES;
	bits_per_pixel = BITS_PER_PIXEL;

	int r;
	struct mem_range mr;

	  /* Allow memory mapping */

	  mr.mr_base = (phys_bytes)VRAM_PHYS_ADDR;
	  mr.mr_limit = mr.mr_base + (H_RES*V_RES);

	  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		  panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

	  /* Map memory */

	  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, (H_RES*V_RES));

	  if(video_mem == MAP_FAILED)
		  panic("video_txt couldn't map video memory");



	return (void *)VRAM_PHYS_ADDR;


}

int vg_fill(unsigned long color) {
	int i ;

	ptr= video_mem;

	for(i=0 ; i<(h_res*v_res) ; i++)
	{
		*ptr=color ;
		ptr++ ;
	}


	return 0;
}

int vg_set_pixel(unsigned long x, unsigned long y, unsigned long color) {

	char *pointer;
	pointer = video_mem;

	pointer = (pointer + (y*H_RES)+x);
	*pointer = color;

	//ptr = video_mem + x*h_res + y;
	//*ptr = color ;

	return 0;
}

long vg_get_pixel(unsigned long x, unsigned long y) {

	long result;
	ptr = video_mem + (x-1)*v_res + y ;
	result = *ptr;
	return result;
}

int vg_draw_line(unsigned long xi, unsigned long yi, 
		 unsigned long xf, unsigned long yf, unsigned long color) {

		float d,y;
		int x;

		d = (yf-yi)/(xf - xi);
		y=yi;
		for(x = xi; x<= xf; x++)
		{
			y += d;
			vg_set_pixel(x,(long)y, color);
		}
	return 0;
}

int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}
