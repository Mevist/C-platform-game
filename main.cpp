#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <physics.h>
#include <map.h>
#include <enemy.h>

using namespace std;
using namespace sf;

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);

    //Time//=======================================================================
    Clock clock;

   //Objects//===========================================================================
    Map test("map_1.txt","Textures/Map_Tiles/");
    test.Initialize_map(window);
    auto& Tiles_to_draw = test.getTiles();
    //===ENEMY====//
    Enemy test_enemy(sf::Vector2f(60,545),0.05);
    Enemy test_enemy2(sf::Vector2f(740,60),0.05);
    Enemy test_enemy3(sf::Vector2f(60,60),0.05);
    Enemy test_enemy4(sf::Vector2f(740,545),0.05);
    //====Player====//
    Player p1(400,window.getSize().y/2+50);
   //====Window====//

    while (window.isOpen()) {
    Time elapsed_time = clock.getElapsedTime();
    elapsed_time = clock.restart();

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

       auto& projectiles_to_draw = test_enemy.getprojectiles();
       auto& projectiles_to_draw2 = test_enemy2.getprojectiles();
       auto& projectiles_to_draw3 = test_enemy3.getprojectiles();
       auto& projectiles_to_draw4 = test_enemy4.getprojectiles();


        test_enemy.uptade(elapsed_time,p1.body,Tiles_to_draw);
        test_enemy2.uptade(elapsed_time,p1.body,Tiles_to_draw);
        test_enemy3.uptade(elapsed_time,p1.body,Tiles_to_draw);
        test_enemy4.uptade(elapsed_time,p1.body,Tiles_to_draw);


          p1.uptade(elapsed_time,Tiles_to_draw);



        // clear the window with black color
        window.clear(sf::Color::White);

        //===background===//
        window.draw(test.getbackground_texture());
        //===Enemies projectiles===//
        for(auto &object_to_draw : projectiles_to_draw){
            window.draw(*object_to_draw);
        }
        for(auto &object_to_draw2 : projectiles_to_draw2){
            window.draw(*object_to_draw2);
        }
        for(auto &object_to_draw3 : projectiles_to_draw3){
            window.draw(*object_to_draw3);
        }
        for(auto &object_to_draw4 : projectiles_to_draw4){
            window.draw(*object_to_draw4);
        }


        //===arena tiles===//
        for(auto &object_to_draw : Tiles_to_draw){
            window.draw(*object_to_draw);
        }


        //===Enemy===//
        window.draw(test_enemy);
        window.draw(test_enemy2);
        window.draw(test_enemy3);
        window.draw(test_enemy4);

//        window.draw(test_enemy.line2,2,sf::Lines);
//        window.draw(test_enemy2.line2,2,sf::Lines);
        //===Player===//
        window.draw(p1);


      // end the current frame
             window.display();
    }
    return 0;
}


