/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IGameEntity.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 14:39:26 by fsidler           #+#    #+#             */
/*   Updated: 2016/12/13 17:47:00 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_GAME_ENTITY_HPP
# define I_GAME_ENTITY_HPP

# include <iostream>//yes?
# include <ncurses.h>//yes?

class GameEntity {

    private:
        
        //unsigned int    _size;//size bigger than 1?
        std::string     _type; //useless
        unsigned int    _hp;
        unsigned int    _dmg; //move into weapon class
        double          _rateOfFire; //move into weapon class

        char            _fireSymbol; //move into weapon class
        char            _shipSymbol;//or std::string _shipSymbol; (if ships bigger than size = 1)
        
    public:
        GameEntity(std::string type, unsigned int hp, unsigned int dmg, double rateOfFire);
        GameEntity(GameEntity const &src);
        virtual ~GameEntity() {}

        GameEntity      &operator=(GameEntity const &rhs);

        /*std::string     getType() const;

        void            shootMissile(unsigned int dmg) = 0;
        void            takeDamage(unsigned int dmg) = 0;
        void            updatePosition(int keyPressed) = 0;*/



};

#endif