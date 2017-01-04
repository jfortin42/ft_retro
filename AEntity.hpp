/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntity.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:02:23 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/04 18:59:07 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AENTITY_HPP
# define AENTITY_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <ncurses.h>

# include "AWeapon.hpp"
//# include "Missile.hpp"

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
	virtual ~AEntity();

	void			equipWeapon(AWeapon *weapon);
	virtual bool	move(unsigned int height, unsigned int width, int key) = 0;
	//Missile *shoot();
	virtual AEntity	*shoot() = 0;
	void			takeDamage(AEntity const &attacker);
	void			displaySkin(WINDOW *win) const;
	t_coord			getCoord() const;
	t_coord			getSizeSkin() const;

	AEntity	&operator=(AEntity const &rhs);

protected:
	AEntity();
	
	unsigned int	hp;
	unsigned int	speed; // millisecond
	unsigned int	cnt_move;
	std::string		skin;
	t_coord			sizeSkin;
	AWeapon			*weapon;
	t_coord			coord;

};

#endif