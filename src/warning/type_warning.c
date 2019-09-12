/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_warning.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 18:34:56 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 18:34:57 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/warning.h"

void	warning_rgb_field_type(int warning_code)
{
	if (warning_code == WARNING_RGB_TYPE_UNSUPPORTED)
	{
		ft_putstr("Unsupported format for RGB color field type.\n");
	}
	if (warning_code == WARNING_RGB_VALUE)
	{
		ft_putstr("Unsupported value. Color sholud be \
numerical value from 0 to 255.\n\tDefalut value will be used.\n");
	}
}

void	warning_rotation_field_type(int warning_code)
{
	if (warning_code == WARNING_ROTATION_UNSUPPORTED)
	{
		ft_putstr("Unsupported format for rotation field type.\n");
	}
	if (warning_code == WARNING_ROTATION_VALUE)
	{
		ft_putstr("Unsupported value. Rotation sholud be numerical \
value from -360 to 360.\n\tDefalut value will be used.\n");
	}
}

void	warning_transparency_field_type(int warning_code)
{
	if (warning_code == WARNING_TRANSPARENCY_VALUE)
	{
		ft_putstr("Unsupported value. Transparency sholud\
be numerical value from 0 to 100.\n\tDefalut value will be used.\n");
	}
}

void	warning_mirror_field_type(int warning_code)
{
	if (warning_code == WARNING_MIRROR_VALUE)
	{
		ft_putstr("Unsupported value. Mirror sholud\
be numerical value from 0 to 100.\n\tDefalut value will be used.\n");
	}
}
