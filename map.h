#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <tile.h>

class Map
{
private:
    //===Read and store data from file===//
    std::string mapfile_path;
    std::string maptiles_path;
    std::fstream loaded_map;

    //read file data//
    std::string find_line;      // tymczasowe dane
    std::string tile_x_;
    std::string tile_y_;
    std::string texture_number_;
    int texture_number;

    sf::Vector2i tile_position_number;

    //===Tile data===//
    sf::Vector2f size;
    std::vector<sf::Vector2i> vector_of_tile_position_number;
    std::vector<std::unique_ptr<Tile>> Tiles;
    sf::Texture maptiles;

    bool Air_;

    //===Background===//
    sf::Sprite background;
    sf::Texture background_texture;
    //===methods===//
    void read_data_from_file();
    void read_data_line();
    void convert_data();
    void create_tile(bool Air_);
    void setbackgroundsettings(sf::RenderTarget &window);

    sf::Vector2f Calculate_tile_position_(sf::Vector2i &tile_position_number);
    public:

    Map(std::string mapfile_path_,std::string maptiles_path_);

    void Initialize_map(sf::RenderTarget &window);

   //====Getters====//
     std::vector<std::unique_ptr<Tile>>& getTiles();
     sf::Sprite getbackground_texture();
};

#endif // MAP_H
