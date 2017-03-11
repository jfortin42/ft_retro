/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:04:18 by fsidler           #+#    #+#             */
/*   Updated: 2017/03/11 13:22:56 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, Weapon *weapon, t_coord coord, int keyUp, int keyDown, int keyLeft, int keyRight, int keyShoot) : AEntity(hp, damageDeal, speed, 0, skin, weapon, coord), _keyUp(keyUp), _keyDown(keyDown), _keyLeft(keyLeft), _keyRight(keyRight), _keyShoot(keyShoot) {}

Player::Player(Player const &src) : AEntity(src) {}

Player::~Player()
{
    if (_weapon)
        delete _weapon;
}

Player                  &Player::operator=(Player const &rhs)
{
    _weapon = rhs._weapon->clone();
    _keyUp = rhs._keyUp;
    _keyDown = rhs._keyDown;
    _keyLeft = rhs._keyLeft;
    _keyRight = rhs._keyRight;
    _keyShoot = rhs._keyShoot;
    AEntity::operator=(rhs);
    return (*this);
}

bool                    Player::move(unsigned int height, unsigned int width, int key)
{
    if (key == _keyUp && _coord.y > _speed / 2)
        _coord.y -= _speed / 2;
	else if (key == _keyDown && _coord.y < height - _speed / 2 - _skinSize.y)
        _coord.y += _speed / 2;
	else if (key == _keyLeft && _coord.x > _speed / 2)
        _coord.x -= _speed;
	else if (key == _keyRight && _coord.x < width - _speed / 2 - _skinSize.x - 1)
        _coord.x += _speed;
    return (true);
}

AEntity::t_entityList    *Player::shoot(int key)
{
    if (key == _keyShoot)
    {
        if (!_weapon)
            throw(AEntity::NoWeaponEquippedException::NoWeaponEquippedException());
        return (_weapon->createMissile(*this, 'N'));
    }
    return (NULL);
}

unsigned int	        Player::takeDamage(AEntity const &attacker, WINDOW *win)
{
	wattron(win, A_BLINK);
	displaySkin(win, 3);
	usleep(500000);
	wattroff(win, A_BLINK);
	_hp -= _hp < attacker.getDamageDeal() ? _hp : attacker.getDamageDeal();
	return (_hp);
}