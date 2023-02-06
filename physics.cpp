#include "physics.h"


//====Calculation & do stuff====//
void Physics::Calculate_sum_vector(sf::RectangleShape &body){
    float temp_x = body.getPosition().x-this->body.getPosition().x;
    float temp_y = body.getPosition().y-this->body.getPosition().y;
    sum_vector.operator=(sf::Vector2f(temp_x,temp_y));
}

void Physics::Calculate_vel_dir(){
    velocity_length = sqrt( pow(sum_vector.x,2) + pow(sum_vector.y,2));
    velocity_dir = sum_vector / velocity_length;
}

float Physics::Calculate_current_velocity_x(const sf::Time &elapsed_time,float acceleration_){
    float temp_vel=0;
    temp_vel = acceleration_*elapsed_time.asSeconds();
    return temp_vel;
}

float Physics::Calculate_current_velocity_y(const sf::Time &elapsed_time,float acceleration_){
    float temp_vel_y = 0;
    temp_vel_y = acceleration_*elapsed_time.asSeconds();
    return temp_vel_y;
}

void Physics::Gravity_pull(const sf::Time &elapsed_time){
    if(gravity && current_velocity.y <=max_velocity.y){
       current_velocity.y += gravity_acceleration*elapsed_time.asSeconds();
    }
    else if( gravity && current_velocity.y > max_velocity.y){
        current_velocity.y = max_velocity.y;
    }
}

void Physics::collision_with_arena(std::vector<std::unique_ptr<Tile> > &tiles){
    for(auto &obj : tiles){

                if(body.getGlobalBounds().intersects(obj->body.getGlobalBounds())){

                    if (obj->Air && (x_left >= obj->x_left && x_right <= obj->x_right))
                    {
                        if(!hit_bottom && !getgravity()){
                            setgravity(true);
                        }
                    }

                    if((y_bottom <= obj->y_top+1) && !obj->Air){
                        current_velocity.y = 0;
                        body.setPosition(body.getPosition().x,obj->y_top-body.getGlobalBounds().height/2+1);
                        sethit_bottom(true);
                        setgravity(false);
                    }
                    else if (( y_bottom <= obj->y_top+1) && (x_left >= obj->x_left && x_right <= obj->x_right) && (obj->Air && !getgravity())){
                        sethit_bottom(false);
                    }

                    if((y_top >= obj->y_bottom && x_right >= obj->x_left+0.5 && x_left <= obj->x_right-0.5) && (!obj->Air) ){
                        current_velocity.y = 0;
                        body.setPosition(body.getPosition().x,obj->y_bottom+body.getGlobalBounds().height/2);
                    }

                    if((x_right <= obj->x_left+1 && !obj->Air)
                            &&((collision_point_top_bottom.y >= obj->y_top && collision_point_top_bottom.y <= obj->y_bottom)
                               ||(collision_point_top_bottom.x >= obj->y_top && collision_point_top_bottom.x <= obj->y_bottom))
                       ){
                       current_velocity.x = 0;
                       body.setPosition(obj->x_left-body.getLocalBounds().width/2,body.getPosition().y);
                    }

                    if((x_left >= obj->x_right-1 && !obj->Air)
                        && ((collision_point_top_bottom.y >= obj->y_top && collision_point_top_bottom.y <= obj->y_bottom)
                            ||(collision_point_top_bottom.x >= obj->y_top && collision_point_top_bottom.x <= obj->y_bottom))
                            ){
                       current_velocity.x = 0;
                       body.setPosition(obj->x_right+body.getGlobalBounds().width/2,body.getPosition().y);  //+
                    }
                }
         }
    }

void Physics::calculate_collision_point(){

    sf::Vector2f temp_vector(y_top+6,y_bottom-6);
    collision_point_top_bottom=temp_vector;
}

void Physics::calculate_angle(){
    float temp = sum_vector.y/sum_vector.x;
    angle = atanf(temp) * 180/PI;
}

sf::Vector2f Physics::calculate_vector_velocity(const sf::Time &elapsed_time, float acceleration_){
    float temp_x = velocity_dir.x * acceleration_ * elapsed_time.asSeconds();
    float temp_y = velocity_dir.y * acceleration_ * elapsed_time.asSeconds();
    sf::Vector2f temp_vel_vector(sf::Vector2f(temp_x,temp_y));
    return temp_vel_vector;
}
//====Getters====//
sf::Vector2f Physics::getcurrent_velocity(){
    return current_velocity;
}
float Physics::getacceleration(){
    return acceleration;
}
sf::Vector2f Physics::getmax_velocity(){
    return max_velocity;
}
float Physics::getgravity_acceleration(){
    return gravity_acceleration;
}
bool Physics::getgravity(){
    return gravity;
}
bool Physics::gethit_top(){
    return hit_top;
}
bool Physics::gethit_left(){
    return hit_left;
}
bool Physics::gethit_right(){
    return hit_right;
}
bool Physics::gethit_bottom(){
    return hit_bottom;
}

//====Setters====//
void Physics::setcurrent_velocity_x(float current_velocity_){
    current_velocity.x=current_velocity_;
}
void Physics::setcurrent_velocity_y(float current_velocity_){
    current_velocity.y=current_velocity_;
}
void Physics::setacceleration(float acceleration_){
    acceleration=acceleration_;
}
void Physics::setmax_velocity(sf::Vector2f max_velocity_){
    max_velocity=max_velocity_;
}
void Physics::setgravity_acceleration(float gravity_acceleration_){
    gravity_acceleration=gravity_acceleration_;
}
void Physics::setgravity(bool gravity_){
    gravity=gravity_;
}
void Physics::sethit_top(bool hit_top_){
    hit_top = hit_top_;
}
void Physics::sethit_left(bool hit_left_){
    hit_left=hit_left_;
}
void Physics::sethit_right(bool hit_right_){
    hit_right=hit_right_;
}
void Physics::sethit_bottom(bool hit_bottom_){
   hit_bottom=hit_bottom_;
}
