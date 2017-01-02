/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:04:18 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/03 00:13:54 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord) : 
AEntity(hp, speed, skin, weapon, coord)
{}

Player::Player(Player const &src)
{
    *this = src;
}

Player::~Player()
{}

Player          &Player::operator=(Player const &rhs)
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

bool            Player::move(unsigned int height, unsigned int width, int key)
{
	//if (coord.y < height / 2)
	//	coord.y = height - 6;

    // if (cnt_move++ >= speed)
    // {
    //     cnt_move = 0;
	if (key == KEY_UP && this->coord.y > this->speed / 2)
        this->coord.y -= this->speed / 2;
	else if (key == KEY_DOWN && this->coord.y < height - this->speed / 2 - sizeSkin.y)
        this->coord.y += this->speed / 2;
	else if (key == KEY_LEFT && this->coord.x > this->speed / 2)
        this->coord.x -= this->speed;
	else if (key == KEY_RIGHT && this->coord.x < width - this->speed / 2 - sizeSkin.x)
        this->coord.x += this->speed;
    // }
    return (true);
}

AEntity         *Player::shoot()
{
    t_coord coordShoot;
    
    coordShoot.x = this->coord.x + this->sizeSkin.x / 2;
    coordShoot.y = this->coord.y - 1;
    return (new Missile(1, 100, "|", NULL, coordShoot, *this, 'N'));
}
