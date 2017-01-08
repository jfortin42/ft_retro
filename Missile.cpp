/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:20:14 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/08 17:29:39 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord, char direction)
	: AEntity(hp, speed, skin, weapon, coord), direction(direction)
{ return ; }

Missile::Missile(Missile const &src) : AEntity(src), direction(src.direction)
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
	(void)key;
    if (cnt_move++ >= speed)
    {
        cnt_move = 0;
		if (this->direction == 'N' && this->coord.y > 1)
			this->coord.y -= 1;
		else if (this->direction == 'S' && this->coord.y < height - 2)
			this->coord.y += 1;
		else if (this->direction == 'W' && this->coord.x > 1)
			this->coord.x -= 1;
		else if (this->direction == 'E' && this->coord.x < width - 2)
			this->coord.x += 1;
		else
			return (false);
	}
	return (true);
}

AEntity	*Missile::shoot()
{
	t_coord coordShoot;

	coordShoot.y = 0;
	coordShoot.x = 0;
	return (new Missile(1, 1, "o", NULL, coordShoot, this->direction));
}