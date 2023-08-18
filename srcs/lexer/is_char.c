/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:52 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

int	_is_space(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n')
		return (TRUE);
	else
		return (FALSE);
}

int	_is_quote(char ch)
{
	if (ch == '\'' || ch == '\"')
		return (TRUE);
	else
		return (FALSE);
}

int	_is_metachar(char ch)
{
	if (ch == '<' || ch == '>' || ch == '|')
		return (TRUE);
	else
		return (FALSE);
}
