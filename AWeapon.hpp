/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:27 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/15 16:46:28 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AWEAPON_HPP
# define AWEAPON_HPP

// #include "Missile.hpp"
#include "AEntity.hpp"

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