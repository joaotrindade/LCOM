#include "test6.h"

void enable() {
        endpoint_t ep;
        char name[256];
        int priv_f;

        /* Fetch our endpoint */
        sys_whoami(&ep, name, 256, &priv_f);
        /* Enable IO-sensitive operations for ourselves */
        sys_enable_iop(ep);
        asm( "STI" );
}

void disable() {
        endpoint_t ep;
        char name[256];
        int priv_f;

        /* Fetch our endpoint */
        sys_whoami(&ep, name, 256, &priv_f);
        /* Enable IO-sensitive operations for ourselves */
        sys_enable_iop(ep);
        asm( "CLI" );
}

void load_config(unsigned long registers[]){
	disable();
	
	sys_outb(RTC_ADDR_REG, 10);
	sys_inb(RTC_DATA_REG,&registers[0]);
	
	sys_outb(RTC_ADDR_REG, 11);
	sys_inb(RTC_DATA_REG,&registers[1]);
	
	sys_outb(RTC_ADDR_REG, 12);
	sys_inb(RTC_DATA_REG,&registers[2]);
	
	sys_outb(RTC_ADDR_REG, 13);
	sys_inb(RTC_DATA_REG,&registers[3]);
	
	enable();
}

int test_conf() {

	unsigned long registers[4];
	load_config(registers);
	
	printf("Register A: %X \n",register[0]);
	printf("Register B: %X \n",register[1]);
	printf("Register C: %X \n",register[2]);
	printf("Register D: %X \n",register[3]);
	
	return 0;
}
	
int test_date(){
	//implementar aula
	return 0;
}

int test_int(){
	//implementar aula
	return 0;
}