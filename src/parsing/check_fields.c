/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:51:35 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 20:51:36 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/warning.h"

int				check_type(char *value)
{
	int			point;
	int			ambient;

	point = ft_strcmp(value, "point");
	ambient = ft_strcmp(value, "ambient");
	if ((point != 0 && ambient != 0))
	{
		set_warning_message("Unrecognized type of light '");
		set_warning_message(value);
		set_warning_message("' please check your input.\n");
		set_warning_message("Default value 'point' will be used for type.");
		warning(NO_WARNINGS);
		return (FALSE);
	}
	return (TRUE);
}

static int		general_check_field(char *value, char *param_name)
{
	if (is_numeric(value))
		return (TRUE);
	else
	{
		not_numeric_warning(value, param_name);
		return (FALSE);
	}
}

int				check_value(char *value, char *param_name)
{
	if (!ft_strcmp(param_name, "rotation") ||
		!ft_strcmp(param_name, "colorRGB") ||
		!ft_strcmp(param_name, "colorHexadecimal") ||
		!ft_strcmp(param_name, "type") || !ft_strcmp(param_name, "texture") ||
	!ft_strcmp(param_name, "transparency"))
	{
		if (!ft_strcmp(param_name, "type"))
			return (check_type(value));
		if (!ft_strcmp(param_name, "colorRGB"))
			return (check_rgb_color(value, param_name));
		if (!ft_strcmp(param_name, "colorHexadecimal"))
			return (check_hexadecimal_color(value));
		if (!ft_strcmp(param_name, "rotation"))
			return (check_rotation(value, param_name));
		if (!ft_strcmp(param_name, "transparency"))
			return (check_transparency(value, param_name));
		if (!ft_strcmp(param_name, "texture"))
			return (TRUE);
		return (TRUE);
	}
	else
		return (general_check_field(value, param_name));
	return (FALSE);
}
