#include "../../include/Entities/Entities.hpp"

static void configureGrid(uint size, std::vector<std::vector<Box>>* grid)
{
    std::vector<std::vector<Box>> cells;
    uint row = 600/size;
    uint column = 600/size;

    for(uint i = 0; i < row; i++){
        std::vector<Box> row_cells;
        for(uint j = 0; j < column; j++){
            Box box = Box(size, sf::Vector2f(i * size, j * size));
            box.row = i;
            box.col = j;

            //should i manually delete the box, or is it okay?
            row_cells.push_back(box);
        }
        (*grid).push_back(row_cells);
    }
}