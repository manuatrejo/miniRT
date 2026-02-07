/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteag <amonteag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:45:17 by amonteag          #+#    #+#             */
/*   Updated: 2026/02/07 16:42:25 by amonteag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_cones(t_cone_list *cnl)
{
	t_cone_list	*next;

	while (cnl)
	{
		next = cnl->next;
		free(cnl);
		cnl = next;
	}
}

void	free_runtime_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->lights);
	free(scene->sphere);
	free(scene->plane);
	free(scene->cylinder);
	free(scene->cone);
	ft_bzero(scene, sizeof(*scene));
}