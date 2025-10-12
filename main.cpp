#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "coordinate.h"

void add_coordinate(Coordinate **head, float x, float y)//adds a coordinate to the end of the linked list
{
    auto * newCoord = new Coordinate(x, y);
    newCoord->coord_id = (*head)->coord_id + 1;
    newCoord->prev = (*head);
    (*head)->next = newCoord;
    *head = newCoord;
}

void forward_display( Coordinate *front)//displays all coordinates from beginning to end.
{
    Coordinate* current = front;
    std::cout << "Fwd Display: "<< std::endl;
    while(current != nullptr)
    {
        std::cout << current->x << ", "<< current->y <<" coord_id: "<< current->coord_id << std::endl;
        current = current->next;
        
    }
}

void backward_display(Coordinate *front)// displays all coordinates from end to beginning. 
{
    Coordinate* current = front;
    std::cout << "bckwd Display: " << std::endl;
    while(current->next != nullptr)
    {
        current = current->next;
    }

    
    while(current != nullptr)
    {
        std::cout<< "x-value: "<< current->x << " y-value: "<< current->y <<" coord_id: "<< current->coord_id << std::endl;
        current = current->prev;
    }
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)//removes a coordinate from the linked list (free memory!)
{

}
int list_length(Coordinate *list_beginning)//return the length of the list
{

}
void closest_to(Coordinate *list_beginning, float x, float y);//find the coordinate that is closest to the given x, y and output the distance between the 2

int main(int argc, char **argv){

    //Coordinate* list_beginning = new Coordinate;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));//creating random unsigned integers using time operator of the ctime library.
    //We want floating point numbers that are unsigned.

    std::cout <<"Number of arguments: "<< argc << std::endl;//checking for correct number of command line arguments.
    if (argc != 2){
        std::cout<<"Not enough arguments"<<std::endl;
        return 1;
    }


    auto numCoords = std::atoi(argv[1]);

    Coordinate* front = nullptr;
    Coordinate* head = nullptr;
    for (auto i = 0; i < numCoords; i++)
    {
        // make random x
        auto x = std::rand() % 255;
        // make random y
        auto y = std::rand() % 255;

        std::cout<<"creating new coordinates: "<< x <<", "<< y << std::endl;

        if (head == nullptr)
        {
            head = new Coordinate(x, y);
            front = head;
            continue;
        }
        
        add_coordinate(&head, x, y);            

    }

    forward_display(front);
    std::cout << "======================"<<std::endl;
    backward_display(front);

    
    //std::cout << "the amount of x & y-values you requested: "<<x<<std::endl;




    return 0;
}