#ifdef EMUL /* In emulation mode */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>

#include "test5.h"

#else	/* Running on Minix*/

#include <minix/drivers.h>
#include <minix/syslib.h>
#include <minix/com.h>
#include <minix/sysutil.h>

#include "test5.h"

#endif

/*#include "lmlib.h"*/

int main(int argc, char **argv) {
	printf("COMECOU") ;
	test_packet() ;
	printf("ACABOU\n\n") ;
  return 0;

}
