#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include "coordinate.h"

void add_coordinate(Coordinate **head, float x, float y)//adds a coordinate to the end of the linked list. (Using double pointers :D).
{
    auto * newCoord = new Coordinate(x, y);//Allocating memory for coordinates x,y
    newCoord->coord_id = (*head)->coord_id + 1;
    newCoord->prev = (*head);
    (*head)->next = newCoord;
    *head = newCoord;
}

void forward_display( Coordinate *list_beginning)//displays all coordinates from beginning to end.
{
    auto current = list_beginning;
    while(current != nullptr)//While loop to iterate over list FROM FIRST NODE (coord id = 0).
    {
        std::cout << "("<< current->x << ", "<< current->y <<") Coord_id: "<< current->coord_id << std::endl;
        current = current->next;//pointing our current pointer  to the next node, which points to the data in that node.
        
    }
}

void backward_display(Coordinate *list_beginning)// displays all coordinates from end to beginning. 
{
    auto current = list_beginning;
    while(current->next != nullptr)
    {
        current = current->next;
    }

    
    while(current != nullptr)//end of linked list will have our next node->nullptr. Source: https://www.geeksforgeeks.org/dsa/introduction-and-insertion-in-a-doubly-linked-list/ 
    {
        std::cout <<"("<< current->x << ", "<< current->y <<") coord_id: "<< current->coord_id << std::endl;
        current = current->prev;
    }
}

void delete_coordinate(Coordinate **list_beginning, int coord_id_to_delete)//removes a coordinate from the linked list (free memory!)
{
    auto current = *list_beginning;

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
                *list_beginning = current->next;

            }
            auto nextNode = current->next;
            if(nextNode != nullptr)
                nextNode->prev = prevNode;


            delete current;
            std::cout << "Deleting coordinate with id: "<< coord_id_to_delete << std::endl;
            break;
        }
        
        current = current->next;

    }
}

int list_length(Coordinate *list_beginning)//return the length of the list
{
    int count = 0;
    auto current = list_beginning; 

    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}


float calc_dist(float x1, float y1, float x2, float y2)//Using pythagoras identity to calculate distance.
{
    float dx = (x2 - x1);
    float dy = (y2 - y1);

    float distance = std::sqrt((std::pow(dx, 2)) + (std::pow(dy, 2)));

    return distance;
}


void closest_to(Coordinate *list_beginning, float x, float y)//find the coordinate that is closest to the given x, y and output the distance between the 2
{//Randomly generated x,y coordinate and 
    auto current = list_beginning;
    auto dist = std::numeric_limits<float>::max();//Initial large and best distance we're comparing actual dist to. 
    auto closestId = -1;//-1 is invalid score, "none found yet."

    while (current != nullptr)
    {
        auto tempDist = calc_dist(current->x, x, current->y, y);
        std::cout << "Distance for id " << current->coord_id << ": " << tempDist << std::endl;
        if(tempDist < dist)
        {
            dist = tempDist;
            closestId = current->coord_id;
        }
        current = current->next;
    }

    if (closestId >= 0) 
    {
        std::cout << "Closest coord to (" << x << ", " << y << ") is id: " << closestId
                  << "  Distance: " << dist << std::endl;
    } 
    else 
    {
        std::cout << "No nearest coordinate found." << std::endl;
    }
}

void free_memory(Coordinate *list_beginning)
{
    Coordinate* current = list_beginning;
    while(current != nullptr)//Iterate through each node.
    {
        auto next = current->next;
        delete current;
        current = next;
    }
    std::cout << "linked list memory successfully deleted. "<< std::endl;
}

int main(int argc, char **argv){

    std::srand(static_cast<unsigned int>(std::time(nullptr)));//creating random unsigned integers using time operator of the ctime library.
    //We want floating point numbers that are unsigned.

    std::cout <<"Number of arguments: "<< argc << std::endl;//checking for correct number of command line arguments.
    if (argc != 2){
        std::cout<<"Not enough arguments"<<std::endl;
        return 1;
    }

    auto numCoords = std::atoi(argv[1]);
    std::cout<< "Number of coordinates to generate: "<< numCoords <<std::endl;

    Coordinate* list_beginning = nullptr;
    Coordinate* head = nullptr;


    for (auto i = 0; i < numCoords; i++)//Generating coordinates bound by the range of 0 to 255.
    {
        // make random x
        auto x = std::rand() % 255;
        // make random y
        auto y = std::rand() % 255;

        std::cout << "Creating new coordinate(range is between 0 and 255): "<< x <<", "<< y << std::endl;

        if (head == nullptr)
        {
            head = new Coordinate(x, y);
            list_beginning = head;
            continue;
        }
        
        add_coordinate(&head, x, y);            

    }

    //forward display function
    std::cout << "Forward Display: "<< std::endl;
    forward_display(list_beginning);
    std::cout << "======================"<<std::endl;

    //backward display function
    std::cout << "Backward Display: " << std::endl;
    backward_display(list_beginning);
    std::cout << "======================"<<std::endl;

    // make random x
    auto x = std::rand() % 255;
    // make random y
    auto y = std::rand() % 255;
    closest_to(list_beginning, x, y);//calling closest to function and passing in new generated coordinates as args.
    std::cout << "======================"<<std::endl;

    std::cout << "List length: " 
        << list_length(list_beginning)<<std::endl;
        std::cout << "======================"<<std::endl;   

    //assigning coord_id to delete and calling delete coordinate function. 
    auto coord_id_to_delete = 1;
    delete_coordinate(&list_beginning, coord_id_to_delete);
    forward_display(list_beginning);


    //Testing corner cases at the list_beginning and tail of 5 generated coords. 
    coord_id_to_delete = 4;
    delete_coordinate(&list_beginning, coord_id_to_delete);
    forward_display(list_beginning);
    coord_id_to_delete = 0;
    delete_coordinate(&list_beginning, coord_id_to_delete);
    forward_display(list_beginning);
     std::cout << "======================"<<std::endl;

    std::cout << "List length after deleting coordinates: " 
        << list_length(list_beginning)<<std::endl;
        std::cout << "======================"<<std::endl;        

    free_memory(list_beginning);

    return 0;
}