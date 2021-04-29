#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Autor {
    friend class Librarian;
    friend class Library;
protected:
    string name;
public:
    explicit Autor (string name) : name(name) {}
};

class Book {
    string name;
    friend class Autor;
    friend class Librarian;
    friend class Library;
public:
    explicit Book (string name) : name(name) {}
};

// книга в библиотеке может иметь только одного автора
class Library {
    friend class Book;
    friend class Autor;
protected:
    struct Books {
        vector<Book> books;
        vector<Autor> autors;
    };
    Books B;


public:
    Library(vector<Book> books, vector<Autor> autors) {
        B.books = books;
        B.autors = autors;
    }

    void addBooks (Book BK, Autor AU) {
        vector<string> vec;
        for (int i = 0; i < B.books.size(); ++i) {
            vec.push_back(B.books[i].name);
        }
        if (std::find(vec.begin(), vec.end(), BK.name) != vec.end())
            cout << "Такая книга уже есть в библиотеке" << endl;
        else {
            B.books.push_back(BK);
            B.autors.push_back(AU);
        }
    }

    vector<Book> getBook () {
        return B.books;
    }

    vector<Autor> getAutor () {
        return B.autors;
    }

};

// библиотекарь ищет книгу по названию и автору
class Librarian : public Library {

public:
    Librarian(vector<Book> books, vector<Autor> autors) : Library(books, autors) {}

    void welcome () {
        cout << "Добро пожаловать в библиотеку.\nДавайте я вам помогу найти нужную вам книгу!" << endl;
    }

    void printSearch (string book, string autor) {
        if (autor != "" && book != "")
            cout << "Ваша книга: " << book  << '/' << autor << endl;
        else cout << "Такой книги нет в нашей библиотеке" << endl;
    }

    void searchAutor (string autor) {
        for (int k = 0; k < Library::B.books.size(); ++k) {
            if (Library::B.autors[k].name == autor)
                printSearch(Library::B.books[k].name, autor);
        }
    }

    void searchBook (string book) {
        string au = "";
        for (int k = 0; k < B.books.size(); ++k) {
            if (B.books[k].name == book)
                printSearch(book, B.autors[k].name);
        }
    }

    void searchAutorBook (string autor, string book) {
        for (int k = 0; k < B.books.size(); ++k) {
            if ((B.books[k].name == book) && (B.autors[k].name == autor))
                printSearch(book, autor);
        }
    }

};

class Visitor : public Librarian {
public:
    Visitor(vector<Book> books, vector<Autor> autors) : Librarian(books, autors) {}

    void wantSearch () {
        welcome();
        string book;
        string autor;
        bool check = false;
        cout << "Вы знаете автора книги? (1 - да, 2 - нет)" << endl;
        int i;
        do {
            if (check){
                cout << "Вы ввели некорректное число" << endl;
            }
            cin >> i;
            check = true;
        }
        while (i != 1 && i != 2);

        int j;
        check = false;
        cout << "Вы знаете название книги? (1 - да, 2 - нет)" << endl;
        do {
            if (check){
                cout << "Вы ввели некорректное число" << endl;
            }
            cin >> j;
            check = true;
        }
        while (j != 1 && j != 2);

        cin.ignore();
        if (i == 1) {
            cout << "Введите имя автора:" << endl;
            getline(cin, autor);
        }

        if (j == 1) {
            cout << "Введите название книги:" << endl;
            getline(cin, book);
        }

        if ((i == 1) && (j == 2))
            searchAutor(autor);
        else if (i == 1 && j == 1)
            searchAutorBook(autor, book);
        else if (i == 2 && j == 1)
            searchBook(book);
        else cout << "Так зачем вы вообще пришли, если не знаете ничего о книге?" << endl;
    }
};


