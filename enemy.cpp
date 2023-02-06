#include "enemy.h"

Enemy::Enemy(sf::Vector2f starting_position_,float fire_speed_)
{

    //===Enemy object===//
    fire_speed=fire_speed_;
    starting_position=starting_position_;
    body.setSize({20,20});
    body.setFillColor(sf::Color::Red);
    setOrigin();
    setEdges();
    body.setPosition(starting_position);

    points_vector.resize(20);
    contains_bool_vector.resize(20);

    //===lufa===//
    lufa.setSize({(5/3)*body.getSize().x,5});
    lufa.setFillColor(sf::Color::Blue);
    lufa.setOrigin(0,lufa.getSize().y/2);
    lufa.setPosition(body.getPosition());
    lufa.rotate(0);

    object_ptr=std::make_unique<sf::RectangleShape>(lufa);
    objects_body.push_back(std::move(object_ptr));

    object_ptr=std::make_unique<sf::RectangleShape>(body);
    objects_body.push_back(std::move(object_ptr));

}

void Enemy::uptade(const sf::Time &elapsed_time,sf::RectangleShape &body,std::vector<std::unique_ptr<Tile> > &tiles){
    Calculate_sum_vector(body);
    Calculate_vel_dir();
    calculate_angle();
    create_points_vector(body);
    check_if_tile_contain_point(tiles);
    check_in_sight();
    fire(elapsed_time);
    for(auto &obj_uptade : projectiles){
        obj_uptade->uptade(elapsed_time);
    }
    clear_projectiles_out_of_window();
    projectiles_collision_arena(tiles);
    uptade_line(body);
    uptade_lufa(body);


    object_ptr=std::make_unique<sf::RectangleShape>(lufa);
    objects_body[0].swap(object_ptr);

    object_ptr=std::make_unique<sf::RectangleShape>(this->body);
    objects_body[1].swap(object_ptr);

}

void Enemy::fire(const sf::Time &elapsed_time){
   float seconds = elapsed_time.asSeconds();
   time_passed += seconds;

       if(time_passed > fire_speed && in_sight){
            auto temp_projectile = std::make_unique<Projectile>(this->body.getPosition(),angle,velocity_dir);
            projectiles.push_back(std::move(temp_projectile));
       time_passed = 0;
    }

}

void Enemy::clear_projectiles_out_of_window(){
    for(auto i=0;i< projectiles.size();i++){
        if(projectiles.size() >5){
        if(projectiles[i]->body.getPosition().y < 0){
            projectiles.erase(projectiles.begin()+i);
        }
        if(projectiles[i]->body.getPosition().y > 600){
            projectiles.erase(projectiles.begin()+i);
        }
        if(projectiles[i]->body.getPosition().x < 0){
            projectiles.erase(projectiles.begin()+i);
        }
        if(projectiles[i]->body.getPosition().x > 800){
            projectiles.erase(projectiles.begin()+i);
        }
        }
    }
}

void Enemy::projectiles_collision_arena(std::vector<std::unique_ptr<Tile> > &tiles){
    for(auto &tile :tiles){
        if(!tile->getAir()){
            for(auto i=0;i< projectiles.size();i++){
                if(projectiles.size() >5 && tile->body.getGlobalBounds().intersects(projectiles[i]->body.getGlobalBounds())){
                projectiles.erase(projectiles.begin()+i);
                }
            }
        }
    }
}
void Enemy::uptade_line(sf::RectangleShape &body){
    line2[1]=sf::Vertex(body.getPosition());
}

void Enemy::create_points_vector(sf::RectangleShape &body){         // jest to vector punktow polozonych w jednej lini od gracza do przeciwnika, jesli jakikolwiek punkt pokrywa sie z bloczkiem mapy, przeciwnik nie widzie gracza
       float temp_vector_length = velocity_length / 20;
   for(size_t i=0;i<points_vector.size();i++){
      point_cordinates.x = this->body.getPosition().x + velocity_dir.x*temp_vector_length*point_number;
      point_cordinates.y = this->body.getPosition().y + velocity_dir.y*temp_vector_length*point_number;
       contains=false;
      points_vector[i]= point_cordinates;
      contains_bool_vector[i]=false;
      point_number++;
       if(point_number==points_vector.size()+1){
          point_number=1;
       }
     }

}

void Enemy::uptade_lufa(sf::RectangleShape &body){
    if(this->body.getPosition().x > body.getPosition().x){
    lufa.setRotation(angle+180);
   }
    else{
    lufa.setRotation(angle);
    }
}

void Enemy::check_if_tile_contain_point(std::vector<std::unique_ptr<Tile> > &tiles){
    for( auto &obj :tiles){
            if(!obj->getAir()){
                for(auto i= 0;i<points_vector.size();i++){

                        if(obj->body.getGlobalBounds().contains(points_vector[i])){
                            contains_bool_vector[i]=true;
                        }
                  }
             }
     }
}


void Enemy::check_in_sight(){
    if(std::none_of(contains_bool_vector.begin(),contains_bool_vector.end(), [](bool v) {return v;})){
        in_sight = true;
    }
    else{
        in_sight = false;
    }
}
//===setters===//

//===getters===//
std::vector<std::unique_ptr<Projectile>>& Enemy::getprojectiles(){
    return projectiles;
}

