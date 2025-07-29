/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshawish <sshawish@student.42amman.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:05:03 by sshawish          #+#    #+#             */
/*   Updated: 2024/11/28 19:05:06 by sshawish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	process_map_line(int fd, char ***map)
{
	size_t	len;
	int		i;
	char	*line;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		(*map)[i] = line;
		i++;
		if (i >= MAX_LINES)
			break ;
	}
	(*map)[i] = NULL;
	return (i);
}

char	**read_map(const char *filename)
{
	int		fd;
	int		result;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (MAX_LINES + 1));
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	result = process_map_line(fd, &map);
	if (result == -1)
	{
		free_map(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}

int	check_walls(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	validate_and_count(char c, t_count_info *count_info)
{
	if (c != '1' && c != '0' && c != 'P' && c != 'C' && c != 'E' && c != 'K')
		return (0);
	if (c == 'P')
		count_info->count_p++;
	else if (c == 'E')
		count_info->count_e++;
	else if (c == 'C')
		count_info->count_c++;
	else if (c == 'K')
		count_info->count_k++;
	return (1);
}
