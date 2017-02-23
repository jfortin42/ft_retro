/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 21:01:50 by jfortin           #+#    #+#             */
/*   Updated: 2017/02/23 21:54:55 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOSS_HPP
# define BOSS_HPP

# include "Game.hpp"

class	Boss : public AEntity {

public:
	Boss(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, AWeapon *weapon, t_coord coord);
	Boss(Boss const &src);
	~Boss();

	Boss			&operator=(Boss const &rhs);
	
	bool        	move(unsigned int height, unsigned int width, int key);
    t_entityList    *shoot(int key);

private:
	Boss();
		
	char	_direction;
};

#endif