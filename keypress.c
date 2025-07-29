/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:13:30 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/28 19:13:35 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_data *data)
{
	cleanup_game(data);
	exit(0);
	return (0);
}

int	handle_symbols(t_data *data, int new_x, int new_y)
{
	if (data->map[new_y][new_x] == 'C')
	{
		data->flood_fill_info->collectibles--;
		data->map[new_y][new_x] = '0';
	}
	if (data->map[new_y][new_x] == 'E' \
		&& data->flood_fill_info->collectibles == 0)
	{
		ft_printf("You win!\n");
		cleanup_game(data);
		exit(0);
	}
	if (data->map[new_y][new_x] == 'K')
	{
		ft_printf("Game Over!\n");
		cleanup_game(data);
		exit(0);
	}
	return (1);
}

int	change_player_position(int keycode, t_data *data, int *new_x, int *new_y)
{
	*new_x = data->player_x;
	*new_y = data->player_y;
	if (keycode == KEY_W || keycode == A_UP)
		*new_y -= 1;
	else if (keycode == KEY_S || keycode == A_DOWN)
		*new_y += 1;
	else if (keycode == KEY_A || keycode == A_LEFT)
		*new_x -= 1;
	else if (keycode == KEY_D || keycode == A_RIGHT)
		*new_x += 1;
	else
		return (0);
	return (1);
}

int	move_player(t_data *data, int keycode)
{
	int	new_x;
	int	new_y;

	if (!change_player_position(keycode, data, &new_x, &new_y))
		return (0);
	if (data->map[new_y][new_x] != '1')
	{
		mlx_put_image_to_window (data->mlx, data->window,
			data->floor_img, data->player_x * TILE_SIZE,
			data->player_y * TILE_SIZE);
		if (!handle_symbols(data, new_x, new_y))
			return (0);
		data->player_x = new_x;
		data->player_y = new_y;
		data->move_count++;
		ft_printf("Number of movements: %d\n", data->move_count);
	}
	return (1);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		cleanup_game(data);
		exit(0);
	}
	if (move_player(data, keycode))
	{
		game_loop(data);
	}
	return (0);
}
