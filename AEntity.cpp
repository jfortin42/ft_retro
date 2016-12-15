/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:01:52 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/15 16:11:29 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AEntity.hpp"

AEntity::AEntity(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord)
	: hp(hp), speed(speed), skin(skin), weapon(weapon), coord(coord)
{
	//temporaire (retirer plus tard)
	(void)weapon;
	//temporaire
}

AEntity::AEntity(AEntity const &src)
{
	*this = src;
}

//temporaire??
AEntity::AEntity() { return ; }
//temporaire??

AEntity::~AEntity()
{}

AEntity	&AEntity::operator=(AEntity const &rhs)
{
	if (this != &rhs)
	{
		hp = rhs.hp;
		speed = rhs.speed;
		skin = rhs.skin;
		weapon = rhs.weapon;
		coord = rhs.coord;
	}
	return (*this);
}

void	AEntity::move(int key)
{
	unsigned int	height;
	unsigned int	width;
	
	getmaxyx(stdscr, height, width);
	//if (coord.y < height / 2)
	//	coord.y = height - 6;
	if (key == KEY_UP)
		this->coord.y -= (this->coord.y > /*(height / 2) + */(this->speed / 2)) ? (this->speed / 2) : 0;
	else if (key == KEY_DOWN)
		this->coord.y += (this->coord.y < height - (this->speed / 2) - 3) ? (this->speed / 2) : 0;
	else if (key == KEY_LEFT)
		this->coord.x -= (this->coord.x > this->speed) ? this->speed : 0;
	else if (key == KEY_RIGHT)
		this->coord.x += (this->coord.x < width - this->speed - 6.5) ? this->speed : 0;
}

/*Missile	*AEntity::shoot()
{
	if (this->weapon)
		return (this->weapon->createMissile());
	return (NULL);
}*/

/*void	AEntity::takeDamage(AEntity const &attcker)
{
	
}*/

void	AEntity::displaySkin() const
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = this->coord.y;
	wattron(stdscr, COLOR_PAIR(3));
	while (skin.c_str()[i])
	{
		x = 0;
		while (skin.c_str()[i] && skin.c_str()[i] != '\n')
			mvwaddch(stdscr, y, coord.x + (x++), skin.c_str()[i++]);
		i++;
		y++;
	}
	wattroff(stdscr, COLOR_PAIR(3));
}