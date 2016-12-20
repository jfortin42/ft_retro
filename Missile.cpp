/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:20:14 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/20 20:06:20 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord, AEntity const &shooter, char direction)
	: AEntity(hp, speed, skin, weapon, coord), shooter(shooter), direction(direction)
{ return ; }

Missile::Missile(Missile const &src) : AEntity(src), shooter(src.shooter), direction(src.direction)
{
	*this = src;
}

Missile::~Missile() { return ; }

Missile	&Missile::operator=(Missile const &rhs)
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

bool	Missile::move(unsigned int height, unsigned int width, int key)
{
	//if (coord.y < height / 2)
	//	coord.y = height - 6;
	(void)key;// = 0;
	if (this->direction == 'N' && this->coord.y > this->speed / 2)
		this->coord.y -= (this->speed / 2);
	else if (this->direction == 'S' && this->coord.y < height - (this->speed / 2) - 3)
		this->coord.y += (this->speed / 2);
	else if (this->direction == 'E' && this->coord.x > this->speed)
		this->coord.x -= this->speed;
	else if (this->direction == 'W' && this->coord.x < width - this->speed - 6.5)
		this->coord.x += this->speed;
	else
		return (false);
	return (true);
}

AEntity	*Missile::shoot()
{
	t_coord coordShoot;

	coordShoot.y = 0;
	coordShoot.x = 0;
	return (new Missile(1, 1, "o", NULL, coordShoot, *this, this->direction));
}