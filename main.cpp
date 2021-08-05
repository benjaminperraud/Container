#include <iostream>
#include <typeinfo>

#include "Cont.hpp"

#include <vector>



int main() {

    std::cout << std::boolalpha << "<<<" << std::endl;
    {                                         // Test de Cont
        std::cout << "***" << std::endl;

        Cont_base<int>::Info y(1,12);

        BST<int> *x = new Cont<int>(3);   // one parameter constructor

        //BST<int> *x = reinterpret_cast<BST<int> *>(new Cont<int>(3));   // one parameter constructor

        x->insert(3);

        Cont_base<int>::Info t(1,12);

        int p = 3;
        p = t;

        std::cout << "p = " << p << std::endl;

        //Cont<int> *i = new Cont<int>(34);   // one parameter constructor

        Cont<int> *i = new Cont<int>(34);   // one parameter constructor

        i->insert(0, 9);

        std::cout << i[0] << std::endl;        // pas un pointeur affiche bien, avec pointeur appel à dsp

        i->insert(0, 6);

        std::cout << i[1] << std::endl;

        i->insert(1, 90);

        //std::cout << i[1] << std::endl;


        Vect<int> *o = new Cont<int>(34);   // one parameter constructor



//        std::cout << "x.dim = " << x.dim() << std::endl;
//        std::cout << "x = " << x << std::endl;


//        std::cout << "x[1] = " << x[1] << std::endl;
//        x[0] = i; x[2] = 1515;
//        std::cout << "x = " << x << std::endl;
//        std::cout << "x[2] = " << x[2] << std::endl;
//        const Cont y(x);
//        std::cout << "y.dim = " << y.dim() << std::endl;
//        std::cout << "y = " << y << std::endl;
//        std::cout << "x = " << x << std::endl;
//        std::cout << "y[2] = " << y[2] << std::endl;


//        x[1] = -1;
//        Cont z = std::move(x);   // vrai transfert
//        std::cout << "z.dim = " << z.dim() << std::endl;
//        std::cout << "z = " << z << std::endl;
//        std::cout << "x.dim = " << x.dim() << std::endl;
//        std::cout << "x = " << x << std::endl;
//        // Vect_dyn<int> u0 = {1, 2, 3.14, true, 'a'};  // Erreur
//        Cont<float> u0 = {1, 2.0l, 3.14, true, 'a'};   // ???
//        std::cout << "u0.dim = " << u0.dim() << std::endl;
//        std::cout << "u0 = " << u0 << std::endl;
//        std::cout << "type(u0) = " << typeid_name(u0) << std::endl;
//        Cont u = {1, 2, 3, 4};
//        std::cout << "u.dim = " << u.dim() << std::endl;
//        std::cout << "u = " << u << std::endl;
//        std::cout << "type(u) = " << typeid_name(u) << std::endl;
//        Cont v0(5, {1, 2, 3, 4, 5, 6, 7, 8});
//        std::cout << "v0.dim = " << v0.dim() << std::endl;
//        std::cout << "v0 = " << v0 << std::endl;
//        Cont v(5, {1, 2, 3});
//        std::cout << "v.dim = " << v.dim() << std::endl;
//        std::cout << "v = " << v << std::endl;
        std::cout << "***" << std::endl;
    }


}
