/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_structures.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 17:49:25 by akulaiev          #+#    #+#             */
/*   Updated: 2018/11/28 17:49:27 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVICE_STRUCTURES_H
# define SERVICE_STRUCTURES_H

typedef struct		s_iterators
{
	int				i;
	int				j;
	int				k;
	int				x;
	int				y;
	double			x_screen;
	double			y_screen;
}					t_iterators;

typedef struct		s_refract
{
	double			fresnel;
	double			ior_air;
	double			ior_fig;
	double			refr_coeff;
	double			cos_ray_norm;
	double			cos_refl_ray;
	t_color			refraction;
	t_color			reflection;
	t_ray			refl;
	t_ray			refr;
}					t_refract;

typedef struct		s_quadratic
{
	t_position		tmp;
	t_position		tmp1;
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			u;
	double			v;
	double			z;
	double			p;
	double			q;
	double			discriminant;
	double			sq_a;
	double			cb_p;
	double			sqrt_d;
	t_position		delta_p;
	int				i;
	int				num;
	t_ray			ray;
	t_object		figure;
}					t_quadratic;

typedef struct		s_torus
{
	double			dir_scalar;
	double			dir_origin;
	double			origin_scalar;
	double			radiuses_sum;
	double			ray_torus_dir;
	double			ray_origin_torus_dir;
}					t_torus;

typedef struct		s_refdata
{
	t_object		fig;
	t_thread		*data;
	t_ray			ray;
	t_intersection	*its;
}					t_refdata;

typedef struct		s_smap
{
	int				nt;
	double			x_cube;
	double			y_cube;
	double			ma;
	double			ax;
	double			ay;
	double			az;
	double			x_tex;
	double			y_tex;
	int				x_pix;
	int				y_pix;
	int				np;
}					t_smap;

typedef struct		s_box
{
	double			tmax;
	double			tymin;
	double			tymax;
	double			tzmin;
	double			tzmax;
	t_position		inverted_dir;
	t_position		borders[2];
	int				sign[3];
}					t_box;

typedef struct		s_shot
{
	int				x;
	int				y;
	char			*x_c;
	char			*y_c;
	char			*w_c;
	char			*h_c;
	char			*sh;
	char			*command;
}					t_shot;

t_position			vector_add(t_position first, t_position second);
t_position			vector_mult(t_position first, double val);
t_position			vector_divide(t_position first, double val);
double				vector_scalar(t_position first, t_position second);
t_position			vector_cross(t_position first, t_position second);
t_position			vector_subtract(t_position first, t_position second);
double				vector_len(t_position vec);
void				normalize(t_position *ray);
t_base				get_basis(t_position vect);
void				camera_rotation(t_position *n, t_position tmp,
t_rotation ro);
t_base				rotate_basis(t_base basis, int angle, char axis);
t_position			rotate_figure(t_object fig);
double				solve_quadratic(t_quadratic var, t_intersection *its,
double height);
int					solve_quadratic_two(double c[3], double s[2]);
double				solve_quartic(t_quadratic var, t_intersection *its);
int					tex_gen(t_scene *scene, t_sdl *sdl_data);
t_refdata			init_refdata(t_object fig, t_thread *data, t_ray ray,
t_intersection *its);

#endif
