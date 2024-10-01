/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:57:58 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/03 20:10:00 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*helper;

	if (!lst)
		return ;
	while (*lst)
	{
		helper = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = helper;
	}
}
