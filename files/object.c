/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 19:32:18 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/02 13:23:43 by vomelchu         ###   ########.fr       */
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
		if (x != 3 && (data->num_icon != 6 && data->num_icon != 4
					&& data->num_icon != 2) && data->icons[q].obj
			== data->num_icon)
			return (q);
		if ((data->num_icon == 6 || data->num_icon == 4 ||
					data->num_icon == 2) && data->icons[q].obj == data->num_icon
				&& data->icons[q].sector == data->num_sector)
			return (q);
	}
	if (x == 3)
		data->object -= 1;
	return (q);
}

int		end_start_marker(t_data *data)
{
	int q;

	if (data->num_icon == 6)
		return (0);
	q = -1;
	while (++q != data->object)
	{
		if (data->num_icon == 0 && data->icons[q].obj == 1
				&& data->icons[q].sector == data->num_sector)
			return (1);
		if (data->num_icon == 1 && data->icons[q].obj == 0
				&& data->icons[q].sector == data->num_sector)
			return (1);
	}
	return (0);
}

int		check_flag(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->object)
	{
		if (data->icons[i].flag == 0)
			return (i);
	}
	return (-1);
}

void	special_icons(t_data *data)
{
	int q;

	if (end_start_marker(data) == 0)
	{
		q = modif_obj(data, data->num_icon);
		if (q == data->object)
		{
			if (check_flag(data) > 0)
				writte_icons_to_struct(data, check_flag(data));
			else
			{
				writte_icons_to_struct(data, data->object);
				data->object++;
			}
		}
		else
			writte_icons_to_struct(data, q);
	}
}
