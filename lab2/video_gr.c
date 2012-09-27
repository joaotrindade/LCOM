#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"

/* Constants for VBE 0x105 mode */

#define VRAM_PHYS_ADDR    0xD0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void * vg_init(unsigned long mode) {

	struct reg86u r;

	r.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
	r.u.w.bx = 1<<14|0x105; // set bit 14: linear framebuffer
	r.u.b.intno = 0x10;
	sys_int86(&r);

	if( sys_int86(& r) != OK ) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return 1;
	}

	return NULL;
}

int vg_fill(unsigned long color) {
	return 0;
}

int vg_set_pixel(unsigned long x, unsigned long y, unsigned long color) {
	return 0;
}

long vg_get_pixel(unsigned long x, unsigned long y) {
	return 0;
}

int vg_draw_line(unsigned long xi, unsigned long yi, 
		 unsigned long xf, unsigned long yf, unsigned long color) {
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
