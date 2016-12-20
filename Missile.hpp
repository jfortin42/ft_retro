/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:15:44 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/20 18:29:13 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AEntity.hpp"
#include "AWeapon.hpp"

class	AEntity;
class	AWeapon;

class	Missile : public AEntity{

public:
	Missile(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord, AEntity const &shooter);
	Missile(Missile const &src);
	~Missile();

	Missile		&operator=(Missile const &rhs);

private:
	Missile();

	AEntity	const &shooter;

};