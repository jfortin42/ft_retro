/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:07:28 by jfortin           #+#    #+#             */
/*   Updated: 2018/02/11 22:47:00 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_HPP
# define BONUS_HPP

# include "Game.hpp"

class Bonus : public AEntity {

    public:

        Bonus(std::string skin, Weapon *weapon, t_coord coord, unsigned int timePop = 10000);
        Bonus(Bonus const &src);
        ~Bonus();

        Bonus           &operator=(Bonus const &rhs);

        bool			move(unsigned int height, unsigned int width, int key);
        t_entityList	*shoot(int key);

        unsigned int	takeDamage(AEntity &attacker);
        
    private:
        Bonus();

};

#endif