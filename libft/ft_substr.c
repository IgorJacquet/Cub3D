/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:06:36 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/30 11:25:38 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char *ret;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		if (!(ret = (char *)malloc(sizeof(char))))
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	return (ft_strndup(&s[start], len));
}
