#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "arkanoid.h"

void		print_block(t_game *game)
{
	t_level *lv;
	int		i;
	int		y;

	lv = game->levels;
	while (lv)
	{
		i = 0;
		ft_printf("Tab name tab = %s, %d, %d\n", lv->name ,lv->width, lv->height);
		while (lv->height > i)
		{
			y = 0;
			while (lv->width > y)
			{
				if (lv->blocks[i][y].type == BLOCK_EMPTY)
					ft_printf(" ");
				else if (lv->blocks[i][y].type == BLOCK_EASY)
					ft_printf("1");
				else if (lv->blocks[i][y].type == BLOCK_MEDIUM)
					ft_printf("2");
				else if (lv->blocks[i][y].type == BLOCK_HARD)
					ft_printf("3");
				else if (lv->blocks[i][y].type == BLOCK_IMMORTAL)
					ft_printf("4");
				else if (lv->blocks[i][y].type == BLOCK_BONUS)
					ft_printf("5");
				y++;
			}
			ft_printf("\n");
			i++;
		}
		ft_printf("End Tab \n");
		lv = lv->next;
	}
}



int		main()
{
	t_game game;

	game.levels = NULL;
	parse_file(&game);
	print_block(&game);
	return 0;
}
