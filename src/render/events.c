/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:30:16 by akulaiev          #+#    #+#             */
/*   Updated: 2018/12/20 14:30:18 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		screenshot(t_scene *scene, t_sdl *sdl_data, t_shot s)
{
	SDL_GetWindowPosition(sdl_data->win_ptr, &s.x, &s.y);
	s.x_c = ft_itoa(s.x);
	s.y_c = ft_itoa(s.y);
	s.w_c = ft_itoa(scene->window_width);
	s.h_c = ft_itoa(scene->window_height);
	s.sh = ft_itoa(sdl_data->shot_num);
	s.command = (char*)malloc(150);
	s.command = ft_strcpy(s.command, "screencapture -R ");
	s.command = ft_strcat(s.command, s.x_c);
	s.command = ft_strcat(s.command, ",");
	s.command = ft_strcat(s.command, s.y_c);
	s.command = ft_strcat(s.command, ",");
	s.command = ft_strcat(s.command, s.w_c);
	s.command = ft_strcat(s.command, ",");
	s.command = ft_strcat(s.command, s.h_c);
	s.command = ft_strcat(s.command, " ./screenshots/test");
	s.command = ft_strcat(s.command, s.sh);
	s.command = ft_strcat(s.command, ".png");
	system(s.command);
	free(s.command);
	free(s.x_c);
	free(s.y_c);
	free(s.w_c);
	free(s.h_c);
	free(s.sh);
}

static void		rotation(t_scene *scene, t_sdl *sdl_data, SDL_Scancode scancode)
{
	t_cam			*cam;

	cam = &scene->camera;
	if (scancode == SDL_SCANCODE_RIGHT)
		cam->origin.x -= 1;
	else if (scancode == SDL_SCANCODE_LEFT)
		cam->origin.x += 1;
	else if (scancode == SDL_SCANCODE_UP)
		cam->origin.y -= 1;
	else if (scancode == SDL_SCANCODE_DOWN)
		cam->origin.y += 1;
	else if (scancode == SDL_SCANCODE_EQUALS)
		cam->origin.z += 0.5;
	else if (scancode == SDL_SCANCODE_MINUS)
		cam->origin.z -= 0.5;
	else if (scancode == SDL_SCANCODE_A)
		cam->basis = rotate_basis(cam->basis, -10, 'y');
	else if (scancode == SDL_SCANCODE_D)
		cam->basis = rotate_basis(cam->basis, 10, 'y');
	else if (scancode == SDL_SCANCODE_S)
		cam->basis = rotate_basis(cam->basis, -10, 'x');
	else if (scancode == SDL_SCANCODE_W)
		cam->basis = rotate_basis(cam->basis, 10, 'x');
	calculate_and_render(scene, sdl_data);
}

void			events(t_scene *scene, t_sdl *sdl_data)
{
	t_shot		s;

	s.x = 0;
	sdl_data->done = SDL_FALSE;
	sdl_data->shot_num = 0;
	while (!sdl_data->done)
	{
		while (SDL_PollEvent(&sdl_data->event) && !sdl_data->done)
		{
			if (sdl_data->event.type == SDL_KEYDOWN)
				rotation(scene, sdl_data,
				sdl_data->event.key.keysym.scancode);
			if (sdl_data->event.type == SDL_QUIT || (
			sdl_data->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE &&
			sdl_data->event.type == SDL_KEYDOWN))
				sdl_data->done = SDL_TRUE;
			if (sdl_data->event.key.keysym.scancode == SDL_SCANCODE_Q &&
			sdl_data->event.type == SDL_KEYDOWN && (++sdl_data->shot_num))
				screenshot(scene, sdl_data, s);
		}
	}
	SDL_RenderClear(sdl_data->render);
	SDL_DestroyWindow(sdl_data->win_ptr);
	SDL_DestroyTexture(sdl_data->texture);
	SDL_Quit();
}
