/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:59:37 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/05 17:15:31 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*store;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		store = f(lst->content);
		new = ft_lstnew(store);
		if (!new)
		{
			del(store);
			ft_lstclear(&head, (*del));
			return (head);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
