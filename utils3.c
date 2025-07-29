/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:11:47 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/28 19:11:48 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_ber(const char *filename)
{
	int	len;
	int	fd;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".ber", 4) == 0)
		return (1);
	return (0);
}

void	window_size(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (!data->map || !data->map[0])
		return ;
	while (data->map[i])
		i++;
	j = 0;
	while (data->map[0][j] != '\0')
		j++;
	data->window_height = i * TILE_SIZE;
	data->window_width = j * TILE_SIZE;
}

int	validate_map(t_data *data, int ac, char **av)
{
	t_count_info	count_info;

	count_info.count_p = 0;
	count_info.count_e = 0;
	count_info.count_c = 0;
	count_info.count_k = 0;
	if (ac != 2)
	{
		ft_putstr_fd("Error: try ./so_long map.ber\n", 2);
		return (EXIT_FAILURE);
	}
	if (!valid_ber(av[1]))
	{
		ft_putstr_fd("Error: provide a valid file that ends with .ber\n", 2);
		return (EXIT_FAILURE);
	}
	if (parse_map(data, av[1], &count_info) == 0)
	{
		ft_putstr_fd("Error: Invalid map!\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	find_start(char **map, int *start_x, int *start_y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*start_x = i;
				*start_y = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	find_start_s(t_data *data, int *start_x, int *start_y)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				*start_x = j;
				*start_y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
