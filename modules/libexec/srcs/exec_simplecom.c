/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:19:17 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/27 16:19:18 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "builtin_commands.h"
#include "t_node.h"
#include "strutils.h"
#include "msgdef.h"
#include "executor_internal.h"

int	_exec_simplecom_fork_extern(char **argv);

int	_exec_simplecom_assort_elems(t_node *simplecom, int n_elem, t_pchararr *args)
{
	int		i;
	t_node	*elem;

	i = 0;
	while (i < n_elem)
	{
		elem = node_get_nthchild(simplecom, i);
		if (node_get_nthchild(elem, 0)->type == NODETYPE_CMD_WORD
			&& pchararr_append(args, node_get_nthchild(elem, 0)->content))
		{
			ft_print_error(MSG_ERROR_PREFIX, CODE_ERROR_MALLOC);
			return (CODE_ERROR_MALLOC);
		}
		else if (node_get_nthchild(elem, 0)->type == NODETYPE_IO_REDIRECT
			&& _exec_io_redir(node_get_nthchild(elem, 0)))
			return (CODE_ERROR_IO);
		i++;
	}
	return (CODE_OK);
}

static int	_exec_simplecom_abort(t_pchararr *argarr, int stat)
{
	pchararr_destroy(argarr);
	return (stat);
}

static int	_exec_simplecom_init(t_node *simplecom, char ***argv_buf)
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
	stat = _exec_simplecom_assort_elems(simplecom, n_elem, argarr);
	if (stat)
		return (_exec_simplecom_abort(argarr, stat));
	stat = pchararr_to_strarr(argarr, argv_buf);
	return (_exec_simplecom_abort(argarr, stat));
}

int	_exec_simplecom(t_node *simplecom)
{
	char	**argv;
	int		_stat;

	if (_exec_simplecom_init(simplecom, &argv))
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
	_stat = _exec_simplecom_fork_extern(argv);
	ft_free_strarr(argv);
	return (_stat);
}
