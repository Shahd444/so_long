/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:51:08 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/28 18:51:10 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_info_error(t_flood_fill_info *info)
{
	free (info);
	return (0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	free_struct(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
	{
		free_map(data->map);
		data->map = NULL;
	}
}

void	cleanup_sprites(t_data *data)
{
	if (data->wall_img)
		mlx_destroy_image (data->mlx, data->wall_img);
	if (data->floor_img)
		mlx_destroy_image (data->mlx, data->floor_img);
	if (data->collectible_img)
		mlx_destroy_image (data->mlx, data->collectible_img);
	if (data->exit_img)
		mlx_destroy_image (data->mlx, data->exit_img);
	if (data->player_img1)
		mlx_destroy_image (data->mlx, data->player_img1);
	if (data->enemy_img)
		mlx_destroy_image (data->mlx, data->enemy_img);
}

void	cleanup_game(t_data *data)
{
	cleanup_sprites(data);
	free(data->flood_fill_info);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_struct(data);
}
