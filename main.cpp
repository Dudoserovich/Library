#include <iostream>
#include <vector>
#include "Library.h"

using namespace std;

int main() {
    vector<string> nameB = {"Книжка с тёлкой", "Банда четырёх", "Банда четырёх", "В", "Г", "Д", "Е", "Ё"};
    vector<string> nameA = {"Роман Лось", "Эрих Гамма", "Джон Влисидис", "Г", "Г", "Е", "Ё", "Ж"};
    vector<Book> B = {};
    vector<Autor> A = {};
    Library L(B, A);
    for (int i = 0; i < 8; ++i) {
        Book b(nameB[i]);
        Autor a(nameA[i]);
        L.addBooks (b, a);
    }

    Visitor V(L.getBook(), L.getAutor());
    V.wantSearch();

    return 0;
}
