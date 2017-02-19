/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:04:18 by fsidler           #+#    #+#             */
/*   Updated: 2017/02/19 19:07:42 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord) : AEntity(hp, damageDeal, speed, 0, skin, weapon, coord) {}

Player::Player(Player const &src) : AEntity(src) {}

Player::~Player()
{
    if (_weapon)
        delete _weapon;
}

Player          &Player::operator=(Player const &rhs)
{
    _weapon = rhs._weapon->clone();
    AEntity::operator=(rhs);
    return (*this);
}

bool            Player::move(unsigned int height, unsigned int width, int key)
{
    if (key == KEY_UP && _coord.y > _speed / 2)
        _coord.y -= _speed / 2;
	else if (key == KEY_DOWN && _coord.y < height - _speed / 2 - _skin_size.y)
        _coord.y += _speed / 2;
	else if (key == KEY_LEFT && _coord.x > _speed / 2)
        _coord.x -= _speed;
	else if (key == KEY_RIGHT && _coord.x < width - _speed / 2 - _skin_size.x - 1)
        _coord.x += _speed;
    return (true);
}

AEntity::t_entityList    *Player::shoot()
{
    if (!_weapon)
        throw(AEntity::NoWeaponEquippedException::NoWeaponEquippedException());
    return (_weapon->createMissile(*this, 'N'));
}

unsigned int	Player::takeDamage(AEntity const &attacker, WINDOW *win)
{
	wattron(win, A_BLINK);
	displaySkin(win);
	usleep(500000);
	wattroff(win, A_BLINK);
	_hp -= _hp < attacker.getDamageDeal() ? _hp : attacker.getDamageDeal();
	return (_hp);
}