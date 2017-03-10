/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:51:42 by fsidler           #+#    #+#             */
/*   Updated: 2017/03/10 18:44:00 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AEntity.hpp"

AEntity::AEntity(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, AWeapon *weapon, t_coord coord) : _skin_size(getSkinSize(skin)), _hp(hp), _damageDeal(damageDeal), _speed(speed), _score(score), _last_move(0), _skin(skin), _weapon(weapon), _coord(coord)
{}

AEntity::AEntity(AEntity const &src) : _skin_size(src._skin_size), _hp(src._hp), _damageDeal(src._damageDeal), _speed(src._speed), _score(src._score), _last_move(0), _skin(src._skin), _weapon(src._weapon), _coord(src._coord)
{}

AEntity::~AEntity() {}

AEntity			&AEntity::operator=(AEntity const &rhs)
{
	if (this != &rhs)
	{
		_hp = rhs._hp;
		_damageDeal = rhs._damageDeal;
		_speed = rhs._speed;
		_score = rhs._score;
		_last_move = rhs._last_move;
		_skin = rhs._skin;
		_coord = rhs._coord;
	}
	return (*this);
}

void			AEntity::equipWeapon(AWeapon *weapon) { _weapon = weapon; }

unsigned int	AEntity::takeDamage(AEntity const &attacker, WINDOW *win)
{
	(void)win;
	_hp -= _hp < attacker.getDamageDeal() ? _hp : attacker.getDamageDeal();
	return (_hp);
}

void			AEntity::displaySkin(WINDOW *win, unsigned int color_nb) const
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = _coord.y;
	wattron(win, COLOR_PAIR(color_nb));
	while (_skin.c_str()[i])
	{
		x = 0;
		while (_skin.c_str()[i] && _skin.c_str()[i] != '\n')
			mvwaddch(win, y, _coord.x + (x++), _skin.c_str()[i++]);
		i += _skin.c_str()[i] ? 1 : 0;
		y++;
	}
	wattroff(win, COLOR_PAIR(color_nb));
}

unsigned int	AEntity::getHp() const { return (_hp); }

unsigned int	AEntity::getDamageDeal() const { return (_damageDeal); }

unsigned int    AEntity::getScore() const { return (_score); }

t_coord			AEntity::getCoord() const { return (_coord); }

t_coord			AEntity::getSkinSize(std::string skin)
{
    std::size_t index;
	std::size_t	height;
    std::size_t length_tmp;
    std::size_t length_max;

    index = 0;
	height = 0;
    length_tmp = 0;
    length_max = 0;
	while (index < skin.length() - 1)
    {
		height++;
        index += length_tmp + 1;
		if ((length_tmp = skin.find("\n", index + 1) - index) > skin.length())
        {
            length_tmp = skin.length() - index;
            length_max = (length_max < length_tmp) ? length_tmp : length_max;        
            break ;
        }
        length_max = (length_max < length_tmp) ? length_tmp : length_max;
    }
	return ((t_coord){length_max, height});
}

AEntity::NoWeaponEquippedException::NoWeaponEquippedException() {}

AEntity::NoWeaponEquippedException::NoWeaponEquippedException(NoWeaponEquippedException const &src) { *this = src; }

AEntity::NoWeaponEquippedException::~NoWeaponEquippedException() throw() {}

AEntity::NoWeaponEquippedException	&AEntity::NoWeaponEquippedException::operator=(AEntity::NoWeaponEquippedException const &rhs)
{
    (void)rhs;
    return (*this);
}

char const                        	*AEntity::NoWeaponEquippedException::what(void) const throw() { return ("No Weapon Equipped"); }
