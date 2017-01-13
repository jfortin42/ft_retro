/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:20:14 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/13 19:39:00 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord, char direction) : AEntity(hp, damageDeal, speed, skin, weapon, coord), direction(direction) {}

Missile::Missile(Missile const &src) : AEntity(src), direction(src.direction) {}

Missile::~Missile() {}

Missile		&Missile::operator=(Missile const &rhs)
{
	AEntity::operator=(rhs);
	return (*this);
	//OU ALORS
	/*if (this != &rhs)
	{
		_hp = rhs._hp;
		_damageDeal = rhs._damageDeal;
		_speed = rhs._speed;
		_cnt_move = rhs._cnt_move;
		_skin = rhs._skin;
		//_weapon = rhs._weapon;//DEEPCOPY!
		_coord = rhs._coord;
	}
	return (*this);*/
}

bool		Missile::move(unsigned int height, unsigned int width, int key)
{
	(void)key;
    if (_cnt_move++ >= _speed)
    {
        _cnt_move = 0;
		if (direction == 'N' && _coord.y > 1)
			_coord.y -= 1;
		else if (direction == 'S' && _coord.y < height - 2)
			_coord.y += 1;
		else if (direction == 'W' && _coord.x > 1)
			_coord.x -= 1;
		else if (direction == 'E' && _coord.x < width - 2)
			_coord.x += 1;
		else
			return (false);
	}
	return (true);
}

AEntity	*Missile::shoot()
{
	//a changer
	/*t_coord coordShoot;

	coordShoot.y = 0;
	coordShoot.x = 0;
	return (new Missile(1, 1, 1, "o", NULL, coordShoot, _direction));*/
	return (NULL);
}