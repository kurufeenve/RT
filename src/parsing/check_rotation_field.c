/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rotation_field.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:28:05 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 20:28:06 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"
#include "../../include/parsing.h"

int				warning_handler_rotation(char *rotation, int rotation_num)
{
	int			temp_rot;

	temp_rot = ft_atoi(rotation);
	if (temp_rot < -360 || temp_rot > 360 || !is_numeric(rotation))
	{
		set_warning_message("Value for ");
		if (rotation_num == 0)
			set_warning_message("'X-axis'");
		if (rotation_num == 1)
			set_warning_message("'Y-axis'");
		if (rotation_num == 2)
			set_warning_message("'Z-axis'");
		set_warning_message(" \
rotatoin is not numerical or value out of range.\n\
	Value: '");
		set_warning_message(rotation);
		set_warning_message("'.\n");
		warning(WARNING_ROTATION_VALUE);
		return (FALSE);
	}
	return (TRUE);
}

static void		rotation_val_warning(char *value, char *param_name)
{
	set_warning_message("One or more values were missing for '");
	set_warning_message(param_name);
	set_warning_message("'\n\tValues: ");
	set_warning_message(value);
	set_warning_message(".\n");
	warning(WARNING_ROTATION_UNSUPPORTED);
}

int				check_rotation(char *value, char *param_name)
{
	char		**rotation;
	int			is_rotation_rdy;
	int			i;
	int			rotation_len;

	i = 0;
	rotation_len = 0;
	is_rotation_rdy = TRUE;
	rotation = ft_strsplit(value, ',');
	rotation_len = array_length(rotation);
	if (rotation_len != 3)
	{
		rotation_val_warning(value, param_name);
		is_rotation_rdy = FALSE;
	}
	while (i < rotation_len)
	{
		if (warning_handler_rotation(rotation[i], i) == FALSE)
			is_rotation_rdy = FALSE;
		ft_strdel(&rotation[i]);
		i++;
	}
	free(rotation);
	return (is_rotation_rdy);
}
