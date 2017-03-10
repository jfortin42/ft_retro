/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:15:44 by jfortin           #+#    #+#             */
/*   Updated: 2017/03/10 18:02:09 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISSILE_HPP
# define MISSILE_HPP

# include "AEntity.hpp"
# include "AWeapon.hpp"

class Missile : public AEntity {

public:
	Missile(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, AWeapon *weapon, t_coord coord, char direction1, char direction2);
	Missile(Missile const &src);
	~Missile();

	Missile		&operator=(Missile const &rhs);

	bool	 		move(unsigned int height, unsigned int width, int key);
    t_entityList	*shoot(int key);

private:
	Missile();

	char			_direction1;
	char			_direction2;

};

#endif