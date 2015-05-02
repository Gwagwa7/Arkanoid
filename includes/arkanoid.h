/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arkanoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 12:02:06 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/02 13:38:38 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARKANOID_H
# define ARKANOID_H

# include <GLFW/glfw3.h>

# define WIN_WIDTH	800
# define WIN_HEIGHT	600

typedef enum	e_block_type
{
	BLOCK_EMPTY, BLOCK_EASY, BLOCK_MEDIUM, BLOCK_HARD, BLOCK_IMMORTAL,\
	BLOCK_BONUS
}				t_block_type;

typedef enum	e_dificulty
{
	EASY, MEDIUM, HARD
}				t_dificulty;

typedef enum	e_bonus_type
{
	BOARD_SPEED, BOARD_WIDTH, BALL_SPEED, MULTIBALL, HIDE, SCORE
}				t_bonus_type;

typedef struct	s_point_2d
{
	int	x;
	int	y;
}				t_point_2d;

typedef struct	s_vector_2d
{
	t_point_2d		pos;
	int				direction;
}				t_vector_2d;

typedef struct	s_bonus
{
	t_vector_2d		bonus;
	t_bonus_type	bonus_type;
	int				malus;
}				t_bonus;

typedef struct	s_block
{
	t_point_2d		pos;
	t_block_type	type;
	int				life;
	t_bonus			*bonus;
}				t_block;

typedef struct	s_board
{
	t_vector_2d		board;
	int				width;
	int				speed;
	int				hide;
}				t_board;

typedef struct	s_ball
{
	t_vector_2d		ball;
	int				speed;
}				t_ball;

typedef struct	s_level
{
	int				width;
	int				height;
	t_block			**blocks;
	struct s_level	*next;
	struct s_level	*prev;
}				t_level;

typedef struct	s_game
{
	t_board			board;
	t_level			*levels;
	t_block			**blocks;
	t_ball			*ball;
	char			*player_name;
	int				life;
	int				score;
	int				paused;
	double			time;
	double			last_time;
	t_dificulty		difficulty;
	GLFWwindow		*window;
}				t_game;

typedef enum	e_collision_type
{
	PLAYER_COLLISION, BLOCK_COLLISION, WALL_COLLISION, GOAL_COLLISION,\
	NO_COLLISION
}				t_collision_type;

typedef struct	s_collision
{
	t_collision_type	type;
	t_block				*collided_block;
}				t_collision;

void		init_game(t_game *game, const char *player_name);
void		parse_file(t_game *game);

void		draw_start_window(t_game *game);
void		draw_level_chooser(t_game *game, t_point_2d pos);
void		draw_difficulty_chooser(t_game *game, t_point_2d pos);
void		change_game_level(t_game *game, int sens);
void		change_game_difficulty(t_game *game, int sens);
void		draw_start_button(t_game *game, t_point_2d pos);
void		launch_game(t_game *game);

void		draw_player_name(t_game *game, t_point_2d pos);

void		draw_pause_window(t_game *game);
void		draw_end_window(t_game *game);
void		draw_restart_button(t_game *game, t_point_2d pos);
void		draw_final_score(t_game *game);
void		move_ball(t_game *game);
void		move_board(t_game *game);
void		move_bonus(t_game *game);
t_collision	check_collision(t_game *game);
void		block_take_damage(t_game *game, int ind);
void		board_take_bonus(t_game *game, int ind);
void		player_lose_life(t_game *game);
void		check_win(t_game *game);

#endif
