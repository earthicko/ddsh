#ifndef SIGHANDLER_H
# define SIGHANDLER_H

int	signal_set_state_default(void);
int	signal_set_state_interactive(void);
int	signal_set_state_heredoc(void);
int	signal_set_state_executing(void);

#endif
