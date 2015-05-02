/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arkanoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcassagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/02 12:02:06 by mcassagn          #+#    #+#             */
/*   Updated: 2015/05/02 12:18:41 by mcassagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARKANOID_H
# define ARKANOID_H

typedef enum	e_block_type
{
	EMPTY, EASY, MEDIUM, HARD, IMMORTAL, BONUS
}				t_block_type;

typedef enum	e_bonus_type
{
	BOARD_SPEED, BOARD_WIDTH, BALL_SPEED, MULTIBALL, HIDE
}				t_bonus_type;

typedef struct	s_vector_2d
{
	int			x;
	int			y;
	int			z;
}				t_vector_2d;

typedef struct	s_bonus
{
	t_vector_2d		vector;
	t_bonus_type	bonus_type;
	int				malus;
}				t_bonus;

typedef struct	s_block
{
	int				x;
	int				y;
	t_block_type	type;
	int				life;
	t_bonus			*bonus;
}				t_block;

typedef struct	s_board
{
	t_vector_2d		vector;
	int				width;
	int				speed;
	int				hide;
}				t_board;

typedef struct	s_game
{
	t_board		bord;

}				t_game;

#endif
