/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 02:09:53 by earth             #+#    #+#             */
/*   Updated: 2023/01/27 02:09:53 by earth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	exec_lstadd(t_list **lst, void *exec)
{
	t_list	*node;

	node = ft_lstnew(exec);
	if (!node)
		return (CODE_ERROR_MALLOC);
	ft_lstadd_back(lst, node);
	return (CODE_OK);
}

void	*get_nth_exec(t_list *lst, int n)
{
	if (n < 0)
		return (NULL);
	while (lst && n > 0)
	{
		lst = lst->next;
		n--;
	}
	if (!lst)
		return (NULL);
	return (lst->content);
}
