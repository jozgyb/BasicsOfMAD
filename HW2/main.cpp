#include <iostream>

class RealSheep {
    int sheep_id;
public:
    RealSheep(int i) {
        sheep_id = i;
        std::cout << "I'm a sheep and alive. My ID is: " << sheep_id << std::endl;
    }
    ~RealSheep(){
        std::cout << "I'm sheep " << sheep_id << " and I'll leave." << std::endl;
    }
    void baa() {
        std::cout << "Sheep " << sheep_id << "is making a noise." << std::endl;
    }

};

class Sheep {
    RealSheep *theRealSheep;
    int sheep_id;
    static int s_next;

public:
    Sheep() {
        sheep_id = s_next++;
        theRealSheep = 0;
    }
    ~Sheep() {
        delete theRealSheep;
    }

    void baa() {
        if(!theRealSheep) {
            theRealSheep = new RealSheep(sheep_id);
        }
        theRealSheep->baa();
    }
};

int Sheep::s_next = 1;

int main() {
    Sheep herd[10];
    int i;

    while(true) {
        std::cout << "Welcome to the farm which sheep do you want to hear ?" << std::endl;
        std::cout << "ID range is from 1 to 10" << std::endl;
        std::cout << "Type 0 to leave the farm" << std::endl;
        std::cin >> i;
        if (i == 0){
            break;
        }
        herd[i - 1].baa();
    }
}