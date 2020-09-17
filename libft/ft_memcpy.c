/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:21:22 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/28 15:52:42 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char *)dest;
	temp2 = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (n--)
	{
		*temp1 = *temp2;
		temp1++;
		temp2++;
	}
	return (dest);
}
