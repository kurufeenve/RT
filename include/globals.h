/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 20:34:38 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/02 20:34:39 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

# include "parsing.h"

char				*g_params[16] = {
	"position",
	"direction",
	"colorRGB",
	"colorHexadecimal",
	"intensity",
	"radius",
	"transparency",
	"height",
	"rotation",
	"mirror",
	"refraction",
	"cone_angle",
	"position2",
	"shininess",
	"type",
	"texture"
};

void				(*g_set_params[16])(t_tags param_tag,
t_obj_wrapper *object) = {
	&set_position,
	&set_normale,
	&set_color_rgb,
	&set_color_hex,
	&set_intensity,
	&set_radius,
	&set_transparency,
	&set_height,
	&set_rotation,
	&set_mirror,
	&set_refraction,
	&set_cone_angle,
	&set_position2,
	&set_shininess,
	&set_ligth_type,
	&set_texture
};

#endif
