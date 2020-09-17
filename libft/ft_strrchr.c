/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:38:55 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/15 18:41:47 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	char	*ptr;

	ptr = 0;
	while (*str != '\0')
	{
		if (*str == c)
			ptr = (char *)str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (ptr);
}
