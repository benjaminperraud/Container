#include <iostream>
#include <typeinfo>

#include "Cont.hpp"

#include <vector>



int main() {

    std::cout << std::boolalpha << "<<<" << std::endl;
    {                                         // Test de Cont
        std::cout << "***" << std::endl;
        int i = 42;

        Cont_base<int>::Info t(1,12);

        //BST<Cont_base<int>::Ptr2Info> *x = new Cont<int>(5);   // one parameter constructor

        //BST<int> *x = new BST<int>();   // one parameter constructor

        //BST<Cont_base<int>::Ptr2Info> *x = new Cont<int>();   // one parameter constructor

        Cont<int> *x = new Cont<int>(5);   // one parameter constructor

        //Cont_base<int>::Info y(1,12);

        //x->insert(1, t);    // conversion de Info vers Ptr_Info via operateur()

        x->insert(1, 3);    // conversion de int vers Ptr_Info implicit !           -> pas de polymoprhisme possible car méthode pas redefinissable !

        std::cout << "find(3) :" << x->find(3) << std::endl;

        x->insert(1, 9);    // conversion de int vers Ptr_Info implicit !           -> pas de polymoprhisme possible car méthode pas redefinissable (pas les memes parametres) !

        std::cout << "find(3) :" << x->find(3) << std::endl;
        std::cout << "find(9) :" << x->find(9) << std::endl;

        std::cout << x->operator[](1) << std::endl;

        x->erase(1,9);

        std::cout << "find(9) :" << x->find(9) << std::endl;

        std::cout << x->operator[](1) << std::endl;

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
