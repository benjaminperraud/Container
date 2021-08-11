#include <iostream>
#include <typeinfo>

#include "Cont.hpp"

#include <vector>



int main() {

    std::cout << std::boolalpha << "<<<" << std::endl;
    {                                         // Test de Cont
        std::cout << "***" << std::endl;

        Cont_base<int>::Info t(15,12);
        Cont_base<int>::Info info(2,5);

//        BST<Cont_base<int>::Info> arb ;
//        arb.insert(t);
//        std::cout << "find(t) :" << arb.find(t) << std::endl;
//
//        BST<Cont_base<int>::Info> bra = BST<Cont_base<int>::Info>(arb) ;
//        std::cout << "find(t) :" << bra.find(t) << std::endl;

        //Cont_base<int>::PtrInfo ptr(15,12);
        //Vect<Cont_base<int>::Ptr2Info> x = Vect<Cont_base<int>::Ptr2Info>(5);
        //Vect<int> x = Vect<int>(5);
        //Vect<Cont_base<int>::Ptr2Info> *x = new Cont<int>(20);   // one parameter constructor

//        Vect<Cont_base<int>::Ptr2Info> x = Vect<Cont_base<int>::Ptr2Info>(20);
//        BST<Cont_base<int>::Info> m = BST<Cont_base<int>::Info>();
//
//        x[1] = 1;
//        x[2] = 2;
//        x[15] = 12;
//
//
//        m.insert(t);
//        m.insert(info);
//
//        std::cout << "find(t) :" << m.find(t) << std::endl;

        Cont<int> cont ;

        //std::cout << "find t : " << cont.find(t) << std::endl;          -> erreur si cont pas initalisé, normal ?

        cont = Cont<int>(30);


        std::cout << "find 9 in cont2 :" << cont.find(9) << std::endl;
        std::cout << "find 15 in cont2 :" << cont.find(15) << std::endl;
        std::cout << "find t in cont2 : " << cont.find(t) << std::endl;

        std::cout << "_used : " << cont.getUsed() << std::endl;


//        Cont<int> *j = new Cont(m);          // deduction guide donc pas de <T> à mettre avant Cont;
//
//        std::cout << "find(t) :" << j->find(t) << std::endl;
//
//        std::cout << "index 3" << j->operator[](3) << std::endl;
//        std::cout << "index 2" << j->operator[](2) << std::endl;

        //j->operator[](2) = 5;                                             // compile pas car de type Cont, pas de modificateur de _val

        //j->insert(t);
//
//        std::cout << j->operator[](15) << std::endl;
//        std::cout << j->at(15) << std::endl;
//        std::cout << j->dim() << std::endl;
//
//        std::cout << "find(t) :" << j->find(t) << std::endl;

//        Vect<Cont_base<int>::Ptr2Info> *v = new Cont<int>(50);   // one parameter constructor
//        //BST<Cont_base<int>::Info> *x = new Cont<int>(5);   // one parameter constructor
//
//        v->operator[](2) = 5;
//
//        std::cout << v->at(2) << std::endl;
//        std::cout << v->operator[](2) << std::endl;
//        std::cout << v->dim() << std::endl;

//
//
//        x->insert(t);    // conversion de int vers Info implicit ?
//        std::cout << "find(t) :" << x->find(t) << std::endl;
//        std::cout << "find(Info(2,12)) :" << x->find(Cont_base<int>::Info(2,12)) << std::endl;
//        std::cout << x->operator[](15) << std::endl;
//        std::cout << "find(12) :" << x->find(12) << std::endl;
//        x->erase(t);
//        std::cout << "find(12) :" << x->find(12) << std::endl;
//        x->insert(Cont_base<int>::Info(2,9));    // conversion de int vers Ptr_Info implicit ?           -> pas de polymoprhisme possible car méthode pas redefinissable !
//        std::cout << x->operator[](2) << std::endl;
//        std::cout << "find(9) :" << x->find(9) << std::endl;
//        x->erase(9);
//        std::cout << "find(9) :" << x->find(9) << std::endl;
//        std::cout << x->operator[](2) << std::endl;

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
