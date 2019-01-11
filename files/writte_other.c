/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writte_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vomelchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 12:45:16 by vomelchu          #+#    #+#             */
/*   Updated: 2019/01/09 12:45:17 by vomelchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	malloc_vertex(t_vertex *new_vertex)
{
	if (!(new_vertex = (t_vertex *)malloc(sizeof(t_vertex) * 1)))
		ft_error("Bad realloc in vertex");
}

void	free_vertex(t_data *data)
{
	t_vertex	*vert;
	t_vertex	*tmp;
	int			q;

	q = 0;
	vert = &data->vertex;
	tmp = &data->vertex;
	while (vert->next != NULL)
	{
		if (vert->next->next == NULL)
		{
			free(vert->next);
			vert->next = NULL;
			vert = tmp;
		}
		else
			vert = vert->next;
	}
}
