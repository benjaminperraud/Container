#include <iostream>

#include "Cont.hpp"
#include "MyType.hpp"

int main() {

    std::cout << std::boolalpha << "<<<" << std::endl;
    {
        std::cout << "***" << std::endl;

        Cont<MyType> *contMyType = new Cont<MyType>(20);   // test with defined type
        MyType str = MyType("43test");
        contMyType->insert({1, str});
        contMyType->insert({3, MyType("mot")});
        contMyType->insert({18, MyType("random")});
        std::cout << "find(str) (43test) : " << contMyType->find(str) << std::endl;
        std::cout << *contMyType << std::endl;

        std::cout << std::endl << "*** Utilisation d'un Cont de type effectif Vect ***" << std::endl << std::endl;

        Vect<Cont_base<int>::Ptr2Info> *vect = new Cont<int>(30);   // one parameter constructor
        vect->operator[](2) = 5;
        try{
            vect->operator[](2) = 10;
        }
        catch (const std::exception& e){
            std::cout << "Caught exception <" << e.what() << "> " << std::endl;
        }
        std::cout << "v[2] (5) : " << vect->at(2)  << std::endl;
        std::cout << "dim v (30) : " << vect->dim() << std::endl;
        *vect = Vect<Cont_base<int>::Ptr2Info>({10, 11, 12, 13});
        std::cout << "v[3] (13) : " << vect->at(3) << std::endl;
        std::cout << "dim v (4) : " << vect->dim() << std::endl;
        try{vect->at(25);}
        catch (const std::exception& e) {std::cout << "Caught exception <" << e.what() << "> " << std::endl;}

        std::cout << std::endl << "*** Utilisation d'un Cont de type effectif BST ***" << std::endl;

        BST<Cont_base<char>::Info> *bstchar = new Cont<char>(10);
        bstchar->insert({1, 'c'});
        bstchar->insert({5, 'b'});
        bstchar->insert({9, 'a'});
        std::cout << "output :" << *bstchar << std::endl;

        Cont_base<int>::Info info(12,15);
        BST<Cont_base<int>::Info> *bst = new Cont<int>(20);
        bst->insert(info);
        std::cout << "find(info) (15) : " << bst->find(info) << std::endl;
        bst->insert(Cont_base<int>::Info(12,17));
        std::cout << "find(15) (0) : " << bst->find(15) << std::endl;           // index updated, no more 15 at 12
        std::cout << "erase(15) false : " << bst->erase(15) << std::endl;
        std::cout << "find((12,17)) (17) : " << bst->find({12,17}) << std::endl;
        std::cout << "find((89,17)) (0) : " << bst->find({89,17}) << std::endl;
        std::cout << "find(17) (17) : " << bst->find(17) << std::endl;
        try{bst->insert({19, 17});}     // no duplicated element
        catch (const std::exception& e){std::cout << "Caught exception <" << e.what() << "> " << std::endl;}
        try{std::cout << "erase({5,17}) (exception) : " << bst->erase(Cont_base<int>::Info(5,17)) << std::endl;}
        catch (const std::exception& e){std::cout << "Caught exception <" << e.what() << "> " << std::endl;}
        std::cout << "erase({12,17}) (true) : " << bst->erase({12,17}) << std::endl;


        std::cout << std::endl << "*** Utilisation d'un Cont de type effectif Cont ***" << std::endl << std::endl;


        Cont_base<int>::Info t(7,52);
        Cont<int> *container = new Cont<int>(30) ;
        container->insert(t);
        container->insert(info);
        std::cout << "find (t) (52) : " << container->find(t) << std::endl;
        std::cout << "container[7] (52) : " << container->at(7) << std::endl;
        std::cout << "_used (2) : " << container->getUsed() << std::endl;
        std::cout << "erase (t) (true) : " << container->erase(t) << std::endl;
        std::cout << "container[7] (0) : " << container->at(7) << std::endl;
        std::cout << "_used (1) : " << container->getUsed() << std::endl;

        Cont<int> *container2 = new Cont<int>({1,2,3,4,5,6,7}) ;
        std::cout << "find (3) (3) : " << container2->find(3) << std::endl;
        std::cout << *container2 << std::endl;

        std::cout << " " << std::endl;
        std::cout << "***** Copies/Transferts *****" << std::endl;
        std::cout << " " << std::endl;

        Cont<int> cont2(*container2) ;
        std::cout << cont2 << std::endl;
        Cont<int> cont3 = std::move(*container2) ;
        std::cout << cont3 << std::endl;

        std::cout << std::endl <<"***** Conversions *****" << std::endl << std::endl;

        // deduction guide pas de <T> à mettre avant Cont;
        Cont<int> *fromVect = new Cont(*vect);        // pseudo conversion d'un Vect vers un Cont
        std::cout << *fromVect << std::endl;

        BST<Cont_base<int>::Info> arb;
        arb.insert(3);
        try{Cont<int> cont5(arb);}        // wrong effectiv type
        catch (const std::exception& e){std::cout << "Caught exception <" << e.what() << "> " << std::endl;}

        bst->insert({4,23});
        bst->insert({6,11});
        bst->insert({9,2});
        Cont<int> *fromBST = new Cont(*bst);        // pseudo conversion d'un BST vers un Cont
        std::cout << "find(23) (23) : " << fromBST->find(23) << std::endl;
        //std::cout << "fromBST[6] (11) : " << fromBST->at(6) << std::endl;     // pas implementé
        std::cout << "_used (4) : " << fromBST->getUsed() << std::endl;

        std::cout << "*********" << std::endl;

        delete vect;
        delete bst;
        delete container;
        delete fromVect;
        delete fromBST;
    }
    std::cout << ">>>" << std::endl;
    return 0;
}
