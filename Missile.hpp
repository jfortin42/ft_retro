/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:15:44 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/20 19:19:07 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISSILE_HPP
# define MISSILE_HPP

# include "AEntity.hpp"
# include "AWeapon.hpp"

class AEntity;
class AWeapon;

class Missile : public AEntity {

	public:
		Missile(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord, AEntity const &shooter, char direction);
		Missile(Missile const &src);
		~Missile();

		Missile		&operator=(Missile const &rhs);

		void        move(unsigned int height, unsigned int width, int key);
        AEntity     *shoot();

	private:
		Missile();

		AEntity	const	&shooter;
		char const		direction;
};

#endif