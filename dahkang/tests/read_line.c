#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("prompt: ");
		printf("str: %s\n", str);
	}
	return (0);
}
