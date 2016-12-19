/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:27 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/19 19:14:03 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AWEAPON_HPP
# define AWEAPON_HPP

// #include "Missile.hpp"
#include "AEntity.hpp"

class	AEntity;

class	AWeapon{

public:
	~AWeapon();
	AWeapon(AWeapon const &src);

	AEntity	*createMissile(AEntity const &shooter);

	AWeapon	&operator=(AWeapon const &rhs);

private:
	AWeapon();

};

#endif