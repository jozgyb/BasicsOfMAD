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
//    Diamond problem! If we remove the virtual keywords at the inheritance part, we will get an error, because MultipleDescendant
//    derives from DescendantA and DescendantB, which each have there copy of their sayHello() method.
//    Thats why we make the inheritance virtual, this C++ will ensure that only one subobject of the
//    SuperAncestor class will be created for every MultipleDescendant Obejct.
    MultipleDescendant example;
    example.sayHello();
}