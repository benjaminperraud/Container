/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Benjamin Perraudin - 2021/08 - <Vect.hpp>
 * ADT générique de vecteur dynamique (taille variable) et polymorphe
 * Copies et transferts possibles
 */
#ifndef _VECT_H_
#define _VECT_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <type_traits>         // is_class, true_type, remove_const...
#include  <initializer_list>    // initialisation list
#include  <exception>
#include  <stdexcept>           // standard exceptions
#include  <ostream>             // output streams

template <typename T>
class Vect {
    std::size_t _size = 0;        // taille du vecteur
    T *_val = nullptr;            // valeur contenu
    // ...
protected:
    virtual void _dsp (std::ostream&) const;
public:
    // Constructors
    Vect (const std::initializer_list<T>&) noexcept;
    Vect (std::size_t, const std::initializer_list<T>&) noexcept;
    // ...
    // Getters
    constexpr std::size_t size () const noexcept {return _size;}
    // ...
    // Associated functions
    template <typename U>
    friend inline std::ostream& operator<< (std::ostream&, const Vect<U>&);
}; // Vect<T>

// Constructors ==============================================================

template <typename T>
Vect<T>::Vect (const std::initializer_list<T>& init) noexcept:
        _size(init.size()), _val(new T[_size]{}) {
    auto p = init.begin();
    for (std::size_t i = 0; i < _size; ++i)
        const_cast<std::remove_const_t<T>*>(_val)[i] = *p++;
}

template <typename T>
Vect<T>::Vect (std::size_t d, const std::initializer_list<T>& init) noexcept:
        _size(d), _val(new T[d]{}) {
    const std::size_t size = init.size() > d ? d : init.size();
    auto p = init.begin();
    for (std::size_t i = 0; i < size; ++i)
        const_cast<std::remove_const_t<T>*>(_val)[i] = *p++;
}

// ...

// Associated functions =========================================================

template <typename T>
inline std::ostream& operator<< (std::ostream& out, const Vect<T>& v)
{out << "[ "; v._dsp(out); out << ']'; return out;}

#endif // _VECT_H_
