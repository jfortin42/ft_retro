/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pioupiou.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 21:44:35 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/05 22:16:50 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pioupiou.hpp"

Pioupiou::Pioupiou()
{}

Pioupiou::~Pioupiou()
{}

Pioupiou::Pioupiou(Pioupiou const &src)
{
	*this = src;
}

AEntity		*Pioupiou::createMissile(AEntity const &shooter)
{
	t_coord coordShoot;
    
    coordShoot.x = shooter.getCoord().x + shooter.getSizeSkin().x / 2;
    coordShoot.y = shooter.getCoord().y - 1;
	return (new Missile(1, 100, "8", NULL, coordShoot, 'N'));
}

Pioupiou	&Pioupiou::operator=(Pioupiou const &rhs)
{
	if (this != &rhs)
	;
	return (*this);	
}