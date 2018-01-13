/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:15:44 by jfortin           #+#    #+#             */
/*   Updated: 2018/02/11 22:27:29 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISSILE_HPP
# define MISSILE_HPP

# include "AEntity.hpp"
# include "Weapon.hpp"

class Missile : public AEntity {

public:
	Missile(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, Weapon *weapon, t_coord coord, char direction_move, char direction_shoot);
	Missile(Missile const &src);
	~Missile();

	Missile		&operator=(Missile const &rhs);

	bool	 		move(unsigned int height, unsigned int width, int key);
    t_entityList	*shoot(int key);

private:
	Missile();

	char			_direction_move;
	char			_direction_shoot;

};

#endif