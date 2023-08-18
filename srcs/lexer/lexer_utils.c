/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:01 by dahkang           #+#    #+#             */
/*   Updated: 2023/01/22 16:41:52 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer_internal.h"

int	_get_n_toks(char *str)
{
	int		n_toks;
	int		tok_type;
	int		word_len;

	n_toks = 0;
	while (*str)
	{
		str += _get_len_space(str);
		tok_type = _get_token_type(str);
		if (tok_type == TOKENTYPE_WORD)
		{
			word_len = _get_word_len(str);
			if (word_len == -1)
				return (-1);
			str += word_len;
		}
		else if (tok_type == TOKENTYPE_NULL)
			continue ;
		else
			str += op_len(str);
		n_toks++;
	}
	return (n_toks);
}

int	_get_word_len(char *str)
{
	int		len;
	char	quote;

	len = 0;
	while (str[len] && !_is_space(str[len]) && !_is_metachar(str[len]))
	{
		if (str[len] == '\'' || str[len] == '"')
		{
			quote = str[len++];
			len += _get_len_inquotes(str + len, quote);
			if (str[len] != quote)
				return (-1);
			quote = 0;
			len++;
		}
		len += _get_len_normal(str + len);
	}
	return (len);
}

int	_get_token_type(char *str)
{
	if (*str == 0)
		return (TOKENTYPE_NULL);
	if (*str == '|')
		return (TOKENTYPE_PIPE);
	else if (*str == '<' && *(str + 1) == '<')
		return (TOKENTYPE_REDIR_IN_HERE);
	else if (*str == '>' && *(str + 1) == '>')
		return (TOKENTYPE_REDIR_OUT_APPEND);
	else if (*str == '<')
		return (TOKENTYPE_REDIR_IN);
	else if (*str == '>')
		return (TOKENTYPE_REDIR_OUT);
	else
		return (TOKENTYPE_WORD);
}

char	*trunc_comments(char *line)
{
	char	*cursor;

	cursor = ft_strchr(line, '#');
	if (!cursor)
		return (ft_strdup(line));
	return (ft_substr(line, 0, cursor - line));
}
