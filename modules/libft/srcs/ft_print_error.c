/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:14:25 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:48 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_error(char *prefix, int code)
{
	char	*msg[6];

	if (code >= CODE_OK || CODE_ERROR_DATA > code)
		return ;
	msg[-CODE_ERROR_GENERIC] = "%s: Unknown error.\n";
	msg[-CODE_ERROR_IO] = "%s: I/O Error.\n";
	msg[-CODE_ERROR_MALLOC] = "%s: Cannot allocate memory.\n";
	msg[-CODE_ERROR_SCOPE] = "%s: Value is out of scope.\n";
	msg[-CODE_ERROR_DATA] = "%s: Invalid data.\n";
	ft_dprintf(2, msg[-code], prefix);
}
