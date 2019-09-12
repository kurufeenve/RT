/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:42:33 by akulaiev          #+#    #+#             */
/*   Updated: 2018/12/05 14:42:35 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H
# include "external.h"

typedef	struct		s_position
{
	double			x;
	double			y;
	double			z;
}					t_position;

typedef	struct		s_rotation
{
	int				rot_x;
	int				rot_y;
	int				rot_z;
}					t_rotation;

typedef struct		s_clr
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_clr;

typedef	union		u_color
{
	int				color;
	t_clr			rgb;
}					t_color;

typedef struct		s_base
{
	t_position		direction_vect;
	t_position		up_vect;
	t_position		right_vect;
}					t_base;

typedef	struct		s_cam
{
	int				exist;
	t_position		origin;
	t_base			basis;
}					t_cam;

typedef struct		s_ray
{
	t_position		direction;
	t_position		origin;
}					t_ray;

typedef struct		s_texture
{
	SDL_Surface		*surf;
	t_color			*texture;
	unsigned		wid;
	unsigned		hei;
	double			u;
	double			v;
	char			*filename;
	int				tex_check;
}					t_texture;

#endif
