#include "tile.h"

Tile::Tile(sf::Vector2f tile_position_,int texture_number_,sf::Vector2f size,sf::Texture &area_textures):
    texture_number(texture_number_),tile_position(tile_position_)
{
    body.setSize(size);
    setOrigin();
    body_texture=area_textures;
    body.setTexture(&body_texture);
    select_texture(texture_number);
    body.setPosition(tile_position);
    setEdges();
    object_ptr=std::make_unique<sf::RectangleShape>(body);
    objects_body.push_back(std::move(object_ptr));
}

Tile::Tile(sf::Vector2f tile_position_,int texture_number_,sf::Vector2f size,bool Air_):
    texture_number(texture_number_),tile_position(tile_position_),Air(Air_)
{
    body.setSize(size);
    body.setFillColor(sf::Color(0,0,0,0));
    setOrigin();
    body.setPosition(tile_position);
    setEdges();
}


void Tile::select_texture(int texture_number_){
    if(texture_number_ == 0){           //floor
         roi=(sf::IntRect(0,0,70,70));
         body.setTextureRect(roi);
    }
    if(texture_number_ == 1){           //ceiling
         roi=(sf::IntRect(0,0,70,70));
         body.setScale(1,-1);
         body.setTextureRect(roi);
    }
    if(texture_number_ == 2){           //left wall
         roi=(sf::IntRect(72,0,70,70));
         body.setTextureRect(roi);
    }
    if(texture_number_ == 3){           //right wall
         roi=(sf::IntRect(72,0,70,70));
         body.setScale(-1,1);
         body.setTextureRect(roi);
    }
    if(texture_number_ == 4){           //center block
         roi=(sf::IntRect(144,0,70,70));
         body.setTextureRect(roi);
    }
    if(texture_number_ == 5){           //left clif
         roi=(sf::IntRect(216,0,70,70));
         body.setTextureRect(roi);
    }
    if(texture_number_ == 6){           //right clif
         roi=(sf::IntRect(289,0,70,70));
         body.setTextureRect(roi);
    }
}

//===Setters===//
void Tile::setcollides(bool collides_){
    collides=collides_;
}

//===Getters===//
bool Tile::getcollides(){
    return collides;
}
bool Tile::getAir(){
    return Air;
}
