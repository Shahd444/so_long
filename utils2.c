/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:09:00 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/28 19:09:02 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	count_collectibles(char **map)
{
	int	i;
	int	j;
	int	collectibles;

	i = 0;
	collectibles = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				collectibles++;
			j++;
		}
		i++;
	}
	return (collectibles);
}

int	find_start_and_check(char **map, int *start_x,
							int *start_y, t_flood_fill_info *info)
{
	if (!find_start(map, start_x, start_y))
	{
		free(info);
		return (0);
	}
	return (1);
}

void	flood_fill(char **map, int x, int y, t_flood_fill_info *info)
{
	if (x < 0 || y < 0 || !map[x] \
		|| !map[x][y] || map[x][y] == '1' \
		|| map[x][y] == 'V')
		return ;
	if (map[x][y] == 'C')
		info->collectibles++;
	if (map[x][y] == 'E')
		info->exit_found++;
	map[x][y] = 'V';
	flood_fill(map, x - 1, y, info);
	flood_fill(map, x + 1, y, info);
	flood_fill(map, x, y - 1, info);
	flood_fill(map, x, y + 1, info);
}

int	allocate_flood_fill_info(t_flood_fill_info **info)
{
	*info = malloc(sizeof(t_flood_fill_info));
	if (!*info)
		return (0);
	(*info)->collectibles = 0;
	(*info)->exit_found = 0;
	return (1);
}
