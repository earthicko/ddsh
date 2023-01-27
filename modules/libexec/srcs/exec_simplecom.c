#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "envmanager.h"
#include "builtin_commands.h"
#include "t_node.h"
#include "strutils.h"
#include "msgdef.h"
#include "executor_internal.h"

int	exec_simplecom_assort_elem(t_node *simplecom, int n_elem, t_pchararr *argarr)
{
	int		i;
	t_node	*elem;

	i = 0;
	while (i < n_elem)
	{
		elem = node_get_nthchild(simplecom, i);
		if (node_get_nthchild(elem, 0)->type == NODETYPE_CMD_WORD
			&& pchararr_append(argarr, node_get_nthchild(elem, 0)->content))
		{
			ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
			return (CODE_ERROR_MALLOC);
		}
		else if (node_get_nthchild(elem, 0)->type == NODETYPE_IO_REDIRECT
			&& exec_io_redir(node_get_nthchild(elem, 0)))
			return (CODE_ERROR_IO);
		i++;
	}
	return (CODE_OK);
}

static int	exec_simplecom_abort(t_pchararr *argarr, int stat)
{
	pchararr_destroy(argarr);
	return (stat);
}

static int	exec_simplecom_init(t_node *simplecom, char ***argv_buf)
{
	int			stat;
	t_pchararr	*argarr;
	int			n_elem;

	argarr = pchararr_create();
	if (!argarr)
	{
		ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
		return (CODE_ERROR_MALLOC);
	}
	n_elem = ft_lstsize(simplecom->childs);
	stat = exec_simplecom_assort_elem(simplecom, n_elem, argarr);
	if (stat)
		return (exec_simplecom_abort(argarr, stat));
	stat = pchararr_to_strarr(argarr, argv_buf);
	return (exec_simplecom_abort(argarr, stat));
}

static void	exec_simplecom_prepare_extern(char **argv, char ***envp_buf)
{
	int			_stat;
	struct stat	s_statbuf;

	_stat = find_exec(&argv[0]);
	if (_stat == CODE_ERROR_MALLOC)
		exit(EXIT_FAILURE);
	if (_stat == CODE_ERROR_GENERIC)
		exit(127);
	if (envman_setval("_", argv[0], TRUE) || envman_getenvp(envp_buf))
		exit(EXIT_FAILURE);
	if (stat(argv[0], &s_statbuf) != 0)
		exit(EXIT_FAILURE);
	if (S_ISDIR(s_statbuf.st_mode))
	{
		ft_dprintf(2, "%s%s: is a directory\n", MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
	if (access(argv[0], X_OK) != 0)
	{
		ft_dprintf(2, "%s%s: Permission denied\n", MSG_ERROR_PREFIX, argv[0]);
		exit(126);
	}
}

static int	exec_simplecom_fork_extern(char **argv)
{
	pid_t	pid;
	char	**envp;
	int		_stat;

	pid = fork();
	if (pid < 0)
	{
		ft_dprintf(2, "%sfailed to fork.\n", MSG_ERROR_PREFIX);
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		exec_simplecom_prepare_extern(argv, &envp);
		execve(argv[0], argv, envp);
	}
	wait4(pid, &_stat, 0, NULL);
	if (WIFSIGNALED(_stat))
		return (WTERMSIG(_stat) + 128);
	else
		return (WEXITSTATUS(_stat));
}

int	exec_simplecom(t_node *simplecom)
{
	char	**argv;
	int		_stat;

	if (exec_simplecom_init(simplecom, &argv))
		return (EXIT_FAILURE);
	if (argv[0] == NULL)
	{
		ft_free_strarr(argv);
		return (EXIT_SUCCESS);
	}
	if (builtin_getindex(argv[0]) >= 0)
	{
		_stat = builtin_exec_by_name(argv[0], argv);
		ft_free_strarr(argv);
		return (_stat);
	}
	_stat = exec_simplecom_fork_extern(argv);
	ft_free_strarr(argv);
	return (_stat);
}
