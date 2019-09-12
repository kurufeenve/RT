/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:32:32 by dkliukin          #+#    #+#             */
/*   Updated: 2018/10/20 21:32:33 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init(t_scene *sc)
{
	sc->num_figs = 0;
	sc->num_lights = 0;
	sc->window_width = 760;
	sc->window_height = 512;
}

static void		start_render(t_scene *scene, char **av, int ac)
{
	scene->sky_num = 4;
	if (ac == 3)
		scene->sky_num = atoi(av[2]);
	if (scene->sky_num < 0 || scene->sky_num > 5)
		scene->sky_num = 1;
	set_warning_file(av[1]);
	if (run_scene(av[1]))
		processing_scene(scene);
	if (!scene->lst_obj)
		exit(write(2, "\033[31mEmpty scene\033[0m\n", 22));
	init(scene);
	scene->camera.exist = 0;
	obj_count(scene);
	light_write(scene);
	fig_write(scene);
}

int				main(int ac, char *av[])
{
	t_scene		scene;
	t_sdl		sdl_data;
	int			i;

	if (ac == 2 || ac == 3)
		start_render(&scene, av, ac);
	else
		exit(write(2, "Usage: ./rt src/scenes/SCENE_NUM SKYBOX_NUM\n\n\
It is not possible for lights or camera to lay on the surface of a figure.\
\nVisual effects coefficients:\n\
light: 0-100\ntransparency: 0-100\nrefraction: 100-200\nmirror: \
0-100\n", 217));
	i = -1;
	while (++i < scene.num_figs)
	{
		if (ft_strcmp(scene.figs[i].object, "sphere"))
			scene.figs[i].direction = rotate_figure(scene.figs[i]);
	}
	sdl_init(&scene, &sdl_data);
	system("leaks rt | grep -iE \"leak\"");
	return (0);
}
