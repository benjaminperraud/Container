#include <iostream>

#include "Cont.hpp"
#include "MyType.hpp"

int main() {

    std::cout << std::boolalpha << "<<<" << std::endl;
    {                                         // Test de Cont
        std::cout << "***" << std::endl;

        std::cout << "*** Utilisation d'un Cont de type effectif Vect ***" << std::endl;

        Vect<Cont_base<int>::Ptr2Info> *vect = new Cont<int>(30);   // one parameter constructor
        vect->operator[](2) = 5;
        std::cout << "v[2] (5) : " << vect->at(2) << ", " << vect->operator[](2) << std::endl;
        std::cout << "dim v (30) : " << vect->dim() << std::endl;
        *vect = Vect<Cont_base<int>::Ptr2Info>({10, 11, 12, 13});
        std::cout << "v[3] (13) : " << vect->at(3) << ", " << vect->operator[](3) << std::endl;
        std::cout << "dim v (4) : " << vect->dim() << std::endl;
        try{
            vect->at(25);
        }
        catch (const std::exception& e){
            std::cout << "Caught exception <" << e.what() << "> " << std::endl;
        }

        std::cout << "*** Utilisation d'un Cont de type effectif BST ***" << std::endl;

        Cont_base<int>::Info info(12,15);
        BST<Cont_base<int>::Info> *bst = new Cont<int>(20);
        bst->insert(info);
        std::cout << "find(info) (15) : " << bst->find(info) << std::endl;
        bst->insert(Cont_base<int>::Info(12,17));
        std::cout << "find(15) (0) : " << bst->find(15) << std::endl;           // index updated, no more 15 at 12
        std::cout << "erase(15) false : " << bst->erase(15) << std::endl;
        std::cout << "find((12,17)) (17) : " << bst->find({12,17}) << std::endl;            // error également
        std::cout << "find(17) (17) : " << bst->find(17) << std::endl;
        try{
            bst->insert({5, 17});
        }
        catch (const std::exception& e){
            std::cout << "Caught exception <" << e.what() << "> " << std::endl;
        }
        bst->erase(17);
        try{
            std::cout << "erase(17) : " << bst->erase(Cont_base<int>::Info(12,17)) << std::endl;
        }
        catch (const std::exception& e){
            std::cout << "Caught exception <" << e.what() << "> " << std::endl;
        }

        std::cout << "*** Utilisation d'un Cont de type effectif Cont ***" << std::endl;

        Cont_base<int>::Info t(7,52);
        Cont<int> *container = new Cont<int>(30) ;
        container->insert(t);
        container->insert(info);
        std::cout << "find (t) (52) : " << container->find(t) << std::endl;
        std::cout << "container[7] (52) : " << container->at(7) << std::endl;
        std::cout << "_used (2) : " << container->getUsed() << std::endl;


//        Cont<int> *cont2 = new Cont<int>({1,2,3,4,5}) ;             // initialization list      -> copie dans vect puis constructeur de CONVERSION
//        std::cout << "find (3) (3) : " << cont2->find(3) << std::endl;
//        std::cout << "cont2[4] (5) : " << cont2->operator[](4) << std::endl;
//        std::cout << "_used (5) " << cont2->getUsed() << std::endl;

        // Conversions


        std::cout << "***** Copies/Transferts *****" << std::endl;

        Cont<int> cont2(*container) ;           // constructeur de copie de Cont
        std::cout << "find ({7,52}) (52) : " << cont2.find({7,52}) << std::endl;
        std::cout << "find (52) (52) : " << cont2.find(52) << std::endl;
        std::cout << "find (15) (15) : " << cont2.find(15) << std::endl;
        std::cout << "cont2[7] (52) : " << cont2.at(7) << std::endl;
        std::cout << "_used (2) " << cont2.getUsed() << std::endl;


        std::cout << "***** Conversions *****" << std::endl;

        // deduction guide pas de <T> à mettre avant Cont;
        Cont<int> *fromVect = new Cont(*vect);        // pseudo conversion d'un Vect vers un Cont
        std::cout << "find({2,13}) (0) : " << fromVect->find({2,13}) << std::endl;
        std::cout << "find (13) (13) : " << fromVect->find(13) << std::endl;
        std::cout << "_used (4) " << fromVect->getUsed() << std::endl;


        BST<Cont_base<int>::Info> arb;
        arb.insert(3);
        try{
            Cont<int> cont5(arb);        // wrong effectiv type
        }
        catch (const std::exception& e){
            std::cout << "Caught exception <" << e.what() << "> " << std::endl;
        }

        bst->insert({4,23});
        bst->insert({6,11});
        bst->insert({9,2});
        Cont<int> *fromBST = new Cont(*bst);        // pseudo conversion d'un BST vers un Cont
        std::cout << "find(23) (23) : " << fromBST->find(23) << std::endl;
        //std::cout << "fromBST[6] (11) : " << fromBST->at(6) << std::endl;
        std::cout << "_used (4) : " << fromBST->getUsed() << std::endl;


        *container = *bst;                          // pseudo conversion d'un BST vers un Cont
        std::cout << "find(23) (23) : " << container->find({4,23}) << std::endl;
        //std::cout << "fromBST[6] (11) : " << fromBST->at(6) << std::endl;
        std::cout << "_used (4) : " << container->getUsed() << std::endl;

        // manque test assignement d'un vect

        std::cout << "*********" << std::endl;
        delete vect;
        delete bst;
        delete container;


//    std::cout << "***** Output *****" << std::endl;
//
//    BST<Cont_base<int>::Info> *bst = new Cont<int>(20);
//
//    bst->insert({1,13});
//    bst->insert({2,4});
//    bst->insert({19,980});
//
//    std::cout << *bst << std::endl;
//
//
//    Cont<int> *contai = new Cont<int>(20);
//
//    contai->insert({1,13});
//    contai->insert({2,4});
//    contai->insert({19,980});
//
//    std::cout << *contai << std::endl;



        // Cont<int> *cont3 = new Cont<int>(*cont2);
//
//        BST<Cont_base<int>::Info> arb ;
//
////        Cont_base<int>::PtrInfo ptr(15,12);
////        Vect<Cont_base<int>::Ptr2Info> x = Vect<Cont_base<int>::Ptr2Info>(5);
////        Vect<int> x = Vect<int>(5);
////        Vect<Cont_base<int>::Ptr2Info> *x = new Cont<int>(20);   // one parameter constructor
//
//        BST<Cont_base<int>::Info> *bst = new Cont<int>();
//
//        auto *l = new BST<Cont_base<int>::Info>();
//
//        auto *x = new Cont<int>(10);
//
//        *x = *bst;
//        *x = *l;
//
//
//
//


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
    std::cout << ">>>" << std::endl;
    return 0;
}
