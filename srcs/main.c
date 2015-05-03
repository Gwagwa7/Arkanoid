/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 13:40:09 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 11:18:04 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>

#include <arkanoid.h>
#include <libft.h>

static t_game	*uf_get_game(void)
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

static void error_callback(int error, const char *description)
{
	fputs(description, stderr);
}

void	draw_board(t_game *game)
{
	float	cx;
	float	y;

	y = (float)game->board.pos.y / (float)WIN_HEIGHT;
	glBegin(GL_LINES);
	glColor3f(0.9f, 0.5f, 0.3f);
	cx = (float)game->board.pos.x / (float)WIN_WIDTH;
	glVertex2f(cx - (game->board.width / 2), y);
	glVertex2f(cx + (game->board.width / 2), y);
	glEnd();
}

void	move_board(t_game *game, int sens)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	if (sens)
	{
		while (i < game->board.speed && game->board.pos.x > -650)
		{
			--game->board.pos.x;
			++i;
		}
	}
	else if (game->board.pos.x < 650)
	{
		while (i < game->board.speed && game->board.pos.x < 650)
		{
			++game->board.pos.x;
			++i;
		}
	}
}

static void	key_callback(GLFWwindow *window,\
		int key, int scancode, int action, int mods)
{
	t_game *game;

	game = uf_get_game();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_LEFT)
		move_board(game, 1);
	else if (key == GLFW_KEY_RIGHT)
		move_board(game, 0);
	else if (key == GLFW_KEY_P)
		game->paused = 1;
	else if (key == GLFW_KEY_O)
		game->paused = 0;
	printf("Paused = %d\n", game->paused);
}

static void	create_game(t_game *game, char *player_name)
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

static void	print_game_state(t_game game)
{
	ft_printf("Game logically created let's check !\n");
	ft_printf("Game->player_name = %s\n", game.player_name);
	ft_printf("Game->life = %d\n", game.life);
	ft_printf("Game->score = %d\n", game.score);
	ft_printf("Game->paused = %d\n", game.paused);
	printf("Game->time = %f\n", game.time);
	printf("Game->last_time = %f\n", game.last_time);
	ft_printf("Game->difficulty = %d\n", game.difficulty);
}

static void	init_glfw(t_game *game)
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

static void	terminate_glfw(t_game *game)
{
	glfwDestroyWindow(game->window);
	glfwTerminate();
	exit(1);
}

void	draw_ball(t_game *game)
{
	int		i;
	float	theta;
	float	xy[2];
	float	c[2];

	c[0] = (float)game->ball.pos.x / (float)WIN_WIDTH;
	c[1] = (float)game->ball.pos.y / (float)WIN_HEIGHT;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	i = 0;
	while (i <= 100)
	{
		theta = 2.0f * 3.1415926f * (float)i / (float)100;
		xy[0] = (float)game->ball.rayon / ((float)WIN_WIDTH / 4) * cosf(theta);
		xy[1] = (float)game->ball.rayon / ((float)WIN_WIDTH / 4) * sinf(theta);
		glVertex2f(xy[0] + c[0], xy[1] + c[1]);
		i++;
	}
	glEnd(); 
}

void	move_ball(t_game *game)
{
	game->ball.pos.x += game->ball.direction.x;
	if (game->ball.pos.x >= 800 || game->ball.pos.x <= -800)
		game->ball.direction.x = -game->ball.direction.x;
	game->ball.pos.y += game->ball.direction.y;
	if (game->ball.pos.y >= 800)
		game->ball.direction.y = -game->ball.direction.y;
}

void		draw_block(t_game *game, t_block *block)
{
	float	x;
	float	y;
	float	width;
	float	height;

	x = (float)block->pos.x * game->offset_x;
	y = ((float)block->pos.y + 2.0f) * game->offset_y;
	x = (x - ((float)WIN_WIDTH / 2.0f));
	x = x / (WIN_WIDTH / 2);
	y = (y - ((float)WIN_HEIGHT / 2.0f));
	y = -y / (WIN_HEIGHT / 2);
	glBegin(GL_QUADS);
	if (block->type == BLOCK_EASY)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if (block->type == BLOCK_MEDIUM)
		glColor3f(0.0f, 0.0f, 1.0f);
	else if (block->type == BLOCK_HARD)
		glColor3f(1.0f, 0.0f, 0.0f);
	else if (block->type == BLOCK_IMMORTAL)
		glColor3f(0.5f, 0.5f, 0.5f);
	else if (block->type == BLOCK_EMPTY)
		glColor3f(0.0f, 0.0f, 0.0f);
	else if (block->type == BLOCK_BONUS)
		glColor3f(0.7f, 0.7f, 0.7f);
	width = (float)game->offset_x / (float)WIN_WIDTH * 2.0f;
	height = (float)game->offset_y / (float)WIN_HEIGHT * 2.0f;
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glEnd();
}

void		draw_blocks(t_game *game)
{
	int		x;
	int		y;
	t_block	block;

	block.type = BLOCK_EASY;
	block.life = 3;
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 25)
		{
			block.pos.x = x;
			block.pos.y = y;
			draw_block(game, &block);
			if (block.type == BLOCK_EASY)
				block.type = BLOCK_MEDIUM;
			else if (block.type == BLOCK_MEDIUM)
				block.type = BLOCK_HARD;
			else if (block.type == BLOCK_HARD)
				block.type = BLOCK_IMMORTAL;
			else if (block.type == BLOCK_IMMORTAL)
				block.type = BLOCK_EMPTY;
			else if (block.type == BLOCK_EMPTY)
				block.type = BLOCK_BONUS;
			else if (block.type == BLOCK_BONUS)
				block.type = BLOCK_EASY;
			++x;
		}
		++y;
	}
}

void	update_time(t_game *game)
{
	game->last_time = game->time;
	game->time = glfwGetTime();
	game->dt = game->time - game->last_time;
}

void	ball_hit_block(t_block *block, t_ball *ball, t_game *game)
{
	game->score += 10;
	--block->life;
	if (block->life != 0)
	{
		ball->direction.x = -ball->direction.x;
		ball->direction.y = -ball->direction.y;
	}
	else
		block->type = BLOCK_EMPTY;
}

int		check_block_collision(t_block *block, t_ball *ball, t_game *game)
{
	int	p_ball[4][2];
	int	p_block[4][2];

	// North
	p_ball[0][0] = ball->pos.x;
	p_ball[0][1] = ball->pos.y + ball->rayon;
	// East
	p_ball[1][0] = ball->pos.x + ball->rayon;
	p_ball[1][1] = ball->pos.y;
	// South
	p_ball[2][0] = ball->pos.x;
	p_ball[2][1] = ball->pos.y - ball->rayon;
	// West
	p_ball[3][0] = ball->pos.x - ball->rayon;
	p_ball[3][1] = ball->pos.y;
	// Top left
	p_block[0][0] = block->pos.x;
	p_block[0][1] = block->pos.y;
	// Top right
	p_block[1][0] = block->pos.x + game->offset_x;
	p_block[1][1] = block->pos.y;
	// Bottom left
	p_block[2][0] = block->pos.x;
	p_block[2][1] = block->pos.y - game->offset_y;
	// Bottom right
	p_block[3][0] = block->pos.x + game->offset_x;
	p_block[3][1] = block->pos.y - game->offset_y;

	if (p_ball[0][1] > p_block[2][1] && p_ball[0][0] > p_block[2][0] && p_ball[0][0] < p_block[3][0])
	{
		// hit by Bottom
		return (1);
	}
	else if (p_ball[3][0] < p_block[3][0] && p_ball[3][1] > p_block[3][1] && p_ball[3][1] < p_block[1][1])
	{
		// Hit by right
		return (1);
	}
	else if (p_ball[1][0] > p_block[2][0] && p_ball[1][1] > p_block[2][1] && p_ball[1][1] < p_block[0][1])
	{
		// Hit by left
		return (3);
	}
	else if (p_ball[2][1] > p_block[0][1] && p_ball[2][0] > p_block[0][0] && p_ball[2][0] < p_ball[1][0])
	{
		// Hit by top
		return (4);
	}
/*	else if ()
	{
		// Hit by bottom right
		return (5);
	}
	else if ()
	{
		// Hit by bottom left
		return (6);
	}
	else if ()
	{
		// Hit by top left
		return (7);
	}
	else if ()
	{
		// Hit by top right
		return (9);
	}*/
	return (0);
}

void	check_blocks_collision(t_game *game)
{
	t_block	*block;
	t_ball	*ball;
	int		i;
	int		j;
	int		ret;

	ball = &game->ball;
	i = 0;
	while (i < game->level_height)
	{
		j = 0;
		while (j < game->level_width)
		{
			block = &(game->blocks[j][i]);
			if (block->life > 0 && block->type != BLOCK_EMPTY)
			{
				if ((ret = check_block_collision(block, ball, game)))
				{
//					ball_hit_block(block, ball, game);
					printf("Block %d %d hit at %d\n", block->pos.x, block->pos.y, ret);
				}
			}
			++j;
		}
		++i;
	}
}

void	check_collision(t_game *game)
{
	t_block	*block;
	t_ball	*ball;

	ball = &(game->ball);
	if (ball->pos.y < -750)
	{
		--game->life;
		printf("You have again %d lives !\n", game->life);
		ball->pos.x = 0;
		ball->pos.y = 0;
		return ;
	}
	/*	if (ball_hit_board(game))
		{
		rebounce_ball(game);
		}*/
	check_blocks_collision(game);
}

	int		rest_destuctible_block(t_game *game)
	{
		t_block	*block;
		int		i;
		int		j;

		i = 0;
		while (i < game->level_width)
		{
			j = 0;
			while (j < game->level_height)
			{
				block = &(game->blocks[j][i]);
				if (block->type != BLOCK_IMMORTAL && block->life > 0)
					return (1);
				++j;
			}
			++i;
		}
		return (0);
	}

	void	check_game_state(t_game *game)
	{
		/*	if (!rest_destuctible_block(game))
			game->win = 1;*/
		if (game->life <= 0)
			game->win = -1;
	}

	void	draw_start_window(t_game *game)
	{
		/*	draw_player_name(game);
			draw_level_chooser(game);
			draw_start_button(game);*/
	}

	void	draw_end_window(t_game *game)
	{
		/*	if (game->win == 1)
			draw_string("Win!");
			else
			draw_string("Lose!");
			draw_player_name(game);
			draw_score(game);*/
		glfwSwapBuffers(game->window);
		game->paused = 0;
		game->started = 0;
		game->win = 0;
		game->score = 0;
		sleep(5);
	}

	static void	app(t_game *game)
	{
		int	width;
		int	height;

		init_glfw(game);
		while (!glfwWindowShouldClose(game->window))
		{
			update_time(game);
			/*		if (!game->started)
					draw_start_window(game);
					else */if (game->started && !game->paused && !game->win)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
				glfwGetFramebufferSize(game->window, &width, &height);
				draw_blocks(game);
				move_ball(game);
				draw_ball(game);
				draw_board(game);
				check_collision(game);
				check_game_state(game);
			}
			/*		else if (!game->win)
					draw_end_window(game);*/
			glfwSwapBuffers(game->window);
			glfwPollEvents();
			usleep(100);
		}
	}

	int		main(int ac, char **av)
	{
		t_game	*game;

		game = uf_get_game();
		create_game(game, av[1]);
		app(game);
		terminate_glfw(game);
		return (0);
	}
