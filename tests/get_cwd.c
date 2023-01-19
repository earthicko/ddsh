#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char	*home_dir;

	home_dir = getcwd(NULL, 0);
	printf("home_dir: %s\n", home_dir);
}
