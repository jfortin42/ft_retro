/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:04:18 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/20 19:13:00 by jfortin          ###   ########.fr       */
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

void	Player::move(unsigned int height, unsigned int width, int key)
{
	//if (coord.y < height / 2)
	//	coord.y = height - 6;
	if (key == KEY_UP)
		this->coord.y -= (this->coord.y > /*(height / 2) + */(this->speed / 2)) ? (this->speed / 2) : 0;
	else if (key == KEY_DOWN)
		this->coord.y += (this->coord.y < height - (this->speed / 2) - 3) ? (this->speed / 2) : 0;
	else if (key == KEY_LEFT)
		this->coord.x -= (this->coord.x > this->speed) ? this->speed : 0;
	else if (key == KEY_RIGHT)
		this->coord.x += (this->coord.x < width - this->speed - 6.5) ? this->speed : 0;
}

AEntity         *Player::shoot()
{
    t_coord coordShoot;
    std::size_t length_max;
    std::size_t length_tmp;
    std::size_t index;

    index = 0;
    length_max = 0;
    length_tmp = 0;
    while (index < this->skin.length() - 1)
    {
        index += length_tmp + 1;
        if ((length_tmp = this->skin.find("\n", index + 1) - index) > this->skin.length())
        {
            length_tmp = this->skin.length() - index;
            length_max = (length_max < length_tmp) ? length_tmp : length_max;        
            break ;
        }
        length_max = (length_max < length_tmp) ? length_tmp : length_max;
    }
    length_max /= 2;
    coordShoot.x = this->coord.x + length_max;
    coordShoot.y = this->coord.y - 1;
    return (new Missile(1, 1, "|", NULL, coordShoot, *this, 'N'));
}
