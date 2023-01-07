#include <stdio.h>

int	main(void)
{
	void	*ptr;
	int		num;

	num = 10;
	ptr = num;
	printf("num: %d\n", (int)ptr);
	return (0);
}
