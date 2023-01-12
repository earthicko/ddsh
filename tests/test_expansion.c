#include <stdio.h>
#include "envmanager.h"

int	main(void)
{
	char	*word;

	word = "$HOME";
	printf("before: %s\n", word);
	printf("exit status %d\n", envmanager_expand(&word));
	printf("after: %s\n", word);
	return (0);
}
