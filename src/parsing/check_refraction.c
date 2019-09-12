/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_refraction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vordynsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 20:57:31 by vordynsk          #+#    #+#             */
/*   Updated: 2019/03/14 20:57:33 by vordynsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/warning.h"

int			check_refraction(char *value, char *param_name)
{
	int		refraction;

	refraction = ft_atoi(value);
	if (!is_numeric(value))
	{
		not_numeric_warning(value, param_name);
		return (FALSE);
	}
	if (refraction < 0 || refraction > 100)
	{
		set_warning_message("refraction value out of range: '");
		set_warning_message(value);
		set_warning_message("'.\n");
		warning(WARNING_REFRACTION_VALUE);
		return (FALSE);
	}
	return (TRUE);
}
