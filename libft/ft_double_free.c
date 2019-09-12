/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:21:58 by akulaiev          #+#    #+#             */
/*   Updated: 2019/03/23 14:22:00 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_double_free(void **data, int num_lines)
{
	int		i;

	i = 0;
	if (data)
	{
		while (i < num_lines && data[i])
		{
			free(data[i]);
			i++;
		}
		free(data);
		data = NULL;
	}
}
