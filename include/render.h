/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:12:30 by akulaiev          #+#    #+#             */
/*   Updated: 2018/12/05 15:12:34 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

typedef struct		s_shd
{
	t_ray			light;
	t_position		view_vect;
	t_position		half_vect;
	t_color			col;
	double			n_mult_l;
	double			h_mult_l;
	double			light_len;
	t_iterators		i;
	double			light_intens;
	t_object		*fig;
	t_refdata		rd;
}					t_shd;

typedef struct		s_skybox
{
	char			**t_n;
	int				tex_num;
	SDL_Surface		**sky_tex;
	t_color			**sky_tex_3;
}					t_skybox;

typedef struct		s_sdl
{
	SDL_Window		*win_ptr;
	SDL_bool		done;
	SDL_Event		event;
	SDL_Texture		*texture;
	SDL_Renderer	*render;
	int				pitch;
	int				num_threads;
	int				lines_per_thread;
	int				*img_ptr;
	t_skybox		sky;
	int				shot_num;
}					t_sdl;

void				sdl_init(t_scene *scene, t_sdl *sdl_data);
void				*create_ray(void *data);
t_color				blinn_phong_shading(int rec, t_thread *data, t_ray ray,
t_intersection *its);
void				create_threads(t_scene *scene, t_sdl *sdl_data);
void				events(t_scene *scene, t_sdl *sdl_data);
void				calculate_and_render(t_scene *scene, t_sdl *sdl_data);
void				reflection_refraction(int rec, t_refdata rd, t_shd *s);
int					mult_cols(int col, double mult);
int					add_cols(int first, int second);
int					skybox_map(t_sdl *sdl, double x, double y, double z);
void				get_its_params(t_object f, t_ray r, t_intersection *i);
t_color				*tex_transform(SDL_Surface *tex, t_iterators i);
int					tex_c(t_intersection *its, t_scene scene, t_object *fig);
int					sphere_mapping(t_position point, t_object *fig);
int					plane_mapping(t_position point, t_object *fig);
int					cylinder_mapping(t_position point, t_object *fig);
#endif
