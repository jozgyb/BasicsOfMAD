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

class Secret {
public:
    Secret(std::string password0) {
        password = password0;
    }
    std::string getPassword() {
        return password;
    }
private:
    std::string password;
};

class Gossip: private Secret {
public:
    Gossip(std::string password = "asd") : Secret(password) {

    }

    void tellPassword(){
        std::cout << "I'm gonna tell you the secret password but I need the getter for it, because i got the information privately." << std::endl;
        std::cout << "The password is: " << Secret::getPassword() << std::endl;
    }
};


int main() {
//    Diamond problem! If we remove the virtual keywords at the inheritance part, we will get an error, because MultipleDescendant
//    derives from DescendantA and DescendantB, which each have there copy of their sayHello() method.
//    Thats why we make the inheritance virtual, this C++ will ensure that only one subobject of the
//    SuperAncestor class will be created for every MultipleDescendant object.
    MultipleDescendant example;
    example.sayHello();


    Gossip gossip;
    gossip.tellPassword();
}