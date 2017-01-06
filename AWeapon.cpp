/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:51:41 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/05 22:17:59 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AWeapon.hpp"

AWeapon::AWeapon()
{}

AWeapon::~AWeapon()
{}

AWeapon::AWeapon(AWeapon const &src)
{
	*this = src;
}

AEntity	*AWeapon::createMissile(AEntity const &shooter)
{
    t_coord coordShoot;
    
    coordShoot.x = shooter.getCoord().x + shooter.getSizeSkin().x / 2;
    coordShoot.y = shooter.getCoord().y - 1;
    // return (new Missile(1, 100, "|", NULL, coordShoot, *this, 'N'));

	return (new Missile(1, 100, "D", NULL, coordShoot, 'N'));
}

AWeapon	&AWeapon::operator=(AWeapon const &rhs)
{
	if (this != &rhs)
	;
	return (*this);
}