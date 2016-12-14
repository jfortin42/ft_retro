/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:04:18 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/14 17:30:30 by fsidler          ###   ########.fr       */
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