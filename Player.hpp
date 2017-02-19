/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:56:48 by fsidler           #+#    #+#             */
/*   Updated: 2017/02/18 18:18:10 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Game.hpp"

class Player : public AEntity {

public:
    Player(unsigned int hp, unsigned int damageDeal, unsigned int speed, std::string skin, AWeapon *weapon, t_coord coord);
    Player(Player const &src);
    ~Player();

    Player          &operator=(Player const &rhs);

    bool            move(unsigned int height, unsigned int width, int key);
    AEntity::t_entityList    *shoot();
    
    unsigned int    takeDamage(AEntity const &attacker, WINDOW *win);
        
private:
    Player();

};

#endif