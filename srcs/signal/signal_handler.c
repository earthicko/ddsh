#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"

void	_sighandler_int_interactive(int signo)
{
	ft_printf("%s: got SIGINT(%d)\n", __func__, signo);
	rl_replace_line("", TRUE);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	_sighandler_int_heredoc(int signo)
{
	ft_printf("%s: got SIGINT(%d)\n", __func__, signo);
	exit(0);
	return ;
}
