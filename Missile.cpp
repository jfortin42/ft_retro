/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:20:14 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/11 22:19:39 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord, char direction) : AEntity(hp, damageDeal, speed, 0, skin, weapon, coord), direction(direction) {}

Missile::Missile(Missile const &src) : AEntity(src), direction(src.direction) {}

Missile::~Missile() {}

Missile		&Missile::operator=(Missile const &rhs)
{
	_weapon = rhs._weapon->clone();
	AEntity::operator=(rhs);
	return (*this);
}

bool		Missile::move(unsigned int height, unsigned int width, int key)
{
	(void)key;
    if (_cnt_move++ >= _speed)
    {
        _cnt_move = 0;
		if (direction == 'N' && _coord.y > 1)
			_coord.y -= 1;
		else if (direction == 'S' && _coord.y + _skin_size.y < height)
			_coord.y += 1;
		else if (direction == 'W' && _coord.x > 1)
			_coord.x -= 1;
		else if (direction == 'E' && _coord.x  + _skin_size.x < width)
			_coord.x += 1;
		else
			return (false);
	}
	return (true);
}

AEntity	*Missile::shoot()
{
    if (!_weapon)
        throw(AEntity::NoWeaponEquippedException::NoWeaponEquippedException());
    return (_weapon->createMissile(*this, 'N'));
}