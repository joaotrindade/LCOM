#include <minix/drivers.h>

#include "timer.h"
#include "i8254.h"
#include "speaker.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

#define WAIT_TIME_S 2

int main(int argc, char **argv) {
	
	int i;
	char *video_mem;
	sef_startup();

	timer_subscribe_int();


	speaker_test(12356,20);




	timer_unsubscribe_int();

	return 0;
}
