/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pioupiou.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 21:44:35 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/10 16:19:18 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pioupiou.hpp"

Pioupiou::Pioupiou(unsigned int hp_missile, unsigned int damageDeal, unsigned int speed_missile, unsigned int rateOfFire)
	: AWeapon(hp_missile, damageDeal, speed_missile, rateOfFire)
{}

Pioupiou::Pioupiou() : AWeapon(1, 1, 200, 10000)
{}

Pioupiou::~Pioupiou()
{}

Pioupiou::Pioupiou(Pioupiou const &src) : AWeapon(src.hp_missile, src.damageDeal, src.speed_missile, src.rateOfFire)
{
	*this = src;
}

AEntity		*Pioupiou::createMissile(t_coord coord, char direction)
{
	if (cnt_shoot++ < rateOfFire || coord.y >= (unsigned int)(LINES - BOT_WIN_H))
        throw(AWeapon::RateOfFireException::RateOfFireException());
	cnt_shoot = 0;
	return (new Missile(hp_missile, damageDeal, speed_missile, ".", NULL, coord, direction));
}

Pioupiou	&Pioupiou::operator=(Pioupiou const &rhs)
{
	if (this != &rhs)
	{
		hp_missile = rhs.hp_missile;
		speed_missile = rhs.speed_missile;
		rateOfFire = rhs.rateOfFire;
		cnt_shoot = rhs.cnt_shoot;
	}
	return (*this);	
}