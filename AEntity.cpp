/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:01:52 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/14 18:16:01 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AEntity.hpp"

AEntity::AEntity(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord)
	: hp(hp), speed(speed), skin(skin), weapon(NULL), coord(coord)
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

void	AEntity::move(char direction)
{
	if (direction == 'N')
		this->coord.y -= this->speed;
	else if (direction == 'S')
		this->coord.y += this->speed;
	else if (direction == 'E')
		this->coord.x -= this->speed;
	else if (direction == 'W')
		this->coord.x += this->speed;
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