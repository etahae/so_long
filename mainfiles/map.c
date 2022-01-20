/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:55:21 by tnamir            #+#    #+#             */
/*   Updated: 2022/01/20 18:09:59 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mapmodifierx(char	**map, int	*collectibles, int *x, int *y)
{
	int	yy;
	int	xx;

	xx = 0;
	yy = 0;
	while (map[yy])
	{
		xx = 0;
		while (map[yy][xx])
		{
			if (map[yy][xx] == 'C')
				*collectibles += 1;
			if (map[yy][xx] == 'P')
				map[yy][xx] = '0';
			if (yy == *y && xx == *x)
			{
				if (map[yy][xx] != '1')
					map[yy][xx] = 'P';
			}
			xx++;
		}
		yy++;
	}
}

char	**mapmodifier(char	**map, int x, int y, int *movecount)
{
	int			xx;
	int			yy;
	int			collectibles;

	collectibles = 0;
	xx = 0;
	yy = 0;
	if (x || y)
	{
		mapmodifierx(map, &collectibles, &x, &y);
	}
	yy = 0;
	if (!collectibles)
	{
		while (map[yy])
		{
			if (indexof(map[yy], 'E'))
				map[yy][indexof(map[yy], 'E')] = 'e';
			yy++;
		}
	}
	*movecount += 1;
	return (map);
}

void	mapx(char map, t_program *program, char *direction)
{
	if (map == '1')
		putimage(program, "./sprites/wall.xpm");
	else if (map == 'P')
	{
		if (*direction == 'l')
			putimage(program, "./sprites/skeleton2.xpm");
		else
			putimage(program, "./sprites/skeleton1.xpm");
	}
	else if (map == 'E')
		putimage(program, "./sprites/closedoor.xpm");
	else if (map == 'C')
		putimage(program, "./sprites/flame.xpm");
	else if (map == 'e')
		putimage(program, "./sprites/opendoor.xpm");
	else if (map == 'B')
		putimage(program, "./sprites/ghost.xpm");
}

void	mapy(char	**map, t_program *program, char	*direction)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		program->sprite_position.x = 0;
		while (map[y][x])
		{
			mapx(map[y][x], program, direction);
			if (map[y][x] == 'P')
			{
				program->character.pos.x = x;
				program->character.pos.y = y;
			}
			x++;
			program->sprite_position.x += 50;
		}
		y++;
		program->sprite_position.y += 50;
	}
}

void	mapparsing(char	**map, t_program *program, int newx,
		int newy)
{
	static int	movecount;
	char		*movecountchar;

	mlx_clear_window(program->mlx, program->window.reference);
	if (map[newy][newx] == 'e' || map[newy][newx] == 'B')
	{
		if (map[newy][newx] == 'B')
			printf("You lost !");
		if (map[newy][newx] == 'e')
			printf("You won !");
		exit(0);
	}
	if (map[newy][newx] != '1' && (map[newy][newx] != 'E'))
		map = mapmodifier(map, newx, newy, &movecount);
	program->sprite_position.y = 0;
	mapy(map, program, &program->direction);
	movecountchar = ft_itoa(movecount);
	mlx_string_put(program->mlx, program->window.reference,
		18, 15, 0xFFFFFF, movecountchar);
}