#include <iostream>
#include "map.hpp"
using namespace sjtu;
template <class T>
void is_assignable(const T& iter) {
    if (T::iterator_assignable::isassignable == my_true_type::isassignable)
    {
        std::cout << "Assignable" << std::endl;
    }
    else {
        std::cout << "Not Assignable" << std::endl;
    }

}

int main() {
    map<int,int>::iterator iter1;
    map<int,int>::const_iterator iter2;
    is_assignable(iter1);
    is_assignable(iter2);

    return 0;
}