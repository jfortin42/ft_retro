/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 21:04:07 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/23 21:55:18 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Boss.hpp"

Boss::Boss(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, AWeapon *weapon, t_coord coord) : AEntity(hp, damageDeal, speed, score, skin, weapon, coord), _direction('E') {}

Boss::Boss(Boss const &src) : AEntity(src), _direction(src._direction) {}

Boss::~Boss()
{
    if (_weapon)
        delete _weapon;
}

Boss	        &Boss::operator=(Boss const &rhs)
{
    _weapon = rhs._weapon->clone();
    AEntity::operator=(rhs);
    _direction = rhs._direction;
    return (*this);
}

bool            Boss::move(unsigned int height, unsigned int width, int key)
{
    (void)height;
    (void)key;
    if (_cnt_move++ >= _speed)
    {
        _cnt_move = 0;
        if (_direction == 'E' && _coord.x + _skin_size.x < width - 1)
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
    if (!_weapon)
        throw(AEntity::NoWeaponEquippedException::NoWeaponEquippedException());
    return (_weapon->createMissile(*this, 'S'));
}