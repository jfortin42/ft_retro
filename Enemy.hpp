/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:59:42 by jfortin           #+#    #+#             */
/*   Updated: 2018/02/11 22:25:38 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "Game.hpp"

class	Enemy : public AEntity {

public:
	Enemy(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, Weapon *weapon, t_coord coord);
	Enemy(Enemy const &src);
	~Enemy();

	Enemy			&operator=(Enemy const &rhs);
	
	bool        	move(unsigned int height, unsigned int width, int key);
    t_entityList    *shoot(int key);

private:
	Enemy();
		
};

#endif