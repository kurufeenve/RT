/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mirror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:53:51 by vordynsk          #+#    #+#             */
/*   Updated: 2019/03/14 16:53:54 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/warning.h"

int			check_mirror(char *value, char *param_name)
{
	int		mirror;

	mirror = ft_atoi(value);
	if (!is_numeric(value))
	{
		not_numeric_warning(value, param_name);
		return (FALSE);
	}
	if (mirror < 0 || mirror > 100)
	{
		set_warning_message("mirror value out of range: '");
		set_warning_message(value);
		set_warning_message("'.\n");
		warning(WARNING_MIRROR_VALUE);
		return (FALSE);
	}
	return (TRUE);
}

void		manage_normales(double *x, double *y, double *z)
{
	*x = (*x == 0 || *x == 1 || *x == -1) ? *x : 1;
	*y = (*y == 0 || *y == 1 || *y == -1) ? *y : 1;
	*z = (*z == 0 || *z == 1 || *z == -1) && (*x != 0 || *y != 0) ? *z : 1;
	*x = *y != 0 || *z != 0 ? 0 : *x;
	*y = *z != 0 ? 0 : *y;
}

int			check_coord_rel(char *param_name)
{
	if (!ft_strcmp(param_name, "position") ||
		!ft_strcmp(param_name, "direction") ||
		!ft_strcmp(param_name, "position2"))
	{
		set_warning_message(param_name);
		set_warning_message(" should have coordinte x, y or z");
		warning(NO_WARNINGS);
		return (FALSE);
	}
	return (TRUE);
}

int			empty(char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		if (ft_isprint(src[i]) && src[i] != 32)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void		close_warning(char *tag_name)
{
	warning_tag_not_closed(tag_name);
	warning(TAG_NOT_CLOSED);
}
