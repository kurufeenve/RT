/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 10:58:07 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 10:58:09 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARNING_H
# define WARNING_H

# include "external.h"

# define NO_WARNINGS 0
# define CUSTOM_WARNING 1
# define CAMERA_DO_NOT_EXIST 2
# define TAG_NOT_CLOSED 3
# define INPUT_NOT_CORRECT 4
# define LIGHT_DO_NOT_EXIST 6
# define NO_TPL_OBJECT 9
# define WARNING_RGB_TYPE_UNSUPPORTED 10
# define WARNING_RGB_VALUE 11
# define WARNING_ROTATION_UNSUPPORTED 12
# define WARNING_ROTATION_VALUE 13
# define WARNING_TRANSPARENCY_VALUE 14
# define WARNING_MIRROR_VALUE 15
# define WARNING_REFRACTION_VALUE 16

typedef struct		s_warning
{
	char			*message;
	char			*file;
	int				line;
}					t_warning;

t_warning			g_warning;

void				scene_tags_warning(int warning_code);
void				light_tag_warning(int warning_code);
void				camera_tags_warning(int warning_code);
void				no_object_warning(int warning_code);
void				not_numeric_warning(char *str, char *coord);
void				warning_tag_not_closed(char *tag);
void				not_correct_input(int warning_code);
void				no_closing_tag_warning(int warning_code);

void				warning(int warning_code);
void				set_warning_message(char *param);
void				set_warning_line(int line);
int					get_warning_line();

void				set_warning_file(char *file);
char				*get_warning_file(void);
void				delete_warning_file();

void				warning_rgb_field_type(int warning_code);
void				warning_rotation_field_type(int warning_code);
void				warning_transparency_field_type(int warning_code);
void				warning_mirror_field_type(int warning_code);

void				compile_params_warning(char *param);
void				parametr_not_found_warning(char *name);

#endif
