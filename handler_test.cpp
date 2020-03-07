#include <iostream>
#include "ChessHandler.h"

using namespace std;

int main() {
    ChessHandler m;
    m.print();
    
    while (true) {
        char s[4];
        cin >> s;
        if (m.move(s))
            m.print();
        else cout << "ERROR" << endl;
    }

    return 0;
}