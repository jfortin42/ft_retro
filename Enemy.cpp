/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 18:06:28 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/13 19:39:17 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"

Enemy::Enemy(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord) : AEntity(hp, damageDeal, speed, skin, weapon, coord) {}

Enemy::Enemy(Enemy const &src) : AEntity(src) {}

Enemy::~Enemy() {}

Enemy	    &Enemy::operator=(Enemy const &rhs)
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
        //_weapon = rhs._weapon;//DEEP COPY!
        _coord = rhs._coord;
        _sizeSkin = rhs._skin_size;
	}
	return (*this);*/
}

bool        Enemy::move(unsigned int height, unsigned int width, int key)
{
    (void)width;
    (void)key;
    if (_cnt_move++ >= _speed)
    {
        _cnt_move = 0;
        if (_coord.y < height - _skin_size.y - 1)
            _coord.y += 1;
        else
            return (false);
    }
    return (true);
}

AEntity     *Enemy::shoot()
{
    t_coord coordShoot;
    
    coordShoot.x = _coord.x + _skin_size.x / 2;
    coordShoot.y = _coord.y + _skin_size.y + 1;
    return (_weapon->createMissile(coordShoot, 'S'));
}