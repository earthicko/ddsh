/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:45:21 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:45:24 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_valid_name(char *str)
{
	if (!str || ft_strlen(str) == 0 || ft_isdigit(str[0]))
		return (FALSE);
	while (*str)
	{
		if (!(*str == '_' || ft_isalnum(*str)))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
