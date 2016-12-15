/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 14:51:41 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/15 16:49:08 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AWeapon.hpp"

AEntity	*AWeapon::createMissile(AEntity const &shooter)
{
	return (new AEntity(1, 1, ".", NULL, shooter.getCoord()));
}