/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 21:35:00 by dkliukin          #+#    #+#             */
/*   Updated: 2018/10/20 21:35:01 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "scene.h"
# include "external.h"
# include "warning.h"
# include "error.h"
# define OBJ_TPL_PATH "src/scenes/objects/"
# define OBJ_TPL_EXTENTION ".scene.obj"
# define OPEN_TAG 1
# define CLOSE_TAG 2
# define TRUE 1
# define FALSE 0

typedef struct		s_tags
{
	int				open;
	int				close;
	char			*in_tag;
	char			*name;
	char			*obj_tpl;
}					t_tags;

typedef struct		s_param_val
{
	char			*name;
	char			*val;
}					t_param_val;

int					match_tag(char *scene, char *tag, int start_from, int mod);
char				*get_tpl_obj(char *obj);
int					find_tag_position(char *scene,
char **to_find, int start_from);
void				set_param_in_tpl(t_param_val param, char **obj);
void				cut_params(char *scene, int com_fd);
int					read_scene_file(char *file);
int					run_scene(char *file);

int					check_value(char *value, char *param_name);
int					check_type(char *value);
int					check_rgb_color(char *value, char *param_name);
int					check_hexadecimal_color(char *value);
int					check_rotation(char *value, char *param_name);
int					check_transparency(char *value, char *param_name);
int					check_mirror(char *value, char *param_name);
int					check_refraction(char *value, char *param_name);

void				get_figure_inner_info(char *object,
t_scene **scene, t_tags tag);
void				get_tag_inner_info(char *scene_txt,
t_scene **scene, int *i);
void				processing_objects(char *scene_txt, t_scene **scene);
void				processing_scene(t_scene *scene);
t_obj_wrapper		*return_camera(void);
t_obj_wrapper		*return_light(void);
t_obj_wrapper		*return_figure(t_tags tag);
t_obj_wrapper		*create_scene_object(t_tags tag);
void				scene_setup(t_scene **scene, t_obj_wrapper **wrapper);
void				scene_object(
	t_tags param_tag, t_obj_wrapper *object);

void				set_position(t_tags param_tag, t_obj_wrapper *object);
void				set_normale(t_tags param_tag, t_obj_wrapper *object);
void				set_color_rgb(t_tags param_tag, t_obj_wrapper *object);
void				set_color_hex(t_tags param_tag, t_obj_wrapper *object);
void				set_intensity(t_tags param_tag, t_obj_wrapper *object);
void				set_radius(t_tags param_tag, t_obj_wrapper *object);
void				set_transparency(t_tags param_tag, t_obj_wrapper *object);
void				set_height(t_tags param_tag, t_obj_wrapper *object);
void				set_rotation(t_tags param_tag, t_obj_wrapper *object);
void				set_width(t_tags param_tag, t_obj_wrapper *object);
void				set_length(t_tags param_tag, t_obj_wrapper *object);
void				set_mirror(t_tags param_tag, t_obj_wrapper *object);
void				set_refraction(t_tags param_tag, t_obj_wrapper *object);
void				set_cone_angle(t_tags param_tag, t_obj_wrapper *object);
void				set_position2(t_tags param_tag, t_obj_wrapper *object);
void				set_shininess(t_tags param_tag, t_obj_wrapper *object);
void				set_ligth_type(t_tags param_tag, t_obj_wrapper *object);
void				set_texture(t_tags param_tag, t_obj_wrapper *object);
/*
** Additional functionality
*/

char				*ft_strjoin_mod(char *a, char *b);
char				*ft_strjoin_mod_rew(char *a, char *b);
int					array_length(char **array);
int					is_numeric(char *str);
void				del_double_arr(char ***str);
void				manage_normales(double *x, double *y, double *z);
int					check_coord_rel(char *param_name);
int					empty(char *src);
void				close_warning(char *tag_name);

#endif
