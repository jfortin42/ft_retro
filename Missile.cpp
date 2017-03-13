/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:20:14 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/13 19:33:01 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"
#include "Game.hpp"

Missile::Missile(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, Weapon *weapon, t_coord coord, char direction1, char direction2) : AEntity(hp, damageDeal, speed, score, skin, weapon, coord), _direction1(direction1), _direction2(direction2) {}

Missile::Missile(Missile const &src) : AEntity(src), _direction1(src._direction1), _direction2(src._direction2) {}

Missile::~Missile() {}

Missile					&Missile::operator=(Missile const &rhs)
{
	_direction1 = rhs._direction1;
	_direction2 = rhs._direction2;
	AEntity::operator=(rhs);
	return (*this);
}

bool					Missile::move(unsigned int height, unsigned int width, int key)
{
	(void)key;
    if (Game::checkTime(_speed, _lastMove))
    {
		if (_direction1 == 'N' && _coord.y > 2)
			_coord.y -= 1;
		else if (_direction1 == 'S' && _coord.y + _skinSize.y < height - 2)
			_coord.y += 1;
		else if (_direction1 == 'W' && _coord.x > 2)
			_coord.x -= 1;
		else if (_direction1 == 'E' && _coord.x  + _skinSize.x < width - 2)
			_coord.x += 1;
		else
			return (false);
	}
	return (true);
}

AEntity::t_entityList	*Missile::shoot(int key)
{
	(void)key;
    if (!_weaponList)
        throw(AEntity::NoWeaponEquippedException::NoWeaponEquippedException());
    t_weaponList            *tmp = _weaponList;
    AEntity::t_entityList   *listOfMissile = NULL;
    while (tmp)
    {
        Game::pushInList(listOfMissile, tmp->weapon->createMissile(*this, _direction2));
        tmp = tmp->next;
    }
    return (listOfMissile);
}