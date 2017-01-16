/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pioupiou.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 21:44:35 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/16 19:02:50 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pioupiou.hpp"

Pioupiou::Pioupiou(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, unsigned int rateOfFire) : AWeapon(hp_missile, damageDeal, speed_missile, rateOfFire) {}

Pioupiou::Pioupiou() : AWeapon(1, 1, 200, 10000) {}

Pioupiou::~Pioupiou() {}

Pioupiou::Pioupiou(Pioupiou const &src) : AWeapon(src._hp_missile, src._damageDeal, src._speed_missile, src._rateOfFire) {}

Pioupiou	&Pioupiou::operator=(Pioupiou const &rhs)
{
	AWeapon::operator=(rhs);
	return (*this);
}

AWeapon		*Pioupiou::clone() const
{
	AWeapon	*clone = new Pioupiou(*this);

	return (clone);
}

AEntity		*Pioupiou::createMissile(t_coord coord, char direction)
{
	if (_cnt_shoot++ < _rateOfFire || coord.y >= (unsigned int)(LINES - BOT_WIN_H))
        throw(AWeapon::RateOfFireException::RateOfFireException());
	_cnt_shoot = 0;
	return (new Missile(_hp_missile, _damageDeal, _speed_missile, ".", NULL, coord, direction));
}