#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("prompt: ");
		if (str)
			printf("str: %s\n", str);
		else
			break ;
	}
	return (0);
}
