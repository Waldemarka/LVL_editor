/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:32:00 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/03 19:32:01 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void    ft_error(char *str)
{
	ft_putstr(str);
	exit(0);
}

int		near_round(int q)
{
	int i;

	i = q % 10;
	if (i < 5)
		return (q - i);
	else
		return((q - i) + 10);
	return (q);
}

double		min(double	x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double		max(double	x, double y)
{
	if (x > y)
		return (x);
	return (y);
}
