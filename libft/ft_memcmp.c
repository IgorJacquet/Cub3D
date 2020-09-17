/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:48:44 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/28 17:58:30 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ch1;
	unsigned char	*ch2;

	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	if (!s1 && !s2)
		return (0);
	while (n)
	{
		if (*ch1 != *ch2)
			return (*ch1 - *ch2);
		ch1++;
		ch2++;
		n--;
	}
	return (0);
}
