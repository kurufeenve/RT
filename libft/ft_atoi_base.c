/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkliukin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:49:56 by dkliukin          #+#    #+#             */
/*   Updated: 2019/03/27 16:49:58 by dkliukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_strchr_n(char *str, char c)
{
	int				i;

	i = -1;
	if (str != NULL)
	{
		while (str[++i] != '\0')
			if (str[i] == c)
				return (i);
	}
	return (i);
}

static char			*cut_spare(const char *s, char *symbols)
{
	char			*buffer;
	int				i;

	i = 0;
	while (s[0] == ' ' || s[0] == '\t' || s[0] == '\n' ||
			s[0] == '\r' || s[0] == '\f' || s[0] == '\v')
		s += 1;
	if (s[0] == '+' && ft_strchr(symbols, ft_toupper(s[1])) != NULL)
		s += 1;
	else if ((s[0] == '-' || s[0] == '+') &&
			ft_strchr(symbols, ft_toupper(s[1])) == NULL)
		return (NULL);
	while (ft_strchr(symbols, ft_toupper(s[i])) != NULL ||
			(i == 0 && s[i] == '-'))
		i++;
	buffer = (char *)malloc(sizeof(char) * i + 1);
	if (buffer == NULL)
		return (NULL);
	buffer[i] = '\0';
	while (--i >= 0)
		buffer[i] = s[i];
	return (buffer);
}

int					ft_atoi_base(const char *str, int base)
{
	int				i;
	long long int	res;
	int				factor;
	char			*ptr;
	char			buffer[17];

	factor = 1;
	res = 0;
	ft_strcpy(buffer, "0123456789ABCDEF");
	if (!(ptr = cut_spare(str, buffer)))
		return (0);
	i = ft_strlen(ptr);
	while (--i >= 0)
	{
		if (ptr[i] == '-')
			return (-res);
		res += ft_strchr_n(buffer, ft_toupper(ptr[i])) * factor;
		factor *= base;
	}
	free(ptr);
	return ((int)res);
}
