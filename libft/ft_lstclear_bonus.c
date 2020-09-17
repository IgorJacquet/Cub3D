/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:44:44 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/24 13:46:11 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*ptr2;

	if (!lst || !*lst || !del)
		return ;
	ptr = *lst;
	while (ptr)
	{
		ptr2 = ptr->next;
		ft_lstdelone(ptr, del);
		ptr = ptr2;
	}
	*lst = NULL;
}
