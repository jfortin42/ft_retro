/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:02:23 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/19 19:51:57 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AENTITY_HPP
# define AENTITY_HPP

# include <iostream>
# include <string>
# include <ncurses.h>

# include "AWeapon.hpp"

typedef struct	s_coord
{
	unsigned int	x;
	unsigned int	y;
}				t_coord;

//class	Missile;
class	AWeapon;

class	AEntity{

public:
	AEntity(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord);
	AEntity(AEntity const &src);
	~AEntity();

	void	equipWeapon(AWeapon *weapon);
	void	move(unsigned int height, unsigned int width, int key);
	//Missile *shoot();
	void	takeDamage(AEntity const &attacker);
	void	displaySkin(WINDOW *win) const;
	t_coord	getCoord() const;

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