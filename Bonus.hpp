/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:35:21 by fsidler           #+#    #+#             */
/*   Updated: 2017/03/19 23:06:45 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_HPP
# define BONUS_HPP

# include "Game.hpp"

class Bonus : public AEntity {

    public:

        Bonus(std::string skin, Weapon *weapon, t_coord coord, unsigned int timePop = 20000);
        Bonus(Bonus const &src);
        ~Bonus();

        Bonus           &operator=(Bonus const &rhs);

        bool			move(unsigned int height, unsigned int width, int key);
        t_entityList	*shoot(int key);

        unsigned int	takeDamage(AEntity &attacker, WINDOW *win);
        
    private:
        Bonus();

};

#endif