/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_manipulate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:42:05 by akulaiev          #+#    #+#             */
/*   Updated: 2018/11/28 14:42:07 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		load_textures(t_scene *scene)
{
	int			i;
	t_iterators	it;

	i = -1;
	while (++i < scene->num_figs && (it.k = 1))
	{
		if (!scene->figs[i].texture.filename ||
		!ft_strcmp(scene->figs[i].texture.filename, "None"))
		{
			scene->figs[i].texture.tex_check = 0;
			return (1);
		}
		scene->figs[i].texture.surf =
		(SDL_LoadBMP(scene->figs[i].texture.filename));
		if (!scene->figs[i].texture.surf)
			return (0);
		scene->figs[i].texture.texture =
		tex_transform(scene->figs[i].texture.surf, it);
		scene->figs[i].texture.wid = scene->figs[i].texture.surf->w;
		scene->figs[i].texture.hei = scene->figs[i].texture.surf->h;
		if (!ft_strcmp(scene->figs[i].object, "sphere"))
			scene->figs[i].color.color = 0;
		scene->figs[i].texture.tex_check = 1;
	}
	return (1);
}

void			calculate_and_render(t_scene *scene, t_sdl *sdl_data)
{
	create_threads(scene, sdl_data);
	sdl_data->pitch = sizeof(sdl_data->img_ptr[0]) *
	scene->window_width;
	SDL_UpdateTexture(sdl_data->texture, NULL,
	sdl_data->img_ptr, sdl_data->pitch);
	SDL_RenderCopy(sdl_data->render, sdl_data->texture,
	NULL, NULL);
	SDL_RenderPresent(sdl_data->render);
}

void			sdl_init(t_scene *scene, t_sdl *sdl_data)
{
	if ((SDL_Init(SDL_INIT_EVERYTHING) != 0) ||
	((sdl_data->win_ptr = SDL_CreateWindow("RT_basic", 300, 300,
	scene->window_width, scene->window_height, 0)) == NULL) ||
	((sdl_data->img_ptr = (int*)malloc(sizeof(int) *
	scene->window_width * scene->window_height)) == NULL) ||
	((sdl_data->render = SDL_CreateRenderer(sdl_data->win_ptr,
	-1, 0)) == NULL) || ((sdl_data->texture =
	SDL_CreateTexture(sdl_data->render, SDL_PIXELFORMAT_UNKNOWN,
	SDL_TEXTUREACCESS_TARGET, scene->window_width,
	scene->window_height)) == NULL) || !load_textures(scene))
		exit(write(2, "Problem with SDL init!\n", 23));
	scene->sky_check = tex_gen(scene, sdl_data);
	calculate_and_render(scene, sdl_data);
	events(scene, sdl_data);
}

static void		join_threads(t_iterators iter, t_thread *data,
pthread_t *th_id, t_sdl sdl_data)
{
	iter.i = -1;
	while (++iter.i < sdl_data.num_threads)
		pthread_join(th_id[iter.i], NULL);
	free(data);
	free(th_id);
}

void			create_threads(t_scene *scene, t_sdl *sdl_data)
{
	t_iterators	iter;
	t_thread	*data;
	pthread_t	*th_id;

	sdl_data->num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	sdl_data->lines_per_thread = scene->window_height / sdl_data->num_threads;
	data = (t_thread*)malloc(sizeof(t_thread) * sdl_data->num_threads);
	th_id = (pthread_t*)malloc(sizeof(pthread_t) * sdl_data->num_threads);
	iter.i = -1;
	iter.j = -1;
	while (++iter.i < sdl_data->num_threads)
	{
		data[iter.i].current_y = iter.j;
		data[iter.i].scene = scene;
		data[iter.i].sdl_data = sdl_data;
		iter.j += sdl_data->lines_per_thread;
	}
	iter.i = -1;
	while (++iter.i < sdl_data->num_threads)
		pthread_create(&th_id[iter.i], NULL, create_ray, data + iter.i);
	join_threads(iter, data, th_id, *sdl_data);
}
