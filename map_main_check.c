/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_main_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:57:51 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/28 18:57:54 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(char **map)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	while (map[i])
	{
		if ((ft_strlen(map[i])) != len)
			return (0);
		i++;
	}
	return (1);
}

int	is_enclosed_in_walls(char **map)
{
	size_t	len;
	int		i;
	int		last_row_index;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	if (!check_walls(map[0]))
		return (0);
	i = 0;
	while (map[i + 1])
		i++;
	last_row_index = i;
	if (!check_walls(map[last_row_index]))
		return (0);
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	has_valid_elements(char **map, t_count_info *count_info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j++])
		{
			if (!validate_and_count(map[i][j - 1], count_info))
				return (0);
		}
		i++;
	}
	if (count_info->count_p != 1 || count_info->count_e != 1 \
		|| count_info->count_c < 1)
		return (0);
	return (1);
}

int	is_accessible(char **map, t_data *data)
{
	t_flood_fill_info	*info;
	int					start_x;
	int					start_y;
	int					total_collectibles;
	char				**map_copy;

	if (!allocate_flood_fill_info(&info))
		return (0);
	data->flood_fill_info = info;
	if (!find_start_and_check(map, &start_x, &start_y, info))
		return (handle_info_error(info));
	total_collectibles = count_collectibles(map);
	map_copy = copy_map(map);
	if (!map_copy)
		return (handle_info_error(info));
	flood_fill(map_copy, start_x, start_y, info);
	if (info->collectibles != total_collectibles || info->exit_found == 0)
	{
		free_map(map_copy);
		return (handle_info_error(info));
	}
	free_map(map_copy);
	return (1);
}

int	parse_map(t_data *data, char *filename, t_count_info *count_info)
{
	int		valid;
	char	**map;

	map = read_map(filename);
	if (!map)
		return (0);
	data->map = map;
	if (!map)
		return (0);
	valid = (is_rectangular(map) \
		&& is_enclosed_in_walls(map) \
		&& has_valid_elements(map, count_info) \
		&& is_accessible(map, data));
	if (!valid)
		free_map(map);
	return (valid);
}
