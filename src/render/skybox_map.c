/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:21:52 by akulaiev          #+#    #+#             */
/*   Updated: 2019/03/23 16:21:54 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		name_tex(t_sdl *sdl_data, char *s_num)
{
	int		i;

	i = -1;
	sdl_data->sky.tex_num = 6;
	sdl_data->sky.t_n = (char**)malloc(sizeof(char*) *
	sdl_data->sky.tex_num);
	while (++i < sdl_data->sky.tex_num)
	{
		sdl_data->sky.t_n[i] = (char*)malloc(100);
		sdl_data->sky.t_n[i] = ft_strcpy(sdl_data->sky.t_n[i],
		"./skyboxes/skybox");
		sdl_data->sky.t_n[i] = ft_strcat(sdl_data->sky.t_n[i], s_num);
	}
	free(s_num);
	sdl_data->sky.t_n[0] = ft_strcat(sdl_data->sky.t_n[0], "/right.bmp");
	sdl_data->sky.t_n[1] = ft_strcat(sdl_data->sky.t_n[1], "/left.bmp");
	sdl_data->sky.t_n[2] = ft_strcat(sdl_data->sky.t_n[2], "/top.bmp");
	sdl_data->sky.t_n[3] = ft_strcat(sdl_data->sky.t_n[3], "/bottom.bmp");
	sdl_data->sky.t_n[4] = ft_strcat(sdl_data->sky.t_n[4], "/front.bmp");
	sdl_data->sky.t_n[5] = ft_strcat(sdl_data->sky.t_n[5], "/back.bmp");
}

t_color			*tex_transform(SDL_Surface *tex, t_iterators i)
{
	unsigned int	*int_pix;
	unsigned char	*char_pix;
	t_color			*ret_tex;

	ret_tex = (t_color*)malloc(sizeof(t_color) * tex->w * tex->h);
	i.i = -1;
	if (tex->format->BytesPerPixel == 3)
	{
		i.j = 0;
		char_pix = tex->pixels;
		while (i.j < tex->w * tex->h * 3 && ++i.i < tex->w * tex->h)
		{
			ret_tex[i.i].rgb.r = char_pix[i.j];
			ret_tex[i.i].rgb.g = char_pix[i.j + 1];
			ret_tex[i.i].rgb.b = char_pix[i.j + 2];
			i.j += 3;
		}
	}
	else if (tex->format->BytesPerPixel == 4)
	{
		int_pix = tex->pixels;
		while (++i.i < tex->w * tex->h)
			ret_tex[i.i].color = int_pix[i.i];
	}
	return (ret_tex);
}

int				tex_gen(t_scene *scene, t_sdl *sdl_data)
{
	t_iterators		i;

	if (scene->sky_num > 0 && scene->sky_num < 6)
		name_tex(sdl_data, ft_itoa(scene->sky_num));
	else
		return (0);
	i.i = -1;
	sdl_data->sky.sky_tex = (SDL_Surface**)malloc(sizeof(SDL_Surface*) *
	sdl_data->sky.tex_num);
	sdl_data->sky.sky_tex_3 = (t_color**)malloc(sizeof(t_color*) *
	sdl_data->sky.tex_num);
	while (++i.i < sdl_data->sky.tex_num)
	{
		sdl_data->sky.sky_tex[i.i] = SDL_LoadBMP(sdl_data->sky.t_n[i.i]);
		sdl_data->sky.sky_tex_3[i.i] =
		tex_transform(sdl_data->sky.sky_tex[i.i], i);
		if (!sdl_data->sky.sky_tex[i.i] || !sdl_data->sky.sky_tex_3[i.i])
		{
			ft_double_free((void**)sdl_data->sky.t_n, i.i);
			return (0);
		}
	}
	return (1);
}

static void		skybox_map_help(t_smap *s, double x, double y, double z)
{
	s->az = fabs(z);
	if (y > 0 && s->ay >= s->ax && s->ay >= s->az && (s->ma = s->ay))
	{
		s->nt = 2;
		s->x_cube = x;
		s->y_cube = z;
	}
	else if (y <= 0 && s->ay >= s->ax && s->ay >= s->az && (s->ma = s->ay))
	{
		s->nt = 3;
		s->x_cube = -x;
		s->y_cube = z;
	}
	else if (z <= 0 && s->az >= s->ax && s->az >= s->ay && (s->ma = s->az))
	{
		s->nt = 4;
		s->x_cube = -x;
		s->y_cube = -y;
	}
	else if (z > 0 && s->az >= s->ax && s->az >= s->ay && (s->ma = s->az))
	{
		s->nt = 5;
		s->x_cube = x;
		s->y_cube = -y;
	}
}

int				skybox_map(t_sdl *sdl, double x, double y, double z)
{
	t_smap		s;

	s.ax = fabs(x);
	s.ay = fabs(y);
	if (x > 0 && s.ax >= s.ay && s.ax >= fabs(z) && (s.ma = s.ax))
	{
		s.nt = 0;
		s.x_cube = -z;
		s.y_cube = -y;
	}
	else if (x <= 0 && s.ax >= s.ay && s.ax >= fabs(z) && (s.ma = s.ax))
	{
		s.nt = 1;
		s.x_cube = z;
		s.y_cube = -y;
	}
	else
		skybox_map_help(&s, x, y, z);
	s.x_tex = 0.5 * (s.x_cube / s.ma + 1.0);
	s.y_tex = 0.5 * (s.y_cube / s.ma + 1.0);
	s.x_pix = s.x_tex * sdl->sky.sky_tex[s.nt]->w;
	s.y_pix = s.y_tex * sdl->sky.sky_tex[s.nt]->h;
	s.np = fmin(sdl->sky.sky_tex[s.nt]->w * sdl->sky.sky_tex[s.nt]->h
	- 1, s.x_pix + s.y_pix * sdl->sky.sky_tex[s.nt]->w);
	return (sdl->sky.sky_tex_3[s.nt][s.np].color);
}
