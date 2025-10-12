#pragma once

struct Coordinate
{
    Coordinate(float x_in, float y_in) : x(x_in), y(y_in), coord_id(0), next(nullptr), prev(nullptr)//Creating constructer
    {
        
    }

    float x;
    float y;
    int coord_id;
    Coordinate *next;
    Coordinate *prev;
};
