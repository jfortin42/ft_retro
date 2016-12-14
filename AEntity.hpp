/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:02:23 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/14 17:31:43 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AENTITY_HPP
# define AENTITY_HPP

#include <iostream>
#include <string>
#include <ncurses.h>

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
	AEntity(AEntity const &src);
	~AEntity();

	void	equipWeapon();
	void	move(char direction);
	Missile *shoot();
	void	takeDamage(AEntity const &attacker);
	void	displaySkin() const;

	AEntity	&operator=(AEntity const &rhs);

protected:
	AEntity();
	
	unsigned int	hp;
	unsigned int	speed;
	std::string		skin;
	AWeapon			*weapon;
	t_coord			coord;

};

#endif