/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:46:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:46:28 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "envmanager.h"

int	_do_tilde_expansion(char **buf)
{
	char	*without_tilde;
	char	*tilde_replacement;
	char	*temp;

	if (!(ft_strncmp(*buf, "~", 2) == 0 || ft_strncmp(*buf, "~/", 2) == 0))
		return (CODE_OK);
	if (envman_getval("HOME", &tilde_replacement))
		return (CODE_OK);
	without_tilde = ft_substr(*buf, 1, ft_strlen(*buf) - 1);
	if (!without_tilde)
	{
		free(tilde_replacement);
		return (CODE_ERROR_MALLOC);
	}
	temp = ft_strjoin(tilde_replacement, without_tilde);
	free(tilde_replacement);
	free(without_tilde);
	if (!temp)
		return (CODE_ERROR_MALLOC);
	free(*buf);
	*buf = temp;
	return (CODE_OK);
}
