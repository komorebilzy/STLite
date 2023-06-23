#include "map.hpp"
#include <iostream>
#include <cstdlib>

int main() {
//    int n = 9;
//    for (int t = 1; t <= 1000; ++t) {
//        int L = rand() % n, R = rand() % n;
//        if (L > R) std::swap(L, R);
//        std::cout << "Case " << t << "  n=" << n << " L=" << L << " R=" << R << std::endl;
    int n = 9, L = 0, R = 2;
    sjtu::map<int, int> m;
    for (int i = 0; i < n; ++i) m.insert({i, i});
    for (int i = 0; i < n; ++i) {
        if (i > L && i <= R) continue;
        auto p = m.find(i);
        m.erase(p);
    }

    return 0;
}
