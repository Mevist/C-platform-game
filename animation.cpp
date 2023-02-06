#include "animation.h"

Animation::Animation(sf::Texture &object_texture,int rect_begin_x_,int rect_begin_y_, int texture_width_,int texture_height_,int frames_in_line_)
    :loaded_texture(object_texture),rect_begin_x(rect_begin_x_),rect_begin_y(rect_begin_y_),texture_width(texture_width_),texture_height(texture_height_),frames_in_line(frames_in_line_)
{
add_frame();
}

void Animation::add_frame(){
     sf::IntRect temp_frame;
     frames_in_line = frames_in_line -1;

    for(int i = 0;i<=frames_in_line;i++){
   temp_frame=(sf::IntRect(i*texture_width,rect_begin_y,texture_width,texture_height));
    animation_frames.emplace_back(temp_frame);
    }
}

void Animation::uptade_animation(const sf::Time &elapsed_time,sf::RectangleShape &body,float time_to_pass){
  float seconds = elapsed_time.asSeconds();
  time_passed += seconds;

  if(time_passed > time_to_pass){
    body.setTextureRect(animation_frames[current_frame]);
    current_frame++;
    if(current_frame==animation_frames.size()){
        current_frame=0;
    }
    time_passed = 0;
  }

}

