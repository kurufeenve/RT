/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:13:47 by dkliukin          #+#    #+#             */
/*   Updated: 2018/10/20 21:13:49 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "data.h"
# include "external.h"

typedef struct s_sdl	t_sdl;

typedef struct			s_intersection
{
	double				t;
	double				t0;
	double				t1;
	double				closest_t;
	t_position			normal;
	t_position			its_point;
	double				parabol_kernel_dist;
	int					x;
	int					y;
}						t_intersection;

typedef	struct			s_refraction
{
	double				ior;
	double				transparency;
}						t_refraction;

typedef struct			s_object
{
	char				*object;
	t_color				color;
	int					shininess;
	double				radius;
	double				small_radius;
	double				height;
	double				cone_angle;
	t_position			pos;
	t_position			direction;
	t_rotation			angle;
	int					(*f)(struct s_object *figs,
	t_ray ray, t_intersection *its);
	double				ellips_a;
	double				ellips_k;
	double				ellips_c;
	double				ellips_b;
	t_position			pos2;
	t_position			pos_mid;
	double				mirror;
	t_refraction		refract;
	t_texture			texture;
}						t_object;

typedef	enum			e_obj_type
{
	CAMERA,
	LIGHT,
	FIGURE
}						t_obj_type;

typedef	enum			e_fig_type
{
	CUT_CYLINDER,
	CUT_CONE,
	SPHERE,
	CONE,
	CYLINDER,
	ELLIPSOID,
	ELLIPTIC_PARABOLOID,
	HYPERBOLIC_PARABOLOID,
	PLANE,
	TORUS,
	CUBE
}						t_fig_type;

typedef	enum			e_light_type
{
	POINT,
	AMBIENT
}						t_light_type;

typedef struct			s_obj_wrapper
{
	t_obj_type			type;
	void				*obj;
}						t_obj_wrapper;

typedef	struct			s_light
{
	t_position			coords;
	t_light_type		type;
	double				intensity;
}						t_light;

typedef	struct			s_scene
{
	t_object			*figs;
	t_light				*lights;
	t_list				*lst_obj;
	t_cam				camera;
	int					window_width;
	int					window_height;
	int					num_lights;
	int					num_figs;
	int					sky_num;
	int					sky_check;
}						t_scene;

typedef struct			s_thread
{
	int					current_y;
	t_scene				*scene;
	t_sdl				*sdl_data;
}						t_thread;

int						get_closest_shape(t_thread *data, t_ray ray,
t_intersection *its);
int						cylinder_intersection(t_object *cylinder, t_ray ray,
t_intersection *its);
int						cone_intersection(t_object *cone, t_ray ray,
t_intersection *its);
int						sphere_intersection(t_object *sphere, t_ray ray,
t_intersection *its);
int						plane_intersection(t_object *plane, t_ray ray,
t_intersection *its);
int						elliptic_paraboloid_intersection(t_object *paraboloid,
t_ray ray,
t_intersection *its);
int						hyperbolic_paraboloid_intersection(t_object *paraboloid,
t_ray ray,
t_intersection *its);
int						ellipsoid_intersection(t_object *ellipsoid, t_ray ray,
t_intersection *its);
int						torus_intersection(t_object *torus, t_ray ray,
t_intersection *its);
int						box_intersection(t_object *box, t_ray ray,
t_intersection *its);
void					obj_count(t_scene *sc);
void					read_cam(t_scene *sc, t_cam *cam);
int						fig_check(t_list *lst);
int						fig_check2(t_list *lst);
void					light_write(t_scene *sc);
void					fig_write(t_scene *sc);
t_object				add_cone_cap(t_object fig);
t_object				add_cylinder_cap(t_object fig, int cap_num);
int						write_params(t_scene *sc, t_list *lst, int i);
int						write_params2(t_scene *sc, t_list *lst, int i);
int						write_params3(t_scene *sc, t_list *lst, int i);
int						write_params4(t_scene *sc, t_list *lst, int i);

#endif
