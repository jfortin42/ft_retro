/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Laser.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:06:23 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/07 22:14:30 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Laser.hpp"

Laser::Laser(unsigned int hp_missile, unsigned int speed_missile, unsigned int rateOfFire)
	: AWeapon(hp_missile, speed_missile, rateOfFire)
{}

Laser::Laser() : AWeapon(1, 50, 200)
{}

Laser::Laser(Laser const &src) : AWeapon(src.hp_missile, src.speed_missile, src.rateOfFire)
{
	*this = src;
}

Laser::~Laser()
{}

AEntity		*Laser::createMissile(t_coord coord, char direction)
{
	if (cnt_shoot++ < rateOfFire)
        throw(AWeapon::RateOfFireException::RateOfFireException());
	cnt_shoot = 0;
	return (new Missile(hp_missile, speed_missile, "|", NULL, coord, direction));
}

Laser	&Laser::operator=(Laser const &rhs)
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