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
    {return findSum(_val) == findSum(i._val);}
    int findSum(const std::string &str) const;
    friend inline std::ostream& operator<< (std::ostream&, const MyType&);
};

int MyType::findSum(const std::string &str) const {
    std::string temp;
    int sum = 0;
    for (char ch : str) {
        if (isdigit(ch)) temp += ch;
        else {
            sum += atoi(temp.c_str());
            temp = "";
        }
    }
    return sum + atoi(temp.c_str());
}

// Associated functions =========================================================

template <typename T>
inline std::ostream& operator<< (std::ostream& out, const MyType& t)
{out << " ' "; t._dsp(out); out << " ' "; return out;}



#ifndef CONTAINERS_MYTYPE_HPP
#define CONTAINERS_MYTYPE_HPP

#endif //CONTAINERS_MYTYPE_HPP
