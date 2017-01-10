/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 18:06:28 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/10 16:10:50 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"

Enemy::Enemy()
{}

Enemy::Enemy(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord)
	: AEntity(hp, damageDeal, speed, skin, weapon, coord)
{}

Enemy::Enemy(Enemy const &src)
{
	*this = src;
}

Enemy::~Enemy()
{}

Enemy	&Enemy::operator=(Enemy const &rhs)
{
	if (this != &rhs)
	{
        this->hp = rhs.hp;
        this->speed = rhs.speed;
        this->skin = rhs.skin;
        this->weapon = rhs.weapon;
        this->coord = rhs.coord;
	}
	return (*this);
}

bool            Enemy::move(unsigned int height, unsigned int width, int key)
{
    (void)width;
    (void)key;
    if (cnt_move++ >= speed)
    {
        cnt_move = 0;
        if (this->coord.y < height - sizeSkin.y - 1)
            this->coord.y += 1;
        else
            return (false);
    }
    return (true);
}

AEntity         *Enemy::shoot()
{
    t_coord coordShoot;
    
    coordShoot.x = this->coord.x + this->sizeSkin.x / 2;
    coordShoot.y = this->coord.y + this->sizeSkin.y + 1;
    return (weapon->createMissile(coordShoot, 'S'));
}

