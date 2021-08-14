/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Benjamin Perraudin - 2021/08 - <MyType.hpp>
 * Exemple de conteneur (projet n°1)
*/

#include <utility>

class MyType{
private:
    std::string _val;
protected:
    void _dsp (std::ostream& out) const {out << _val ;} ;
public:
    // Constructors
    MyType() noexcept = default;
    MyType(std::string value) noexcept : _val(std::move(value)) {};
    bool operator< (const MyType& i) const noexcept
    {return findSum(_val) < findSum(i._val);}
    bool operator== (const MyType& i) const noexcept
    { std::cout << findSum(_val) <<findSum(i._val)  << std::endl;
        return findSum(_val) == findSum(i._val);}
    int findSum(const std::string &str) const;
    friend inline std::ostream& operator<< (std::ostream&, const MyType&);
    // Copies & transfers
    MyType (const MyType& v) noexcept: _val(v._val) {}
    MyType (MyType&& v) noexcept:  _val(v._val) {v._val = "";}
    inline MyType& operator= (const MyType&) noexcept;
    inline MyType& operator= (MyType&&) noexcept;
};


int MyType::findSum(const std::string &str) const {
    // To store the sum
    int sum = 0;
    // For every character
    for (char i : str) sum += (int) i;
    return sum;
}

// Associated functions =========================================================


inline std::ostream& operator<< (std::ostream& out, const MyType& t)
{out << "'"; t._dsp(out); out << "'"; return out;}

MyType &MyType::operator=(const MyType &m) noexcept {
    if (this != &m) {
        _val = m._val;
    }
    return *this;
}

MyType &MyType::operator=(MyType &&m) noexcept {
    if (this != &m) {
        _val = m._val;
        m._val = "";
    }
    return *this;
}


#ifndef CONTAINERS_MYTYPE_HPP
#define CONTAINERS_MYTYPE_HPP

#endif //CONTAINERS_MYTYPE_HPP
