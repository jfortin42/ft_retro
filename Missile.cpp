/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:20:14 by jfortin           #+#    #+#             */
/*   Updated: 2018/02/11 22:27:24 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"
#include "Game.hpp"

Missile::Missile(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, Weapon *weapon, t_coord coord, char direction_move, char direction_shoot) : AEntity(hp, damageDeal, speed, score, skin, weapon, coord, direction_shoot), _direction_move(direction_move), _direction_shoot(direction_shoot) {}

Missile::Missile(Missile const &src) : AEntity(src), _direction_move(src._direction_move), _direction_shoot(src._direction_shoot) {}

Missile::~Missile() {}

Missile					&Missile::operator=(Missile const &rhs)
{
	_direction_move = rhs._direction_move;
	_direction_shoot = rhs._direction_shoot;
	AEntity::operator=(rhs);
	return (*this);
}

bool					Missile::move(unsigned int height, unsigned int width, int key)
{
	(void)key;
    if (Game::checkTime(_speed, _lastMove))
    {
		if (_direction_move == 'N' && _coord.y > 2)
			_coord.y -= 1;
		else if (_direction_move == 'S' && _coord.y + _skinSize.y < height - 2)
			_coord.y += 1;
		else if (_direction_move == 'W' && _coord.x > 2)
			_coord.x -= 1;
		else if (_direction_move == 'E' && _coord.x  + _skinSize.x < width - 2)
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
        Game::pushInList(listOfMissile, tmp->weapon->createMissile(*this, _direction_shoot));
        tmp = tmp->next;
    }
    return (listOfMissile);
}