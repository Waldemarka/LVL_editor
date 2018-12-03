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

int		min(int	x, int y)
{
	if (x < y)
		return (x);
	else
		return (y);
	return (x);
}

int		max(int	x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
	return (x);
}
