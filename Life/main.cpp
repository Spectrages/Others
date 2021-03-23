#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <vector>
#include <time.h>

const int n = 18;
const char live = 'O';
const char dead = '.';


template<typename T> class VectorInVector
{
public:
    VectorInVector(size_t w, size_t h): width(w), data(w*h) {}
    T* operator[](size_t i) {return data.data()+i*height;}
    const T* operator[](size_t i) const {return data.data()+i*height;}
private:
    size_t width;
    std::vector<T> data;
    size_t height = data.size() / width;
};

template <typename T> int checklist(const T& life_array, int rows, int cols)
{
    int num_neighbors = 0;
    if(life_array[rows][cols + 1] == live) num_neighbors++;
    if(life_array[rows][cols - 1] == live) num_neighbors++;
    if(life_array[rows + 1][cols] == live) num_neighbors++;
    if(life_array[rows - 1][cols] == live) num_neighbors++;
    if(life_array[rows + 1][cols + 1] == live) num_neighbors++;
    if(life_array[rows - 1][cols + 1] == live) num_neighbors++;
    if(life_array[rows + 1][cols - 1] == live) num_neighbors++;
    if(life_array[rows - 1][cols - 1] == live) num_neighbors++;
    return num_neighbors;
}

template <typename T> void print(const T& life_array, int rows, int cols)
{
    for(rows = 0; rows < n + 2; rows++) {
        for(cols = 0; cols < n + 2; cols++) {
            std::cout << life_array[rows][cols] << ' '; }
        std::cout << '\n'; }
}

int main()
{
    srand(time(0));
    int rows = 0;
    int cols = 0;
    VectorInVector<char>life_array(n+2, n+2);
    VectorInVector<char>next_array(n+2, n+2);
    VectorInVector<char>repeat_array(n+2, n+2);
    int num_neighbors = 0;
    int num_gen = 0;
/******* GENERATION ********/
    for(rows = 0; rows < n + 2; rows++)
    {
        for(cols = 0; cols < n + 2; cols++)
        {
            int rand_num = (rand() % 2);
            if(rand_num == 0)
                next_array[rows][cols] = dead;
            else
                next_array[rows][cols] = live;
        }
    }
    /******* GAME START ********/
    for(num_gen = 0; num_gen < 300; num_gen++)
    {
        system("clear");
        for(rows = 0; rows < n + 2; rows++)
            for(cols = 0; cols < n + 2; cols++)
            {
                life_array[rows][cols] = next_array[rows][cols];
                repeat_array[rows][cols] = life_array[rows][cols];
            }

        std::cout << std::setw(10) <<"Generation: " << num_gen + 1 << "\n\n";
        print(life_array, rows, cols);
        usleep(100000);

        for(rows = 0; rows < n + 2; rows++)
            {
            for(cols = 0; cols < n + 2; cols++)
            {
                std::cout << '\n';
                if(life_array[rows][cols] == dead)
                {
                    num_neighbors = checklist(life_array, rows, cols);
                    if(num_neighbors == 3)
                    {
                        next_array[rows][cols] = live;
                        num_neighbors = 0;
                    }
                }
                else
                {
                    num_neighbors = checklist(life_array, rows, cols);
                    if(num_neighbors == 2 || num_neighbors == 3)
                    {
                        next_array[rows][cols] = live;
                        num_neighbors = 0;
                    }
                    else
                    {
                        next_array[rows][cols] = dead;
                        num_neighbors = 0;
                    }
                }
            }
        }
    }
 return 0;
}
