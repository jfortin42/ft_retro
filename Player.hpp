/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:56:48 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/16 18:15:40 by fsidler          ###   ########.fr       */
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
    AEntity         *shoot();
    
    unsigned int    takeDamage(AEntity const &attacker, WINDOW *win);
        
private:
    Player();

};

#endif