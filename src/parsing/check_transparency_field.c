/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_transparency_field.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:59:44 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 20:59:45 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/warning.h"

int			check_transparency(char *value, char *param_name)
{
	int		transparency;

	transparency = ft_atoi(value);
	if (!is_numeric(value))
	{
		not_numeric_warning(value, param_name);
		return (FALSE);
	}
	if (transparency < 0 || transparency > 100)
	{
		set_warning_message("Transparency value out of range: '");
		set_warning_message(value);
		set_warning_message("'.\n");
		warning(WARNING_TRANSPARENCY_VALUE);
		return (FALSE);
	}
	return (TRUE);
}
