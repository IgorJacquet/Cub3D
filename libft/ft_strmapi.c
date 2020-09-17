/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:07:43 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/21 12:32:24 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rep;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(rep = (char *)malloc(sizeof(*rep) * ft_strlen((char *)s) + 1)))
		return (NULL);
	while (s[i])
	{
		rep[i] = f(i, s[i]);
		i++;
	}
	rep[i] = '\0';
	return (rep);
}
