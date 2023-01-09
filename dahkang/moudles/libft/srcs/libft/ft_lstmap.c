/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahkang <dahkang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:46:25 by dahkang           #+#    #+#             */
/*   Updated: 2022/07/31 17:15:41 by dahkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*free_alloc(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*curr;

	curr = *lst;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		ft_lstdelone(tmp, del);
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	void	*ptr;

	if (!lst || !f)
		return (0);
	new_list = 0;
	while (lst)
	{
		ptr = f(lst->content);
		node = ft_lstnew(ptr);
		if (!node)
		{
			free(ptr);
			return (free_alloc(&new_list, del));
		}
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}
