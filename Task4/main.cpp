#include <iostream>

class Locality {
public :
    int population;
    int food;
};

class Village: public Locality {
public:
    explicit Village(int startingPopulation) : Locality() {
        population = startingPopulation;
    }

    Village() : Locality() {
        population = 0;
    }

    void growFood() {
        food += 5;
    }
};

Village operator+= (Village& village, int population){
    village.population += population;
    return village;
}

int main() {
    Village village1;
    village1 += 4;

    Village village2 {5};

    std::cout << village2.population;

    return 0;
}
