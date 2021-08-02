#include <iostream>
#include <typeinfo>


int main() {

    std::cout << "Hello" << std::endl;

    int* c = new int(21);

    delete c;

    if (c){

    }
    return 0;
}
