#include <signal.h>
#include "libft.h"

typedef struct sigaction	t_sigact;

void	_sighandler_int_interactive(int signo);
void	_sighandler_int_heredoc(int signo);

int	signal_set_state_default(void)
{
	int			stat;
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
	stat = 0;
	stat |= sigaction(SIGTERM, &action_term, NULL);
	stat |= sigaction(SIGQUIT, &action_quit, NULL);
	stat |= sigaction(SIGINT, &action_int, NULL);
	return (stat);
}

int	signal_set_state_interactive(void)
{
	int			stat;
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
	stat = 0;
	stat |= sigaction(SIGTERM, &action_term, NULL);
	stat |= sigaction(SIGQUIT, &action_quit, NULL);
	stat |= sigaction(SIGINT, &action_int, NULL);
	return (stat);
}

int	signal_set_state_heredoc(void)
{
	int			stat;
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
	stat = 0;
	stat |= sigaction(SIGTERM, &action_term, NULL);
	stat |= sigaction(SIGQUIT, &action_quit, NULL);
	stat |= sigaction(SIGINT, &action_int, NULL);
	return (stat);
}

int	signal_set_state_executing(void)
{
	int			stat;
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
	stat = 0;
	stat |= sigaction(SIGTERM, &action_term, NULL);
	stat |= sigaction(SIGQUIT, &action_quit, NULL);
	stat |= sigaction(SIGINT, &action_int, NULL);
	return (stat);
}
