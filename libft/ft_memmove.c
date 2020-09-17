/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:15:06 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/15 13:45:42 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*srce;

	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	if (dest == srce)
		return (dst);
	if (dest < srce)
		while (len--)
			*dest++ = *srce++;
	else
	{
		srce = (unsigned char*)src + len - 1;
		dest = dst + len - 1;
		while (len--)
			*dest-- = *srce--;
	}
	return (dst);
}
