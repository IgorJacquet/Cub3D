/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeturn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:25:15 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/28 17:24:28 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_freeturn(char **data, int value)
{
	if (data)
	{
		free(*data);
		*data = NULL;
	}
	return (value);
}
