/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:59:42 by jfortin           #+#    #+#             */
/*   Updated: 2017/01/16 18:00:01 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP
# define ENEMY_HPP

# include "Game.hpp"

class	Enemy : public AEntity {

public:
	Enemy(unsigned int hp, unsigned int damageDeal, unsigned int speed, unsigned int score, std::string skin, AWeapon *weapon, t_coord coord);
	Enemy(Enemy const &src);
	~Enemy();

	Enemy			&operator=(Enemy const &rhs);
	
	bool        	move(unsigned int height, unsigned int width, int key);
    AEntity     	*shoot();

private:
	Enemy();
		
};

#endif