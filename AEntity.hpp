/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:02:23 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/10 17:52:38 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_ENTITY_HPP
# define A_ENTITY_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <ncurses.h>
# include <unistd.h>
# include <string>

class   				AWeapon;

typedef struct			s_coord
{
	unsigned int		x;
	unsigned int		y;
}						t_coord;

class					AEntity {

public:

typedef struct          s_entityList
{
	AEntity             *entity;
	struct s_entityList *next;
}                       t_entityList;

	AEntity(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, AWeapon *weapon, t_coord coord);
	AEntity(AEntity const &src);
	virtual ~AEntity();

	AEntity					&operator=(AEntity const &rhs);
	
	void					equipWeapon(AWeapon *weapon);

	virtual bool			move(unsigned int height, unsigned int width, int key) = 0;
	virtual t_entityList	*shoot(int key) = 0;

	virtual unsigned int	takeDamage(AEntity const &attacker, WINDOW *win);

	void					displaySkin(WINDOW *win, unsigned int color_nb) const;

	unsigned int			getHp() const;
	unsigned int			getDamageDeal() const;
	unsigned int			getScore() const;
	t_coord					getCoord() const;
	static t_coord			getSkinSize(std::string skin);

	t_coord	const			_skin_size;

protected:
	class	NoWeaponEquippedException : public std::exception {
		public:
			NoWeaponEquippedException();
			NoWeaponEquippedException(NoWeaponEquippedException const &src);
			virtual ~NoWeaponEquippedException() throw();

			NoWeaponEquippedException	&operator=(NoWeaponEquippedException const &rhs);

			char const					*what(void) const throw();
	};
	
	unsigned int			_hp;
	unsigned int			_damageDeal;
	unsigned int			_speed;
	unsigned int			_score;
	clock_t					_last_move;
	std::string				_skin;
	AWeapon					*_weapon;
	t_coord					_coord;

private:
	AEntity();

};

#endif