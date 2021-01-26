#include "maze.h"

void	init_map(t_map **map, const char *map_file)
{
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
		lite_error(MALLOC_PARSE);
	(*map)->line = NULL;
	(*map)->split = NULL;
	(*map)->raw_map = NULL;
	(*map)->map = NULL;
	(*map)->paths = (char **)malloc(sizeof(char *) * 5);
	if (!(*map)->paths)
		map_error(MALLOC_PARSE, map);
	(*map)->paths[NO] = NULL;
	(*map)->paths[EA] = NULL;
	(*map)->paths[SO] = NULL;
	(*map)->paths[WE] = NULL;
	(*map)->paths[SPRITE] = NULL;
	(*map)->fd = open(map_file, O_RDONLY);
	if ((*map)->fd == -1)
		map_error(NEG_FD, map);
	(*map)->colors[GET_FLOOR] = 0;
	(*map)->colors[GET_CEILING] = 0;
	(*map)->player[GET_ALL] = 0;
	(*map)->res[X] = 0;
	(*map)->map_done = 0;
}

void	init_game(t_game **game, t_map *map)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!*game)
		map_error(MALLOC_GAME, &map);
	(*game)->paths = map->paths;
	map->paths = NULL;
	(*game)->map = map->map;
	map->map = NULL;
	(*game)->win = NULL;
	(*game)->maze = NULL;
	(*game)->ttrs = (t_mlximg **)malloc(sizeof(t_mlximg *) * 5);
	if (!(*game)->ttrs)
	{
		free_map(&map);
		game_error(MLX_MALLOC, game);
	}
	(*game)->ttrs[NO] = NULL;
	(*game)->ttrs[EA] = NULL;
	(*game)->ttrs[SO] = NULL;
	(*game)->ttrs[WE] = NULL;
	(*game)->ttrs[SPRITE] = NULL;
	(*game)->rows = map->tokens;
	(*game)->res[X] = map->res[X];
	(*game)->res[Y] = map->res[Y];
	(*game)->colors[FLOOR] = map->colors[FLOOR];
	(*game)->colors[CEILING] = map->colors[CEILING];
	(*game)->player[X] = map->player[X];
	(*game)->player[Y] = map->player[Y];
	(*game)->dir[X] = map->dir[X];
	(*game)->dir[Y] = map->dir[Y];
	(*game)->plane[X] = map->plane[X];
	(*game)->plane[Y] = map->plane[Y];
	(*game)->event = NO_KEY;
	free_map(&map);
}