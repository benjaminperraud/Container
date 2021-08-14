/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Benjamin Perraudin - 2021/08 - <Cont.hpp>
 * Exemple de conteneur (projet n°1)
 */
#ifndef _CONT_H_
#define _CONT_H_

#include  "Vect.hpp"
#include  "BST.hpp"
#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <utility>             // swap, move, forward...
#include  <exception>
#include  <stdexcept>           // standard exceptions
#include  <ostream>             // output streams

// Common output operator ====================================================

namespace _Cont_base {
  namespace {
    template <typename U>
    struct _Base {
      constexpr void _dsp (std::ostream& out) const
        {static_cast<const U*>(this)->_dsp(out);}
    };
  }
}

template <typename U>
std::ostream& operator<< (std::ostream& out, const _Cont_base::_Base<U>& b)
    {b._dsp(out); return out;}

// Abstract base class =======================================================

template <typename T>
class Cont_base { // abstract
public:
    class Info;               // make class Info local
    class Ptr2Info;
protected:
  static const Info _EMPTY;
  // Access methods
  static constexpr std::ptrdiff_t _index (const Info& i) {return i._index;}
  static constexpr std::ptrdiff_t& _index (Info& i) {return i._index;}
  static constexpr const Info* _ptr (const Ptr2Info& p) {return p._ptr;}
  static constexpr const Info*& _ptr (Ptr2Info& p) {return p._ptr;}
  // Implementation
  std::size_t _used = 0;
  virtual void _dsp (std::ostream&) const = 0;
  // Non virtual assignations => protected
  Cont_base& operator= (const Cont_base&) = default;
  Cont_base& operator= (Cont_base&& c)
    {if (this != &c) {_used = c._used; c._used = 0;} return *this;}
public:
  // Getter
  constexpr std::size_t used () const noexcept {return _used;};
  // Constructors & destructor
  constexpr Cont_base () noexcept = default;
  constexpr Cont_base (const Cont_base&) noexcept = default;
  constexpr Cont_base (Cont_base&& c) noexcept: _used(c._used) {c._used = 0;}
  virtual ~Cont_base () noexcept = default;
};

// Cont_base<T>
template <typename T>
const typename Cont_base<T>::Info Cont_base<T>::_EMPTY{};     // Info _EMPTY attribute initialize

// Embedded class Info =======================================================

template <typename T>
class Cont_base<T>::Info : public _Cont_base::_Base<typename Cont_base<T>::Info> {      // class Info inherit from struct _Base define in _Cont_Base
  friend class Cont_base<T>;   // for _index static methods
  std::ptrdiff_t _index = -1;
  const T _data{};
  friend struct _Cont_base::_Base<Info>;
  constexpr void _dsp (std::ostream& out) const {out << _data;}
public:
  // Traits
  using value_type      = T;
  using reference       = T&;
  using const_reference = const T&;
  // Constructors & casts
  constexpr Info () noexcept = default;
  constexpr Info (std::ptrdiff_t i, const T& v) noexcept: _index(i), _data(v) {}
  constexpr Info (const T& v) noexcept: _data(v) {}             // implicit cast
  constexpr operator const T& () const noexcept {return _data;} // implicit cast
  template <typename> friend constexpr bool operator< (const Info&, const Info&) noexcept;
  template <typename> friend constexpr bool operator== (const Info&, const Info&) noexcept;
  constexpr bool operator< (const Info& i) const noexcept
    {return _data < i._data;}
  constexpr bool operator== (const Info& i) const noexcept
    {return _data == i._data;}
}; // Info

//template<typename T>
//constexpr bool operator==(const typename Cont_base<T>::Info &i, const typename Cont_base<T>::Info &j) noexcept {
//    return i._data == j._data && i._index == j._index;
//}

// Embedded class Ptr2Info ===================================================

template <typename T>
class Cont_base<T>::Ptr2Info: public _Cont_base::_Base<typename Cont_base<T>::Ptr2Info> {
    friend class Cont_base<T>;   // for _ptr static methods
  const Info *_ptr = nullptr;
  friend struct _Cont_base::_Base<Ptr2Info>;
  constexpr void _dsp (std::ostream& out) const
    {out << (_ptr ? *_ptr : _EMPTY);}
public:
  // Traits
  using value_type      = T;
  using reference       = T&;
  using const_reference = const T&;
  // Constructors & casts
  constexpr Ptr2Info () noexcept = default;
  constexpr Ptr2Info(T i) : _ptr(new Info(i))  {};       // implicit cast from T to Ptr2Info
  constexpr operator const Info& () const noexcept       // implicit cast
    {return _ptr ? *_ptr : _EMPTY;}
    constexpr operator const T& () const noexcept        // implicit cast -> from const T& to const Info
    {return _ptr ? *_ptr : _EMPTY;}
  // Getter
  constexpr bool isEmpty() const noexcept {return !_ptr;}
  constexpr bool operator< (const Ptr2Info& i) const noexcept
    {return _ptr->_data < i._ptr->_data;}
  constexpr bool operator== (const Ptr2Info& i) const noexcept
    {return _ptr->_data == i._ptr->_data;}
//constexpr bool operator== (const Ptr2Info& i) const noexcept
//{return _ptr->_data == i._ptr->_data && _ptr->_index == i._ptr->_index;}
}; // Ptr2Info

namespace _Cont_base {
  template <typename> using _Base = void;   // "destroy" access to real _Base
}

// Main class ================================================================

template <typename T>
class Cont final: private Cont_base<T>, public BST<typename Cont_base<T>::Info>, public Vect<typename Cont_base<T>::Ptr2Info> {
    using _Base = Cont_base<T>;
    using _Ptr2Info = typename _Base::Ptr2Info;
    using _Info = typename _Base::Info;
    using _Vect = Vect<_Ptr2Info>;
    using _BST  = BST<_Info>;
    using _Base::_index;
    using _Base::_ptr;
public:
    // Traits
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using Info = typename _Base::Info;
    using Ptr2Info = const _Ptr2Info;
    // Constructors
    constexpr Cont() noexcept = default;                                          // constructor without parameters
    explicit constexpr Cont(std::size_t t) noexcept: _BST(), _Vect(t){}           // constructor with maximum size of Cont
    Cont(const std::initializer_list<T> &init) noexcept;           // constructor with maximum size of Cont
    Cont(std::size_t t, const std::initializer_list<T> &init) noexcept;           // constructor with maximum size of Cont

    // pas compris : différence entre copie d'un vect de type Cont ou pas ???
    // vect de type cont peut contenir un arbre ou non, pas le vect simple, un probleme d'index -> forcément de type _Vect
    // un probleme de pointeur ? un Vect de type int doit ensuite être converti en Ptr2Info -> soucis ?

//    constexpr Cont (std::size_t t, const std::initializer_list<T> &init) noexcept: _BST(), _Vect(t, init){
//        for(auto object : {init}) {
//            std::cout << object << std::endl;
//            Cont_base<T>::_used += 1;
//        }
//    }

    // Setters
    _Ptr2Info& operator[] (std::ptrdiff_t idx) override ;       // in Cont Vect setter is not accessible
    const _Info& insert(const _Info &v) override;
    bool erase(const _Info &v) override;
    // Getters
    const _Info& find(const _Info &v) const noexcept override;
    constexpr std::size_t getUsed() const noexcept {return Cont_base<T>::_used;};
    // Copies & transfers
    Cont(const Cont<T> &v) noexcept;
    explicit Cont(const _Vect &v) ;
    explicit Cont(const _BST &v) ;
    inline Cont<T>& operator= (const Cont&) noexcept;
    inline Cont<T>& operator= (Cont&&) noexcept;
    inline Cont<T>& operator=(const _BST &v) override;
    inline Cont<T>& operator=(const _Vect &v);
    // Output
    void _dsp (std::ostream &out) const override {_BST::_dsp(out);}
    // note : ne fonctionne pas pour un type déclaré Vect, problème : celui ci n'a pas de BST rempli et donc ne peut pas utiliser l'opérateur d'output de celui-ci
    // détecter le type déclaré (est-ce possible?) reviendrait à briser le principe de Substitution de Liskov
    // Destructor
    ~Cont () noexcept = default;
    // Associated function
    template <typename U>
    friend inline std::ostream& operator<< (std::ostream&, const Cont<U>&);
};

// Constructors ============================================================

template<typename T>
Cont<T>::Cont(const std::initializer_list<T> &init) noexcept : _BST(), _Vect(init.size()){
    auto p = init.begin();
    std::ptrdiff_t idx;
    for (idx = 0; idx < init.size(); ++idx)
        Cont::insert({idx, *p++});
}

template<typename T>
Cont<T>::Cont(std::size_t t, const std::initializer_list<T> &init) noexcept: _BST(), _Vect(t){
    auto p = init.begin();
    std::ptrdiff_t idx;
    for (idx = 0; idx < init.size(); ++idx)
        Cont::insert({idx, *p++});
}


// Setters =================================================================

template<typename T>
typename Cont<T>::_Ptr2Info& Cont<T>::operator[](std::ptrdiff_t idx) {
    if (_Vect::operator[](idx).isEmpty()){          // value are constant in Cont context, no change allowed for element
        return _Vect::operator[](idx);
    }
    else throw std::domain_error("can't assign new value in constant vect");
}

template<typename T>
const typename Cont<T>::_Info& Cont<T>::insert(const _Info& v) {      // [-Wreturn-type] warning because no explicit return, prevents using insert two times
    std::ptrdiff_t idx = Cont_base<T>::_index(v);
    if (idx == -1){                 // implicit conversion to Info with default index -1
        throw std::domain_error("no index specified");
    }
    if (std::size_t(idx) <= _Vect::dim()){
        if(!_BST::exists(T(v))){                                // cast to T to find element without taking into account the index
            if (!_Vect::operator[](idx).isEmpty()) {            // check if index is occupied, if yes erase it from the BST
                _BST::erase(_Vect::operator[](idx));            // delete old Node at same position to update
            }
            Cont_base<T>::_used += 1;
            Cont_base<T>::_ptr(_Vect::operator[](idx)) = &_BST::insert(v);    // Vect[i] points to correct Node of BST
        }
        else{
            throw std::domain_error("element already in Container");
        }
    }
    else{
        throw std::out_of_range("index out of range");
    }
}

template<typename T>
bool Cont<T>::erase(const _Info &v) {
    std::ptrdiff_t idx = Cont_base<T>::_index(v);
    if (idx == -1){         // either no index specified but v in BST, or v not in BST
        if(_BST::exists(v)) Cont_base<T>::_ptr(_Vect::operator[](Cont_base<T>::_index(_BST::find(v)))) = nullptr;  // delete pointer if v exist in BST
        if(_BST::erase(v)){
            Cont_base<T>::_used -= 1;
            return true;
        }
        else return false;
    }
    else {
        if(_Vect::operator[](idx) == v ){               // implicit cast to constructor Info for vect[idx] with correct index
        //if(_Vect::operator[](idx) == Ptr2Info(v) ){
            _Vect::operator[](idx) = Ptr2Info() ;           // erase pointeur of Vect
            if(_BST::erase(v)){
                Cont_base<T>::_used -= 1;
                return true;
            }
            else return false;
        }
        else{
            throw std::domain_error("element not found at this position");
        }
    }
}

// Getters ===================================================================

template<typename T>
const typename Cont<T>::_Info& Cont<T>::find(const _Info &v) const noexcept{
    std::ptrdiff_t idx = Cont_base<T>::_index(v);
    if (idx == -1){
        return _BST::find(v);
    }
    else{
        if(_Vect::operator[](idx) == v){      // implicit cast to constructor Info for vect[idx] with correct index
            return _BST::find(v);
        }
        else return _BST::_NOT_FOUND;  // no exception threw here because base virtual method is noexcept
    }
}

// Copies & transfers ========================================================

template<typename T>
Cont<T>::Cont (const Cont<T> &v) noexcept: Cont_base<T>(), _BST(), _Vect(v.dim()){   // Cont_base<T> prevents warning
    for (std::size_t i = 0; i < v.dim(); ++i){    // warning conversion to std::ptrdiff_t='long int' from std::size_t='long unsigned int' is acceptable because i start at 0 (same for further into code)
        if ( !v.at(i).isEmpty()) {
            Cont::insert({i,*Cont_base<T>::_ptr(v.at(i))});
        }
    }
    Cont_base<T>::_used = v.getUsed();
}

template<typename T>
Cont<T>::Cont (const _Vect &v) : _BST(), _Vect(v.dim()){
    if (const Cont* cont = dynamic_cast<const Cont*>(&v)){  // dynamic_cast doesn't have the ability to remove a const qualifier
        for (std::size_t i = 0; i < v.dim(); ++i){
            if ( !v.at(i).isEmpty()) Cont::insert({ i,*Cont_base<T>::_ptr(v.at(i))});
        }
    }
    else{
        throw std::domain_error("wrong effectif type");
    }
}

template<typename T>
Cont<T>::Cont(const _BST &v) : _BST(v), _Vect(){
    if (const Cont* cont = dynamic_cast<const Cont*>(&v)){
        Cont_base<T>::_used = cont->getUsed();
        // parcourt de l'arbre -> Vect doit pointer au bon endroit
    }
    else{
        throw std::domain_error("wrong effectif type");
    }
}

template<typename T>
Cont<T>& Cont<T>::operator=(const _BST &v) {
    if (const Cont* res = dynamic_cast<const Cont*>(&v)){           // dynamic_cast doesn't have the ability to remove a const qualifier
        if (this != &v){
            Cont_base<T>::operator=(*res);                 // explicit call to copy assignement operator of Cont_Base for _used
            _BST::operator=(*res) ;                        // explicit call to copy assignement for _BST subobject
            // parcourt de l'arbre -> Vect doit pointer au bon endroit
        }
    }
    else{
        throw std::domain_error("wrong effectif type");
    }
    return *this;
}

template<typename T>
Cont<T>& Cont<T>::operator=(const _Vect &v) {
    if (const Cont* res = dynamic_cast<const Cont*>(&v)){
        if (this != &v){
            Cont_base<T>::operator=(v);                 // explicit call to copy assignement operator of Cont_Base for _used
            _Vect::operator=(v) ;                       // explicit call to copy assignement for _Vect subobject
            for (std::size_t i = 0; i < v.dim(); ++i){
                if ( !v.at(i).isEmpty()) Cont::insert({i,*Cont_base<T>::_ptr(v.at(i))});
            }
        }
    }
    else{
        throw std::domain_error("wrong effectif type");
    }
    return *this;
}

// Associated function =======================================================

template<typename U>
inline std::ostream &operator<<(std::ostream &out, const Cont<U> &c){
    out << "[ "; c._dsp(out); out << ']'; return out;}


template<typename T>
Cont<T>& Cont<T>::operator=(const Cont &v) noexcept {
    if (this != &v){
        Cont_base<T>::operator=(v);                 // explicit call to copy assignement operator of Cont_Base for _used
        _BST::operator=(v) ;
        _Vect::operator=(v) ;
    }
    return *this;
}

template<typename T>
Cont<T>& Cont<T>::operator=(Cont &&v) noexcept {
    if (this != &v){
        Cont_base<T>::operator=(v);                 // explicit call to copy assignement operator of Cont_Base for _used
        _BST::operator=(v) ;
        _Vect::operator=(v) ;
    }
    v.Cont_base<T>::_used = 0;
    return *this;
}


// Deduction guides ==========================================================

template <typename T>
Cont (const Vect<T>&) -> Cont<typename T::value_type>;

template <typename T>
Cont (const BST<T>&) -> Cont<typename T::value_type>;


#endif // _CONT_H_