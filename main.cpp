/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:08:09 by jfortin           #+#    #+#             */
/*   Updated: 2018/02/11 22:44:46 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

int main()
{
    srand((unsigned int)time(NULL));
    Game    *play = new Game();
    try
    {
        while (play->launch() == false)
            {
                delete play;
                play = new Game();
            }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    delete play;
    return (0);
}