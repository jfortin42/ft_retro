/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:04:18 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/13 19:12:16 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord) : AEntity(hp, damageDeal, speed, skin, weapon, coord) {}

Player::Player(Player const &src) : AEntity(src) {}

Player::~Player() {}

Player          &Player::operator=(Player const &rhs)
{
    //(appel de l'operateur d'AEntity? possible//
    if (this != &rhs)
        *this = rhs;
    //??)
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
	}*/
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

AEntity         *Player::shoot()
{
    t_coord coordShoot;

    if (!_weapon)
        throw(AEntity::NoWeaponEquippedException::NoWeaponEquippedException());
    coordShoot.x = _coord.x + _skin_size.x / 2;
    coordShoot.y = _coord.y - 1;
    return (_weapon->createMissile(coordShoot, 'N'));
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