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
    class Info;      // manière de rendre la classe Info locale (pas de place en mémoire) -> éviter d’entrer en collision potentielle avec des déclarations et définitions d’un programme qui l’utiliserait
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
}; // Cont_base<T>

template <typename T>
const typename Cont_base<T>::Info Cont_base<T>::_EMPTY{};     // Info _EMPTY attribute initialize

// Embedded class Info =======================================================

template <typename T>
class Cont_base<T>::Info : public _Cont_base::_Base<typename Cont_base<T>::Info> {      // class Info inherit from struct _Base define in _Cont_Base ?
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
  constexpr operator const Info& () const noexcept     // implicit cast
    {return _ptr ? *_ptr : _EMPTY;}
    constexpr operator const T& () const noexcept        // implicit cast         -> conversion from const T& to const Info
    {return _ptr ? *_ptr : _EMPTY;}
  // Getter
  constexpr bool isEmpty () const noexcept {return !_ptr;}
  constexpr bool operator< (const Ptr2Info& i) const noexcept
    {return _ptr->_data < i._ptr->_data;}
  constexpr bool operator== (const Ptr2Info& i) const noexcept
    {return _ptr->_data == i._ptr->_data;}
}; // Ptr2Info

namespace _Cont_base {
  template <typename> using _Base = void;   // "destroy" access to real _Base
}

// Main class ================================================================



//class Cont final: public Cont_base<T>, private BST<typename Cont_base<T>::Ptr2Info>, private Vect<typename Cont_base<T>::Ptr2Info> {

//<typename Cont_base<T>::Info>

// class Cont final: public Cont_base<T>, private BST<T>, private Vect<T> {
template <typename T>
class Cont final: private Cont_base<T>, public BST<T>, public Vect<T> {
  using _Base = Cont_base<T>;
  using _Ptr2Info = typename _Base::Ptr2Info;
//  using _Vect = Vect<_Ptr2Info>;
//  using _BST  = BST<_Ptr2Info>;

  using _Info = typename _Base::Info;
  using _Vect = Vect<_Info>;
  using _BST  = BST<_Info>;
  using _Base::_index;
  using _Base::_ptr;

  // Attributs
  // std::size_t _max = 0;   // maximum size of Cont (pas besoin car déjà dans Vect?)

public:
  // Traits
  using value_type      = T;
  using reference       = T&;
  using const_reference = const T&;
  using Info = typename _Base::Info;
  using Ptr2Info = const _Ptr2Info;
  // Constructors
  constexpr Cont() noexcept = default;                                          // constructor without parameters


  //explicit constexpr Cont(std::size_t t) noexcept: _BST(), _Vect(t){}           // constructor with maximum size of Cont

  explicit constexpr Cont(std::size_t t) noexcept: BST<T>(), Vect<T>(t){}           // constructor with maximum size of Cont

  Cont (const std::initializer_list<T>& init ) noexcept: _BST(), _Vect(){}      // constructor with initial list  -> faire des insert à la suite pour construire le BST ?

//  template <typename U>
//  explicit constexpr Cont(std::size_t t) noexcept: BST<typename Cont_base<U>::Info()>(), Vect<typename Cont_base<U>::Info()>(t){}   // constructor with maximum size of Cont
  // explicit operator Cont<T>() { return *reinterpret_cast<Cont<T>>(this); }
  //constexpr explicit operator Cont<T> () const noexcept {return &Cont<_Info>(this) ;}          // constructor with maximum size of Cont

//  // Getter
//  static constexpr bool isNotFound (const T& v) noexcept;
//  constexpr bool isEmpty () const noexcept ;
   const T& find (const T&) const noexcept;

  inline const T& operator[] (std::ptrdiff_t) const;
//  bool exists (const T& v) const noexcept ;

  // Setter
  //const _Ptr2Info& insert (const _Ptr2Info &v) override;
  //const _Info& insert (const _Info &v) override;

  inline T& operator[] (std::ptrdiff_t);    // référence non const donc l-value assignable


  const T& insert (std::ptrdiff_t i, const T &v) ;

  // bool erase (const T& v) override;                 // false if doesn't exist

  // copies / transfert / etc...

  inline Cont& operator= (const T&) noexcept;
  inline Cont& operator= (Cont&&) noexcept;

  // Output

  void _dsp (std::ostream&) const {} ;

  // Destructor
  ~Cont () noexcept = default;
};

//template<typename T>
//const typename Cont_base<T>::Info& Cont<T>::insert(const Cont::_Info &v) {       // Ptr2Info converted to Info converted to T
//    return _BST::insert(v);
//}

template<typename T>
const T &Cont<T>::find(const T& v) const noexcept {
    return BST<T>::find(v);
}

template<typename T>
const T& Cont<T>::insert(std::ptrdiff_t i, const T& v) {
    const T& cont = BST<T>::insert(v);
    Vect<T>::operator[](i) = cont;
    Vect<T>::print();
;}

template<typename T>
T& Cont<T>::operator[](std::ptrdiff_t t) {                      // l-value    -> inutile dans le cadre du projet
    return Vect<T>::operator[](t);                              // return observateur ie : r-value
}

template<typename T>
const T &Cont<T>::operator[](std::ptrdiff_t t) const {          // r-value    ->
    return Vect<T>::operator[](t);
}

template<typename T>
Cont<T> &Cont<T>::operator=(const T &) noexcept {            // opérateur d'assignation en l-value ?
    return *this;
}

template<typename T>
Cont<T> &Cont<T>::operator=(Cont &&) noexcept {          // move assignement operator
    return *this;
}


//template <typename T>
//Vect<T>& Vect<T>::operator= (const Vect& v) noexcept {
//    if (this != &v) {delete[] _val; _size = v._size; _val = _cp(v);}
//    return *this;
//}
//
//template <typename T>
//Vect<T>& Vect<T>::operator= (Vect&& v) noexcept {
//    if (this != &v) {
//        delete[] _val; _size = v._size; _val = v._val;
//        v._size = 0; v._val = nullptr;
//    }
//    return *this;
//}


template <typename T>
inline std::ostream& operator<< (std::ostream& out, const Cont<T>& v)
{out << "[ ";  v._dsp(out) ; out << ']'; return out;}


//template<typename T>
//bool Cont<T>::erase(const T &v) {
//    return false;
//}

// Cont<T>

// Deduction guides ==========================================================

template <typename T>
Cont (const Vect<T>&) -> Cont<typename T::value_type>;

template <typename T>
Cont (const BST<T>&) -> Cont<typename T::value_type>;

#endif // _CONT_H_
