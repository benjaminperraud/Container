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
    std::size_t _size = 0;
    T *_val = nullptr;
    inline static T* _cp (const Vect&);
protected:
    virtual void _dsp (std::ostream& out) const {out << *_val ;} ;
public:
    // constructeurs
    constexpr Vect () noexcept = default;   // Tableau vide
    explicit Vect (std::size_t d) noexcept: _size(d), _val(new T[d]) {}
    Vect (const std::initializer_list<T>&) noexcept;
    Vect (std::size_t, const std::initializer_list<T>&) noexcept;
    // observateurs
    constexpr std::size_t dim () const noexcept {return _size;}
    inline const T& operator[] (std::ptrdiff_t) const;
    inline const T& at(std::ptrdiff_t) const;

    inline const T& print() {std::cout << _val[0] << std::endl;}

    // modificateurs
    inline T& operator[] (std::ptrdiff_t);
    // copies, transferts, etc.
    Vect (const Vect& v) noexcept: _size(v._size), _val(_cp(v)) {}
    constexpr Vect (Vect&& v) noexcept: _size(v._size), _val(v._val)
    {v._size = 0; v._val = nullptr;}
    inline Vect& operator= (const Vect&) noexcept;
    inline Vect& operator= (Vect&&) noexcept;
    // destructeur
    ~Vect () noexcept {delete[] _val;}
    // fonctions externes
    template <typename U>
    friend inline std::ostream& operator<< (std::ostream&, const Vect<U>&);
}; // Vect<T>

// constructeurs ============================================================

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

// observateurs =============================================================

template <typename T>
const T& Vect<T>::operator[] (std::ptrdiff_t idx) const {
    return _val[idx];
}

template<typename T>
const T &Vect<T>::at(std::ptrdiff_t idx) const {
    if (std::size_t(idx) >= _size)
        throw std::domain_error("Vect::at(i): index out of range");
    return _val[idx];
}

// modificateurs ============================================================

template <typename T>
T& Vect<T>::operator[] (std::ptrdiff_t idx) {
    if (std::size_t(idx) >= _size)
        throw std::domain_error("Vect::op[]: index out of range");
    return _val[idx];
}

// copies, transferts, etc. =================================================

template <typename T>
T* Vect<T>::_cp (const Vect<T>& v) {
    T *res = new T[v._size];
    for (std::size_t i = 0; i < v._size; ++i) res[i] = v._val[i];
    return res;
}

template <typename T>
Vect<T>& Vect<T>::operator= (const Vect& v) noexcept {
    if (this != &v) {delete[] _val; _size = v._size; _val = _cp(v);}
    return *this;
}

template <typename T>
Vect<T>& Vect<T>::operator= (Vect&& v) noexcept {
    if (this != &v) {
        delete[] _val; _size = v._size; _val = v._val;
        v._size = 0; v._val = nullptr;
    }
    return *this;
}

// Associated functions =========================================================

template <typename T>
inline std::ostream& operator<< (std::ostream& out, const Vect<T>& v)
{out << "[ "; v._dsp(out); out << ']'; return out;}


// fonctions externes =======================================================

//template <typename T>
//inline std::ostream& operator<< (std::ostream& out, const Vect<T>& v){
//    out << "[ ";
//    for (std::size_t i = 0; i < v._size; ++i) out << v._val[i] << ' ';
//    out << ']';
//    return out;
//}

#endif // _VECT_H_





