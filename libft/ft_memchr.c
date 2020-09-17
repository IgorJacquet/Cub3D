/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:52:19 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/29 11:52:24 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	p;

	p = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (n)
	{
		if (*ptr == p)
			return (ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
