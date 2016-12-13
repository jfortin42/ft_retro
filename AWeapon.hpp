/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:18:27 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/13 18:25:24 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AWEAPON_HPP
# define AWEAPON_HPP

#include "Missile.hpp"

class	AWeapon{

public:
	~AWeapon();
	AWeapon(AWeapon const &src);

	virtual Missile	*createMissile() = 0;

	AWeapon	&operator=(AWeapon const &rhs);

private:
	AWeapon();

};

#endif