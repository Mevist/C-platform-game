#include "projectile.h"

Projectile::Projectile(sf::Vector2f starting_position_,float rotate_factor_,sf::Vector2f vel_dir_)
{
    body.setSize({10,5});
    body.setFillColor(sf::Color::Yellow);
    body.setOrigin(0,body.getSize().y/2);
    starting_position=starting_position_;
    body.setPosition(starting_position);
    body.rotate(rotate_factor_);

    auto body_ptr=std::make_unique<sf::RectangleShape>(body);
    objects_body.push_back(std::move(body_ptr));

    velocity_dir=vel_dir_;
    setacceleration(20.0f);
    setmax_velocity({15.0f,15.0f});

    object_ptr=std::make_unique<sf::RectangleShape>(body);
    objects_body.push_back(std::move(object_ptr));
}

void Projectile::move(){
    body.move(current_velocity);
}

void Projectile::uptade(const sf::Time &elapsed_time){
    if(current_velocity.x < max_velocity.x && current_velocity.y < max_velocity.y){
    current_velocity += calculate_vector_velocity(elapsed_time,acceleration);
    }
    move();

    object_ptr=std::make_unique<sf::RectangleShape>(body);
    objects_body[0].swap(object_ptr);
}
