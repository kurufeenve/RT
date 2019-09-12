/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:20:28 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 11:20:30 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define NO_FILE 1
# include "external.h"

void		error(int error_code);
void		file_error(int error_code);

#endif
