/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 13:40:09 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/03 17:29:23 by mcassagn         ###   ########.fr       */
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

void		draw_board(t_game *game)
{
	float	x;
	float	y;

	x = (float)game->board.pos.x;
	x = (x - ((float)WIN_WIDTH / 2.0f));
	x = x / (WIN_WIDTH / 2);
	y = (float)game->board.pos.y;
	y = (y + ((float)WIN_HEIGHT / 2.0f));
	y = y / (WIN_HEIGHT / 2);
	glBegin(GL_LINES);
	glColor3f(0.9f, 0.5f, 0.3f);
	glVertex2f(x - (game->board.width / 2), y);
	glVertex2f(x + (game->board.width / 2), y);
	glEnd();
}

void		move_board(t_game *game, int sens)
{
	int	i;

	i = 0;
	if (sens)
	{
		while (i < game->board.speed && game->board.pos.x > 50)
		{
			--game->board.pos.x;
			++i;
		}
	}
	else if (game->board.pos.x < 1200)
	{
		while (i < game->board.speed && game->board.pos.x < 750)
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

	(void)mods;
	(void)scancode;
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
}

static void	init_ball(t_game *game)
{
	game->ball.speed = 500;
	game->ball.pos.x = 400;
	game->ball.pos.y = 400;
	game->ball.direction.x = 10;
	game->ball.direction.y = 5;
	game->ball.direction.z = 5;
	game->ball.rayon = WIN_WIDTH / 200;
}

static void	init_board(t_game *game)
{
	game->board.pos.x = 400;
	game->board.pos.y = -750;
	game->board.speed = 75;
	game->board.width = 0.3f;
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
	game->level_height = 5;
	game->level_width = 20;
	game->blocks = NULL;
	init_ball(game);
	init_board(game);
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
	game->dt = 1.0f;
	/*parse_files(&game);*/
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

void		draw_ball(t_game *game)
{
	int		i;
	float	theta;
	float	xy[2];
	float	c[2];

	c[0] = ((float)game->ball.pos.x - ((float)WIN_WIDTH / 2))
		/ (float)WIN_WIDTH;
	c[1] = ((float)game->ball.pos.y - ((float)WIN_HEIGHT / 2))
		/ (float)WIN_HEIGHT;
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

void		move_ball(t_game *game)
{
	game->ball.pos.x += game->ball.direction.x;
	if (game->ball.pos.x >= 1200 || game->ball.pos.x <= -400)
		game->ball.direction.x = -game->ball.direction.x;
	game->ball.pos.y += game->ball.direction.y;
	if (game->ball.pos.y >= 1200)
		game->ball.direction.y = -game->ball.direction.y;
}

static void	set_color(t_block_type type)
{
	if (type == BLOCK_EASY)
		glColor3f(0.0f, 1.0f, 0.0f);
	else if (type == BLOCK_MEDIUM)
		glColor3f(0.0f, 0.0f, 1.0f);
	else if (type == BLOCK_HARD)
		glColor3f(1.0f, 0.0f, 0.0f);
	else if (type == BLOCK_IMMORTAL)
		glColor3f(0.5f, 0.5f, 0.5f);
	else if (type == BLOCK_EMPTY)
		glColor3f(0.1f, 0.1f, 0.1f);
	else if (type == BLOCK_BONUS)
		glColor3f(0.7f, 0.7f, 0.7f);
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
	set_color(block->type);
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

	y = 0;
	while (y < game->level_height)
	{
		x = 0;
		while (x < game->level_width)
		{
			draw_block(game, &(game->blocks[y][x]));
			++x;
		}
		++y;
	}
}

void		update_time(t_game *game)
{
	game->last_time = game->time;
	game->time = glfwGetTime();
	game->dt = game->time - game->last_time;
}

void		ball_hit_block(t_block *block, t_ball *ball, t_game *game, int sens)
{
	static double	last_change = 0;

	game->score += 10;
	if (block->life != 0)
	{
		if (glfwGetTime() - last_change >= 0.5)
		{
			if (sens == 1)
				ball->direction.y = -ball->direction.y;
			else if (sens == 2)
				ball->direction.x = -ball->direction.x;
			else if (sens == 3)
				ball->direction.y = -ball->direction.y;
			else if (sens == 4)
				ball->direction.x = -ball->direction.x;
			last_change = glfwGetTime();
		}
	}
	--block->life;
	if (block->life <= 0)
		block->type = BLOCK_EMPTY;
}

void		get_block_maxi(t_block *block, float point[4][2], t_game *game)
{
	float	width;
	float	height;
	float	tmp_x;
	float	tmp_y;

	tmp_x = (float)block->pos.x * game->offset_x;
	tmp_y = ((float)block->pos.y + 1.0f) * game->offset_y;
	tmp_x = (tmp_x - ((float)WIN_WIDTH / 2.0f));
	tmp_x = tmp_x / (WIN_WIDTH / 2);
	tmp_y = (tmp_y - ((float)WIN_HEIGHT / 2.0f));
	tmp_y = -tmp_y / (WIN_HEIGHT / 2);
	width = (float)game->offset_x / (float)WIN_WIDTH * 2.0f;
	height = (float)game->offset_y / (float)WIN_HEIGHT * 2.0f;
	point[0][0] = tmp_x;
	point[0][1] = tmp_y;
	point[1][0] = tmp_x + width;
	point[1][1] = tmp_y;
	point[2][0] = tmp_x;
	point[2][1] = tmp_y - height;
	point[3][0] = tmp_x + width;
	point[3][1] = tmp_y - height;
}

void		get_ball_maxi(t_ball *ball, float point[4][2])
{
	float	tmp_x;
	float	tmp_y;
	float	t;
	float	theta;

	tmp_x = ((float)ball->pos.x - ((float)WIN_WIDTH / 2)) / (float)WIN_WIDTH;
	tmp_y = ((float)ball->pos.y - ((float)WIN_HEIGHT / 2)) / (float)WIN_HEIGHT;
	theta = 2.0f * 3.1415926f * 100.0f / 100.0f;
	t = (float)ball->rayon / ((float)WIN_WIDTH / 4) * sinf(theta);
	point[0][0] = tmp_x;
	point[0][1] = tmp_y + t;
	theta = 2.0f * 3.1415926f * 25.0f / 100.0f;
	t = (float)ball->rayon / ((float)WIN_HEIGHT / 4) * cosf(theta);
	point[1][0] = tmp_x + t;
	point[1][1] = tmp_y;
	theta = 2.0f * 3.1415926f * 50.0f / 100.0f;
	t = (float)ball->rayon / ((float)WIN_HEIGHT / 4) * sinf(theta);
	point[2][0] = tmp_x;
	point[2][1] = tmp_y - t;
	theta = 2.0f * 3.1415926f * 75.0f / 100.0f;
	t = (float)ball->rayon / ((float)WIN_HEIGHT / 4) * cosf(theta);
	point[3][0] = tmp_x - t;
	point[3][1] = tmp_y;
}

int			check_block_collision(t_block *block, t_ball *ball, t_game *game)
{
	float	p_ball[4][2];
	float	p_block[4][2];

	get_ball_maxi(ball, p_ball);
	get_block_maxi(block, p_block, game);
	if (p_ball[0][1] > p_block[2][1] && p_ball[0][0] > p_block[2][0]
			&& p_ball[0][0] < p_block[3][0])
		return (1);
	else if (p_ball[3][0] < p_block[3][0] && p_ball[3][1] < p_block[3][1]
			&& p_ball[3][1] > p_block[1][1])
		return (2);
	else if (p_ball[1][0] > p_block[2][0] && p_ball[1][1] < p_block[2][1] &&
			p_ball[1][1] > p_block[0][1])
		return (3);
	else if (p_ball[2][1] > p_block[0][1] && p_ball[2][0] > p_block[0][0] &&
			p_ball[2][0] < p_block[1][0])
		return (4);
	return (0);
}

void		check_blocks_collision(t_game *game)
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
			block = &(game->blocks[i][j]);
			if (block->life > 0 && block->type != BLOCK_EMPTY)
			{
				if ((ret = check_block_collision(block, ball, game)))
					ball_hit_block(block, ball, game, ret);
			}
			++j;
		}
		++i;
	}
}

int			ball_hit_board(t_game *game)
{
	float			south[2];
	float			board[2];
	float			tmp[2];

	south[0] = ((float)game->ball.pos.x - ((float)WIN_WIDTH / 2))
		/ (float)WIN_WIDTH;
	south[1] = ((float)game->ball.pos.y - ((float)WIN_HEIGHT / 2))
		/ (float)WIN_HEIGHT;
	tmp[0] = 2.0f * 3.1415926f * 50.0f / 100.0f;
	tmp[1] = (float)game->ball.rayon / ((float)WIN_HEIGHT / 4) * sinf(tmp[0]);
	south[1] -= tmp[1];
	board[0] = ((float)game->board.pos.x - ((float)WIN_WIDTH))
		/ (float)WIN_WIDTH;
	board[1] = ((float)game->board.pos.y) / (float)WIN_HEIGHT + 0.1f;
	board[0] = board[0] * 2.0f;
	board[0] += 1.0f;
	if (south[0] >= board[0] - (game->board.width / 2) && south[0] <= board[0]
			+ (game->board.width / 2) && south[1] <= board[1])
		return (1);
	return (0);
}

void		check_collision(t_game *game)
{
	t_ball			*ball;
	static double	last_change = 0;

	ball = &(game->ball);
	if (ball_hit_board(game) && glfwGetTime() - last_change >= 0.4)
	{
		game->ball.direction.y *= -1;
		last_change = glfwGetTime();
	}
	check_blocks_collision(game);
	if (ball->pos.y <= -410)
	{
		--game->life;
		ball->pos.x = 400;
		ball->pos.y = 400;
		usleep(300000);
	}
}

int			rest_destuctible_block(t_game *game)
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

void		check_game_state(t_game *game)
{
	if (!rest_destuctible_block(game))
		game->win = 1;
	if (game->life <= 0)
		game->win = -1;
}

static void	draw_stuff(t_game *game)
{
	draw_board(game);
	draw_blocks(game);
	draw_ball(game);
}

static void	app(t_game *game)
{
	int	width;
	int	height;

	init_glfw(game);
	while (!glfwWindowShouldClose(game->window))
	{
		update_time(game);
		if (game->started && !game->paused && !game->win)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
			glfwGetFramebufferSize(game->window, &width, &height);
			move_ball(game);
			draw_stuff(game);
			check_collision(game);
			check_game_state(game);
			usleep(12500);
		}
		glfwSwapBuffers(game->window);
		glfwPollEvents();
		usleep(100);
	}
}

int			main(int ac, char **av)
{
	t_game	*game;

	(void)ac;
	game = uf_get_game();
	create_game(game, av[1]);
	app(game);
	terminate_glfw(game);
	return (0);
}
