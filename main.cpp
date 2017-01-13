/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 14:35:38 by fsidler           #+#    #+#             */
/*   Updated: 2017/01/13 13:44:02 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <time.h>*/

#include "Game.hpp"

int main()
{
    srand(time(NULL));
    Game    *play = new Game();
    try
    {
        play->launch();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    delete play;
    return (0);
}