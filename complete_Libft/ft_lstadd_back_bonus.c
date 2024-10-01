/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:55:59 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/03 15:43:43 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*helper;

	if (*lst == NULL)
		*lst = new;
	else
	{
		helper = *lst;
		while (helper->next != NULL)
			helper = helper->next;
		helper->next = new;
	}
}
