/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:21:58 by ijacquet          #+#    #+#             */
/*   Updated: 2019/10/16 13:31:33 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	char	*desti;

	desti = dest;
	while (*desti != '\0')
		desti++;
	while (*src != '\0')
	{
		*desti = *src;
		src++;
		desti++;
	}
	*desti = '\0';
	return (dest);
}
