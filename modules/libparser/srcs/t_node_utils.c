/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:41:02 by donghyle          #+#    #+#             */
/*   Updated: 2023/01/22 16:41:07 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"
#include "libft_def.h"
#include "t_node.h"

t_node	*_get_nth_child(t_node *root, int n)
{
	t_list	*cursor;

	if (n < 0)
		return (NULL);
	cursor = root->childs;
	while (cursor && n > 0)
	{
		cursor = cursor->next;
		n--;
	}
	if (!cursor)
		return (NULL);
	return (cursor->content);
}
