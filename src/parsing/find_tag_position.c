/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tag_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:10:15 by dkliukin          #+#    #+#             */
/*   Updated: 2018/12/05 17:10:17 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int			find_tag_position(char *scene, char **to_find, int start_from)
{
	char	*current_ptr;
	char	*start_ptr;
	char	*occure_ptr;
	int		i;

	start_ptr = &scene[start_from];
	current_ptr = start_ptr;
	while (*current_ptr != '\0')
	{
		occure_ptr = current_ptr;
		if (*current_ptr == (*to_find)[0])
		{
			i = 0;
			while (*current_ptr == (*to_find)[i])
			{
				i++;
				if ((*to_find)[i] == '\0')
					return (start_from + (occure_ptr - start_ptr));
				current_ptr++;
			}
		}
		current_ptr++;
	}
	return (-1);
}
