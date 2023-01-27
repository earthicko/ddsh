/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:43:47 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 20:00:57 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "envmanager.h"
#include "msgdef.h"
#include "prompt.h"

void	rl_replace_line(const char *str, int clear_undo);

void	_sighandler_int_interactive(int signo)
{
	char	*prefix;

	(void)signo;
	prefix = prompt_get_prompt_prefix();
	ft_printf("\n%s\r", prefix);
	free(prefix);
	rl_replace_line("", TRUE);
	rl_on_new_line();
	rl_redisplay();
	exit_stat_manager(1);
	return ;
}

void	_sighandler_int_heredoc(int signo)
{
	(void)signo;
	ft_printf("\n", rl_line_buffer);
	exit(128 + signo);
}
