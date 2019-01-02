/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:38:01 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:24:23 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		radians(double a)
{
	int x;

	x = (int)(a * 100);
	if (x == -314)
		return (1);
	return (-1);
}

int		for_atan(t_vector vect1, t_vector vect2)
{
	double a;

	a = atan2(vect1.x * vect2.y - vect2.x * vect1.y,
		vect1.x * vect2.x + vect1.y * vect2.y);
	if (a < 0 && radians(a) < 0)
		return (1);
	return (0);
}

int		clockwise_3(t_sector *tmp_sect)
{
	t_vector vect1;
	t_vector vect2;
	t_vector vect3;

	vect1.x = tmp_sect->next->x0 - tmp_sect->x0;
	vect1.y = tmp_sect->next->y0 - tmp_sect->y0;
	vect2.x = tmp_sect->next->next->x0 - tmp_sect->next->x0;
	vect2.y = tmp_sect->next->next->y0 - tmp_sect->next->y0;
	vect3.x = tmp_sect->x0 - tmp_sect->next->next->x0;
	vect3.y = tmp_sect->y0 - tmp_sect->next->next->y0;
	if (for_atan(vect1, vect2) == 1)
		return (1);
	if (for_atan(vect2, vect3) == 1)
		return (1);
	if (for_atan(vect3, vect1) == 1)
		return (1);
	return (0);
}

int		clockwise_4(t_sector *tmp_sect)
{
	t_vector vect1;
	t_vector vect2;
	t_vector vect3;
	t_vector vect4;

	vect1.x = tmp_sect->next->x0 - tmp_sect->x0;
	vect1.y = tmp_sect->next->y0 - tmp_sect->y0;
	vect2.x = tmp_sect->next->next->x0 - tmp_sect->next->x0;
	vect2.y = tmp_sect->next->next->y0 - tmp_sect->next->y0;
	vect3.x = tmp_sect->next->next->next->x0 - tmp_sect->next->next->x0;
	vect3.y = tmp_sect->next->next->next->y0 - tmp_sect->next->next->y0;
	vect4.x = tmp_sect->x0 - tmp_sect->next->next->next->x0;
	vect4.y = tmp_sect->y0 - tmp_sect->next->next->next->y0;
	if (for_atan(vect1, vect2) == 1)
		return (1);
	if (for_atan(vect2, vect3) == 1)
		return (1);
	if (for_atan(vect3, vect4) == 1)
		return (1);
	if (for_atan(vect4, vect1) == 1)
		return (1);
	return (0);
}

int		clockwise1(t_data *data)
{
	double		a;
	t_sector	*tmp_sect;

	a = 0.0;
	tmp_sect = &data->sectors[data->current_sector];
	if (len_list(tmp_sect) == 3 && clockwise_3(tmp_sect) == 1)
		return (1);
	if (len_list(tmp_sect) == 4 && clockwise_4(tmp_sect) == 1)
		return (1);
	return (0);
}
