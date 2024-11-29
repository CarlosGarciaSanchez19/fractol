/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:01:04 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/26 12:54:40 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxtnode;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		nxtnode = (*lst)->next;
		del((*lst)->content);
		del(*lst);
		*lst = nxtnode;
	}
}
