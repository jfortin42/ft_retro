/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:06:31 by jfortin           #+#    #+#             */
/*   Updated: 2018/02/11 22:49:26 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AEntity.hpp"
#include "Weapon.hpp"

AEntity::AEntity(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, Weapon *weapon, t_coord coord, char direction) : _skinSize(getSkinSize(skin)), _hp(hp), _damageDeal(damageDeal), _speed(speed), _score(score), _lastMove(clock()), _skin(skin), _weaponList(NULL), _coord(coord)
{
	equipWeapon(weapon, direction);
}

AEntity::AEntity(AEntity const &src) : _skinSize(src._skinSize), _hp(src._hp), _damageDeal(src._damageDeal), _speed(src._speed), _score(src._score), _lastMove(0), _skin(src._skin), _coord(src._coord)
{
	copyWeaponList(src._weaponList);
}

AEntity::~AEntity()
{
	while (_weaponList)
	{
		t_weaponList	*next = _weaponList->next;
		delete _weaponList->weapon;
		_weaponList->weapon = NULL;
		delete _weaponList;
		_weaponList = next;
	}
}

AEntity			&AEntity::operator=(AEntity const &rhs)
{
	if (this != &rhs)
	{
		_hp = rhs._hp;
		_damageDeal = rhs._damageDeal;
		_speed = rhs._speed;
		_score = rhs._score;
		_lastMove = rhs._lastMove;
		_skin = rhs._skin;
		_coord = rhs._coord;
		copyWeaponList(rhs._weaponList);
	}
	return (*this);
}

void			AEntity::copyWeaponList(t_weaponList *src)
{
	while (src)
	{
		equipWeapon(src->weapon, 'D');
		src = src->next;
	}
}

void			AEntity::equipWeapon(Weapon *weapon, char direction)
{
 	if (weapon)
	{
		t_weaponList	*tmp = _weaponList;
		t_weaponList	*newWeapon = new t_weaponList();

		newWeapon->weapon = weapon;
		char dir[] = {'N', 'W', 'E', 'S', 'D'};
		int i = 0;
		if (direction == 'D')
		{
			while (tmp)
			{
				if (tmp->direction == dir[i] && ((tmp->weapon->isSimpleWeapon() && weapon->isSimpleWeapon()) || (!tmp->weapon->isSimpleWeapon() && !weapon->isSimpleWeapon())))
				{
					i++;
					tmp = _weaponList;
				}
				else
					tmp = tmp->next;
			}
		}
		else
			dir[i] = direction;
		newWeapon->direction = dir[i];
		tmp = _weaponList;
		newWeapon->next = NULL;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp ? tmp->next = newWeapon : _weaponList = newWeapon;
	}
}

unsigned int	AEntity::takeDamage(AEntity &attacker)
{
	_hp -= _hp < attacker.getDamageDeal() ? _hp : attacker.getDamageDeal();
	return (_hp);
}

void			AEntity::displaySkin(WINDOW *win, unsigned int colorNb) const
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = _coord.y;
	wattron(win, COLOR_PAIR(colorNb));
	while (_skin.c_str()[i])
	{
		x = 0;
		while (_skin.c_str()[i] && _skin.c_str()[i] != '\n')
			mvwaddch(win, y, _coord.x + (x++), _skin.c_str()[i++]);
		i += _skin.c_str()[i] ? 1 : 0;
		y++;
	}
	wattroff(win, COLOR_PAIR(colorNb));
}

unsigned int	AEntity::getHp() const { return (_hp); }

unsigned int	AEntity::getDamageDeal() const { return (_damageDeal); }

unsigned int	AEntity::getScore() const { return (_score); }

t_coord			AEntity::getCoord() const { return (_coord); }

t_coord			AEntity::getSkinSize(std::string skin)
{
	std::size_t index = 0;
	std::size_t	height = 0;
	std::size_t lengthTmp = 0;
	std::size_t lengthMax = 0;

	while (index < skin.length() - 1)
	{
		height++;
		index += lengthTmp + 1;
		if ((lengthTmp = skin.find("\n", index + 1) - index) > skin.length())
		{
			lengthTmp = skin.length() - index;
			lengthMax = (lengthMax < lengthTmp) ? lengthTmp : lengthMax;		
			break ;
		}
		lengthMax = (lengthMax < lengthTmp) ? lengthTmp : lengthMax;
	}
	return ((t_coord){(unsigned int)lengthMax, (unsigned int) height});
}

AEntity::NoWeaponEquippedException::NoWeaponEquippedException() {}

AEntity::NoWeaponEquippedException::NoWeaponEquippedException(NoWeaponEquippedException const &src) { *this = src; }

AEntity::NoWeaponEquippedException::~NoWeaponEquippedException() throw() {}

AEntity::NoWeaponEquippedException	&AEntity::NoWeaponEquippedException::operator=(AEntity::NoWeaponEquippedException const &rhs)
{
	(void)rhs;
	return (*this);
}

char const							*AEntity::NoWeaponEquippedException::what(void) const throw() { return ("No Weapon Equipped"); }
