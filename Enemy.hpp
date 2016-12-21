/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:59:42 by jfortin           #+#    #+#             */
/*   Updated: 2016/12/21 18:06:12 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "AEntity.hpp"
# include "Missile.hpp"

class Missile;
class AEntity;

class	Enemy : public AEntity{

	public:
		Enemy(unsigned int hp, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord);
		Enemy(Enemy const &src);
		~Enemy();

		bool        move(unsigned int height, unsigned int width, int key);
        AEntity     *shoot();

		Enemy	&operator=(Enemy const &rhs);

	private:
		Enemy();
};

#endif