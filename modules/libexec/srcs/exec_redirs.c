/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:40:48 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 18:34:43 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "heredoc.h"
#include "msgdef.h"
#include "executor_internal.h"

int	exec_redir_in(t_exec_redir *redir_arr)
{
	int	fd;

	if (access(redir_arr->content, F_OK) != 0)
	{
		ft_dprintf(2, "%s%s: No such file or directory\n",
			MSG_ERROR_PREFIX, redir_arr->content);
		return (CODE_ERROR_IO);
	}
	if (access(redir_arr->content, R_OK) != 0)
	{
		ft_dprintf(2, "%s%s: Permission denied\n",
			MSG_ERROR_PREFIX, redir_arr->content);
		return (CODE_ERROR_IO);
	}
	fd = open(redir_arr->content, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	exec_redir_out(t_exec_redir *redir_arr)
{
	int	fd;

	fd = open(redir_arr->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	exec_redir_in_here(t_exec_redir *redir_arr)
{
	int		fd;
	char	*heredoc_file;

	(void)redir_arr;
	if (heredoc_get_next_filename(&heredoc_file) != CODE_OK)
		return (CODE_ERROR_IO);
	fd = open(heredoc_file, O_RDONLY);
	free(heredoc_file);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	exec_redir_out_append(t_exec_redir *redir_arr)
{
	int	fd;

	fd = open(redir_arr->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	_exec_redirs(t_list *redirs)
{
	int	stat;
	int	type;

	while (redirs)
	{
		type = ((t_exec_redir *)redirs->content)->type;
		if (type == REDIR_IN)
			stat = exec_redir_in(redirs->content);
		else if (type == REDIR_OUT)
			stat = exec_redir_out(redirs->content);
		else if (type == REDIR_IN_HERE)
			stat = exec_redir_in_here(redirs->content);
		else if (type == REDIR_OUT_APPEND)
			stat = exec_redir_out_append(redirs->content);
		else
			stat = CODE_ERROR_SCOPE;
		if (stat)
			return (stat);
		redirs = redirs->next;
	}
	return (CODE_OK);
}
