#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"

typedef	struct sigaction	t_sigact;

static void	_sighandler_int_interactive(int signo)
{
	ft_printf("%s: got SIGINT(%d)\n", __func__, signo);
	rl_replace_line("", TRUE);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

static void	_sighandler_int_heredoc(int signo)
{
	ft_printf("%s: got SIGINT(%d)\n", __func__, signo);
	exit(0);
	return ;
}

int	signal_set_state_default(void)
{
	t_sigact	action_term;
	t_sigact	action_quit;
	t_sigact	action_int;

	action_term.sa_handler = SIG_DFL;
	action_quit.sa_handler = SIG_DFL;
	action_int.sa_handler = SIG_DFL;
	sigemptyset(&(action_term.sa_mask));
	sigemptyset(&(action_quit.sa_mask));
	sigemptyset(&(action_int.sa_mask));
	action_term.sa_flags = 0;
	action_quit.sa_flags = 0;
	action_int.sa_flags = 0;
	// TODO: 예외 처리
	sigaction(SIGTERM, &action_term, NULL);
	sigaction(SIGQUIT, &action_quit, NULL);
	sigaction(SIGINT, &action_int, NULL);
	return (CODE_OK);
}

int	signal_set_state_interactive(void)
{
	t_sigact	action_term;
	t_sigact	action_quit;
	t_sigact	action_int;

	action_term.sa_handler = SIG_IGN;
	action_quit.sa_handler = SIG_IGN;
	action_int.sa_handler = _sighandler_int_interactive;
	sigemptyset(&(action_term.sa_mask));
	sigemptyset(&(action_quit.sa_mask));
	sigemptyset(&(action_int.sa_mask));
	action_term.sa_flags = 0;
	action_quit.sa_flags = 0;
	action_int.sa_flags = 0;
	// TODO: 예외 처리
	sigaction(SIGTERM, &action_term, NULL);
	sigaction(SIGQUIT, &action_quit, NULL);
	sigaction(SIGINT, &action_int, NULL);
	return (CODE_OK);
}

int	signal_set_state_heredoc(void)
{
	t_sigact	action_term;
	t_sigact	action_quit;
	t_sigact	action_int;

	action_term.sa_handler = SIG_IGN;
	action_quit.sa_handler = SIG_IGN;
	action_int.sa_handler = _sighandler_int_heredoc;
	sigemptyset(&(action_term.sa_mask));
	sigemptyset(&(action_quit.sa_mask));
	sigemptyset(&(action_int.sa_mask));
	action_term.sa_flags = 0;
	action_quit.sa_flags = 0;
	action_int.sa_flags = 0;
	// TODO: 예외 처리
	sigaction(SIGTERM, &action_term, NULL);
	sigaction(SIGQUIT, &action_quit, NULL);
	sigaction(SIGINT, &action_int, NULL);
	return (CODE_OK);
}

int	signal_set_state_executing(void)
{
	t_sigact	action_term;
	t_sigact	action_quit;
	t_sigact	action_int;

	action_term.sa_handler = SIG_IGN;
	action_quit.sa_handler = SIG_IGN;
	action_int.sa_handler = SIG_IGN;
	sigemptyset(&(action_term.sa_mask));
	sigemptyset(&(action_quit.sa_mask));
	sigemptyset(&(action_int.sa_mask));
	action_term.sa_flags = 0;
	action_quit.sa_flags = 0;
	action_int.sa_flags = 0;
	// TODO: 예외 처리
	sigaction(SIGTERM, &action_term, NULL);
	sigaction(SIGQUIT, &action_quit, NULL);
	sigaction(SIGINT, &action_int, NULL);
	return (CODE_OK);
}
