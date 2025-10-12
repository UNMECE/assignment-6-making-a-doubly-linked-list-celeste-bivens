#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
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
        std::cout << current->x << ", "<< current->y <<" coord_id: "<< current->coord_id << std::endl;
        current = current->prev;
    }
}

void delete_coordinate(Coordinate **front, int coord_id_to_delete)//removes a coordinate from the linked list (free memory!)
{

    Coordinate* current = *front;

    while(current != nullptr)
    {
        if(current->coord_id == coord_id_to_delete)
        {
            auto prevNode = current->prev;
            if(prevNode != nullptr)
            {
                prevNode->next = current->next;//updating the previous and next pointers.
            }
            else
            {
                *front = current->next;

            }
            auto nextNode = current->next;
            if(nextNode != nullptr)
                nextNode->prev = prevNode;


            delete current;
            std::cout << "deleting coordinate: "<< coord_id_to_delete << std::endl;
            break;
        }
        
        current = current->next;

    }
}
int list_length(Coordinate *front)//return the length of the list
{
    int count = 0;
    auto current = front; 

    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}


float calc_dist(float x, float x2, float y, float y2)
{
    float xdifference = (x2 - x);
    float ydifference = (y2 - y);

    float distance = std::sqrt((std::pow(xdifference, 2)) + (std::pow(ydifference, 2)));

    return distance;
}


void closest_to(Coordinate *front, float x, float y)//find the coordinate that is closest to the given x, y and output the distance between the 2
{
    auto current = front;
    auto dist = std::numeric_limits<float>::max();
    auto closestId = -1;

    while (current != nullptr)
    {
        auto tempDist = calc_dist(current->x, current->y,x,y);
        std::cout << "distance for id " << current->coord_id << ": " << tempDist << std::endl;
        if(tempDist < dist)
        {
            dist = tempDist;
            closestId = current->coord_id;
        }
        current = current->next;
    }

    if (closestId >= 0) {
        std::cout << "Closest coord to ( " << x << ", " << y << " ) is id: " << closestId
                  << "  Distance: " << dist << std::endl;
    } else {
        std::cout << "No nearest coordinate found." << std::endl;
    }
}

void free_memory(Coordinate *front)
{
    Coordinate* current = front;
    while(current != nullptr)
    {
        auto next = current->next;
        delete current;
        current = next;
    }
    std::cout << "linked list memory successfully deleted. "<< std::endl;
}

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


    for (auto i = 0; i < numCoords; i++)//Generating coordinates bound by the range of 0 to 255.
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
    std::cout << "======================"<<std::endl;

    auto coord_id_to_delete = 1;
    delete_coordinate(&front, coord_id_to_delete);
    forward_display(front);
    //Testing corner cases at the front and tail of my list. 
    coord_id_to_delete = 4;
    delete_coordinate(&front, coord_id_to_delete);
    forward_display(front);
    coord_id_to_delete = 0;
    delete_coordinate(&front, coord_id_to_delete);
    forward_display(front);

    std::cout << "======================"<<std::endl;
    std::cout << "List length: " << list_length(front)<<std::endl;

    std::cout << "======================"<<std::endl;
        // make random x
    auto x = std::rand() % 255;
    // make random y
    auto y = std::rand() % 255;
    closest_to(front, x, y);
    std::cout << "======================"<<std::endl;
    free_memory(front);

    return 0;
}