#include <iostream>

class SuperAncestor {
public:
    void sayHello() {
        std::cout << "I'm a class." << std::endl;
    }
};

class DescendantA : virtual public SuperAncestor {

};

class DescendantB : virtual public SuperAncestor {

};

class MultipleDescendant : public DescendantA, public DescendantB {

};


int main() {
    MultipleDescendant example;
    example.sayHello();
}