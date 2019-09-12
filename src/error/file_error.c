/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:23:04 by dkliukin          #+#    #+#             */
/*   Updated: 2018/11/17 11:23:05 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/error.h"

void		file_error(int error_code)
{
	if (error_code == NO_FILE)
		ft_putstr("\033[1;31mERROR: No such scene or file!\033[0m\n");
}
