#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
private:
    std::vector<sf::IntRect> animation_frames;
    sf::Texture loaded_texture;
    float time_passed;
    int current_frame = 0;

    //===texture cordinates===//
    int rect_begin_x;
    int rect_begin_y;
    int texture_width;
    int texture_height;
    int frames_in_line;

    //===methods===//
     void add_frame();
public:
    Animation(sf::Texture &object_texture,int rect_begin_x_,int rect_begin_y_, int texture_width_,int texture_height_,int frames_in_line_);
    void uptade_animation(const sf::Time &elapsed_time,sf::RectangleShape &body,float time_to_pass);

    //===setters===//

    //===getters===//
};

#endif // ANIMATION_H
