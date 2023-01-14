#include <iostream>

class Headman;

class Locality {
public :
    int population;
    int food;
};

class Village: public Locality {
    friend Headman;
    friend void addMoney(Village& village);
    friend void showMoney(Village& village);
public:
    explicit Village(int startingPopulation) : Locality() {
        population = startingPopulation;
        money = 100;
    }

    Village() : Locality() {
        population = 0;
        money = 0;
    }

private:
    int money;
};

class Headman {
public:
    std::string name;

    explicit Headman(std::string newName) {
        name = newName;
    }

    void spendMoney(Village& village) {
        if (village.money > 0) village.money--;
    }
};

void addMoney(Village& village) {
    village.money += 100;
}

void showMoney(Village& village) {
    std::cout << village.money;
}

int main() {
    Headman headman {"John"};
    Village village{50};
    headman.spendMoney(village);

    addMoney(village);

    showMoney(village);

    return 0;
}
