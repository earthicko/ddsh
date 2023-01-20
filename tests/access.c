#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	printf("access to reg file ret: %d\n", access("./a.out", X_OK));
	printf("access to dir: %d\n", access("./tmp", X_OK));
}
