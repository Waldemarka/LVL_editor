/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_icons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:53:19 by vomelchu          #+#    #+#             */
/*   Updated: 2018/12/17 14:53:20 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	writte_icons_to_struct(t_data *data, int q)
{
	data->icons[q].x = data->x_canv;
	data->icons[q].y = data->y_canv;
	data->icons[q].obj = data->num_icon;
	data->icons[q].sector = data->num_sector;
	data->icons[q].flag = 1;
}

int		modif_obj(t_data *data, int x)
{
	int q;

	q = -1;
	if (x == 3)
		data->object += 1;
	while (++q != data->object)
	{
		if (x == 3 && data->icons[q].sector == data->current_sector)
			data->icons[q].flag = 0;
		if (x != 3 && data->num_icon != 8 && data->icons[q].obj == data->num_icon)
			return (q);
		if (data->num_icon == 8 && data->icons[q].obj == data->num_icon
			&& data->icons[q].sector == data->num_sector)
			return (q);
	}
	if (x == 3)
		data->object -= 1;
	return (q);
}