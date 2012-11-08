#include "test6.h"

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define BIT_POS(N) ( 1U << (N) )

int hook = 2;

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

int checkValue(unsigned long registo, unsigned long bit)
{
	if (registo  & bit) return 1;
	else return 0;

}

int test_conf() {

	unsigned long registers[4];
	load_config(registers);

	printf("Register A: %X \n",registers[0]);
	printf("UIP: %d \n\n", checkValue(registers[0],(1<<7)));

	printf("Register B: %X \n",registers[1]);
	printf("UIE: %d \n\n", checkValue(registers[1],(1<<4)));
	printf("24/12: %d \n\n", checkValue(registers[1],(1<<2)));

	printf("Register C: %X \n",registers[2]);
	printf("Register D: %X \n",registers[3]);
	


	return 0;
}
	
int rtc_subscribe_int(void ) {

	sys_irqsetpolicy(8, IRQ_REENABLE|IRQ_EXCLUSIVE, &hook);
	sys_irqenable(&hook);
	return 1;
}

int rtc_unsubscribe_int() {
	sys_irqdisable(&hook);
	return 1;
}

int test_date(){

	unsigned long regB, regC;
	int UFbit, finish;
	unsigned long dia, mes, ano, hora, minuto, segundo;
	int ipc_status ;
	message msg ;
	UFbit = 0;
	finish= 0;

	enable();


	//Fazer set ao B

	sys_outb(RTC_ADDR_REG, 11);
	sys_inb(RTC_DATA_REG,&regB);

	//regB = regB&0x10;
	regB |= 1 << 4;

	sys_outb(RTC_ADDR_REG,11);
	sys_outb(RTC_ADDR_REG,&regB);

	// Ciclo interrupcoes

	rtc_subscribe_int();

	while( finish == 0 ) {
		if ( driver_receive(ANY, &msg, &ipc_status) != 0 ) {
			//printf("driver_receive failed with: %d", r);
			printf("driver_receive failed");
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					printf("entrou1");
					if (msg.NOTIFY_ARG & 0x4)
					{
						printf("entrou2");
						sys_outb(RTC_ADDR_REG, 12);
						sys_inb(RTC_DATA_REG,&regC);

						if ((regC&0x80) == 0x80)
							{
								finish = 1;
								// Registo C
								sys_outb(RTC_ADDR_REG, 12);
								sys_inb(RTC_DATA_REG,&regC);

								printf("regC: %X", regC);
								printf("\n");

							}
					}
					break;
				default: break;
			}
		}
	}
	rtc_unsubscribe_int();

	sys_outb(RTC_ADDR_REG, 0);
	sys_inb(RTC_DATA_REG, &segundo);

	sys_outb(RTC_ADDR_REG, 2);
	sys_inb(RTC_DATA_REG, &minuto);

	sys_outb(RTC_ADDR_REG, 4);
	sys_inb(RTC_DATA_REG, &hora);

	sys_outb(RTC_ADDR_REG, 7);
	sys_inb(RTC_DATA_REG, &dia);

	sys_outb(RTC_ADDR_REG, 8);
	sys_inb(RTC_DATA_REG, &mes);

	sys_outb(RTC_ADDR_REG, 9);
	sys_inb(RTC_DATA_REG, &ano);




	printf("Hora: %x : %x : %x \n", hora, minuto, segundo);
	printf("Data: %x - %x - %x \n", dia, mes, ano);



	disable();
	return 0;
}

int test_int(){
	//implementar aula
	return 0;
}
