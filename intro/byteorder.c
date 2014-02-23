#include <stdio.h>

int
main(int argc, char **argv)
{
	union {
	  short  s;
      char   c[sizeof(short)];
    } un;

	un.s = 0x0102;
    printf("un.s is %d.\n", un.s);
	/* printf("%s: ", CPU_VENDOR_OS); */
	if (sizeof(short) == 2) {
		if (un.c[0] == 1 && un.c[1] == 2)
			printf("big-endian\n");
		else if (un.c[0] == 2 && un.c[1] == 1)
			printf("little-endian\n");
		else
			printf("unknown\n");
	} else
      /* printf("sizeof(short) = %d\n", sizeof(short)); */
      printf("sizeof(short) = %zu\n", sizeof(short));

	return 0;
}
