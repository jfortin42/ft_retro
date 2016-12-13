/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:02:23 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/13 18:04:34 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AENTITY_HPP
# define AENTITY_HPP

#include <iostream>
#include <string>

typedef struct	s_coord
{
	unsigned int	x;
	unsigned int	y;
}				t_coord;

class	Missile;
class	AWeapon;

class	AEntity{

public:
	AEntity(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord);
	~AEntity();

	void	equipWeapon();
	void	move(char direction);
	Missile *shoot();
	void	takeDamage(AEntity const &attacker);

	AEntity	&operator=(AEntity const &src);

private:
	AEntity();
	
	unsigned int	hp;
	unsigned int	speed;
	std::string		skin;
	AWeapon			*weapon;
	t_coord			coord;


};

#endif