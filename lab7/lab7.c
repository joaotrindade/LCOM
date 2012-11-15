#define COM1 0x3F8
#define COM2 0x2F8

int main(int argc, char **argv) {
	sef_startup();
	test_conf(COM1);

	return 0;
}
