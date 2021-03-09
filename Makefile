/tmp/a.out: main.c
	gcc -o $@ $< -lsystemd
