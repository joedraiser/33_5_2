#include <iostream>
#include <cstdlib>
#include <ctime>

enum fishingResult { FISH, BOOT, NONE };

class Cell
{
public:
    Cell() {};

    virtual void get() = 0;
};

class Fish : public Cell
{
public:
    Fish() {};

    virtual void get()
    {
        throw FISH;
    }
};

class None : public Cell
{
public:
    None() {};

    virtual void get()
    {
        throw NONE;
    }
};

class Boot : public Cell
{
public:
    Boot() {};

    virtual void get()
    {
        throw BOOT;
    }
};

struct cells
{
    Cell* fish;

    ~cells()
    {
        delete fish;
    }
};

int main()
{

    cells field[9];

    for(int i=0;i<9;i++)
        field[i].fish=new None();

    std::srand(std::time(nullptr));
    field[std::rand() % 9].fish = new Fish();

    for(int i=0;i<3;i++)
    {
        while(true)
        {
            int temp = std::rand() % 9;
            try
            {
                field[temp].fish->get();
            }
            catch(fishingResult result)
            {
                if(result==NONE)
                {
                    field[temp].fish=new Boot();
                    break;
                }
            }
        }
    }

    int cellNum, tries=1;

    while(true)
    {

        try
        {
            std::cout << "Input cell num: ";
            std::cin >> cellNum;


            field[cellNum].fish->get();
        }
        catch (fishingResult result)
        {
            if(result == NONE)
            {
                std::cout << "Miss!\n";
                tries++;
            }
            else if(result == BOOT)
            {
                std::cout << "Boot!\nNumber of tries: " << tries;
                return 1;
            }
            else if(result == FISH)
            {
                std::cout << "Fish!\nNumber of tries: " << tries;
                return 0;
            }
        }
    }

    return 0;
}
