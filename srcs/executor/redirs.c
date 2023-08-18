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
#include "t_node.h"
#include "heredoc.h"
#include "msgdef.h"
#include "executor_internal.h"

int	_exec_redir_in(t_node *filename)
{
	int	fd;

	if (access(filename->content, F_OK) != 0)
	{
		ft_dprintf(2, "%s%s: No such file or directory\n",
			MSG_ERROR_PREFIX, filename->content);
		return (CODE_ERROR_IO);
	}
	if (access(filename->content, R_OK) != 0)
	{
		ft_dprintf(2, "%s%s: Permission denied\n",
			MSG_ERROR_PREFIX, filename->content);
		return (CODE_ERROR_IO);
	}
	fd = open(filename->content, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	_exec_redir_out(t_node *filename, int flag)
{
	int	fd;

	fd = open(filename->content, flag, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	_exec_io_file(t_node *io_file)
{
	t_node	*io_op_file;
	t_node	*filename;

	io_op_file = node_get_nthchild(io_file, 0);
	filename = node_get_nthchild(io_file, 1);
	if (ft_strncmp(io_op_file->content, ">>", 2) == 0)
		return (_exec_redir_out(filename, O_WRONLY | O_CREAT | O_APPEND));
	else if (ft_strncmp(io_op_file->content, "<", 1) == 0)
		return (_exec_redir_in(filename));
	else if (ft_strncmp(io_op_file->content, ">", 1) == 0)
		return (_exec_redir_out(filename, O_WRONLY | O_CREAT | O_TRUNC));
	ft_dprintf(2, "%scritical: corrupted tree\n", MSG_ERROR_PREFIX);
	return (CODE_ERROR_DATA);
}

int	_exec_io_here(void)
{
	int		fd;
	char	*heredoc_file;

	if (heredoc_get_next_filename(&heredoc_file) != CODE_OK)
		return (CODE_ERROR_IO);
	fd = open(heredoc_file, O_RDONLY);
	free(heredoc_file);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	_exec_io_redir(t_node *io_redir)
{
	if (node_get_nthchild(io_redir, 0)->type == NODETYPE_IO_HERE)
		return (_exec_io_here());
	if (node_get_nthchild(io_redir, 0)->type == NODETYPE_IO_FILE)
		return (_exec_io_file(node_get_nthchild(io_redir, 0)));
	ft_dprintf(2, "%scritical: corrupted tree\n", MSG_ERROR_PREFIX);
	return (CODE_ERROR_DATA);
}
