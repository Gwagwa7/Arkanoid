#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <arkanoid.h>
#include <libft.h>

static t_game		*uf_get_game(void)
{
	static t_game	*game;

	if (game == NULL)
	{
		game = malloc(sizeof(*game));
		if (game == NULL)
			return (NULL);
	}
	return (game);
}


static void		key_callback(GLFWwindow *window,\
		int key, int scancode, int action, int mods)
{
	t_game *game;

	game = uf_get_game();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//else if (key == GLFW_KEY_LEFT)
	//move_board(game, 1);
	//else if (key == GLFW_KEY_RIGHT)
	//	move_board(game, 0);
	else if (key == GLFW_KEY_P)
		game->paused = 1;
	else if (key == GLFW_KEY_O)
		game->paused = 0;
	printf("Paused = %d\n", game->paused);
}


static void		terminate_glfw(t_game *game)
{
	glfwDestroyWindow(game->window);
	glfwTerminate();
	exit(1);
}


static void		create_game(t_game *game, char *player_name)
{
	game->life = 2;	
	game->score = 0;
	game->paused = 0;
	game->win = 0;
	game->time = 1;
	game->last_time = 1;
	game->difficulty = EASY;
	game->levels = NULL;
	game->level_height = 0;
	game->level_width = 0;
	game->blocks = NULL;
	game->ball.speed = 500;
	game->ball.pos.x = 1;
	game->ball.pos.y = 1;
	game->ball.direction.x = 10;
	game->ball.direction.y = 5;
	game->ball.direction.z = 5;
	game->ball.rayon = WIN_WIDTH / 200;
	game->board.pos.x = 0;
	game->board.pos.y = -750;
	game->board.speed = 150;
	game->board.width = 0.3f;
	game->started = 1;
	if (player_name)
		game->player_name = player_name;
	else
		game->player_name = ft_strdup("Player One\n");
	game->window = NULL;
	game->time = glfwGetTime();
	game->last_time = glfwGetTime();
	game->offset_x = 40;
	game->offset_y = 40;
	/*parse_files(&game);*/
}


static void		init_glfw(t_game *game)
{
	if (!glfwInit())
		exit(0);
	game->window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT,
			"Arkanoid", NULL, NULL);
	if (!game->window)
	{
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(game->window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(game->window, key_callback);
}





void	update_time(t_game *game)
{
	game->last_time = game->time;
	game->time = glfwGetTime();
	game->dt = game->time - game->last_time;
}



static void		app(t_game *game)
{
	int		width;
	int		height;

	init_glfw(game);
	while (!glfwWindowShouldClose(game->window))
	{
		update_time(game);
		if (game->started && !game->paused && !game->win)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
			glfwGetFramebufferSize(game->window, &width, &height);
			draw_score(1234567890, 1.8f, -0.1f);
		}
		glfwSwapBuffers(game->window);
		glfwPollEvents();
		usleep(100);
	}
}

int			main(int ac, char **av)
{
	t_game	*game;

	game = uf_get_game();
	create_game(game, av[1]);
	app(game);
	terminate_glfw(game);
	return (0);
}
