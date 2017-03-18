/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 21:04:07 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/18 16:49:58 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Boss.hpp"

Boss::Boss(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, Weapon *weapon, t_coord coord) : AEntity(hp, damageDeal, speed, score, skin, weapon, coord, 'S'), _direction('E') {}

Boss::Boss(Boss const &src) : AEntity(src), _direction(src._direction) {}

Boss::~Boss() {}

Boss	        &Boss::operator=(Boss const &rhs)
{
    AEntity::operator=(rhs);
    _direction = rhs._direction;
    return (*this);
}

bool            Boss::move(unsigned int height, unsigned int width, int key)
{
    (void)height;
    (void)key;
    if (Game::checkTime(_speed, _lastMove))
    {
        if (_direction == 'E' && _coord.x + _skinSize.x < width - 1)
            _coord.x += 1;
        else
            _direction = 'W';
        if (_direction == 'W' && _coord.x > 1)
            _coord.x -= 1;
        else
            _direction = 'E';
    }
    return (true);
}

AEntity::t_entityList    *Boss::shoot(int key)
{
    (void)key;
    if (!_weaponList)
        throw(AEntity::NoWeaponEquippedException::NoWeaponEquippedException());
    t_weaponList            *tmp = _weaponList;
    AEntity::t_entityList   *listOfMissile = NULL;
    while (tmp)
    {
        Game::pushInList(listOfMissile, tmp->weapon->createMissile(*this,'S'));
        tmp = tmp->next;
    }
    return (listOfMissile);
}