#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
private:
    std::string title;
    std::string author;
    std::string genre;
    bool isAvailable;

public:
    Book(std::string title, std::string author, std::string genre)
        : title(title), author(author), genre(genre), isAvailable(true) {}

    void displayInfo() {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Author: " << author << std::endl;
        std::cout << "Genre: " << genre << std::endl;
        std::cout << "Availability: " << (isAvailable ? "Available" : "Not available") << std::endl;
        std::cout << std::endl;
    }

    bool getAvailability() {
        return isAvailable;
    }

    void setAvailability(bool availability) {
        isAvailable = availability;
    }

    std::string getTitle() const {
        return title;
    }
};

class Student {
private:
    std::string name;
    std::vector<Book*> borrowedBooks;

public:
    Student(std::string name) : name(name) {}

    void borrowBook(Book* book) {
        if (book->getAvailability()) {
            book->setAvailability(false);
            borrowedBooks.push_back(book);
            std::cout << "Book '" << book->getTitle() << "' has been borrowed by " << name << std::endl;
        }
        else {
            std::cout << "Book '" << book->getTitle() << "' is not available for borrowing." << std::endl;
        }
    }

    void returnBook(Book* book) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
        if (it != borrowedBooks.end()) {
            book->setAvailability(true);
            borrowedBooks.erase(it);
            std::cout << "Book '" << book->getTitle() << "' has been returned by " << name << std::endl;
        }
        else {
            std::cout << "Book '" << book->getTitle() << "' is not borrowed by " << name << std::endl;
        }
    }
};

class Library {
private:
    std::string name;
    std::vector<Book> books;

public:
    Library(std::string name) : name(name) {}

    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const Book& book) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getAvailability()) {
                if (it->getTitle() == book.getTitle()) {
                    books.erase(it);
                    break;
                }
            }
        }
    }

    Book* searchBook(const std::string& title) {
        for (auto& book : books) {
            if (book.getAvailability()) {
                if (book.getTitle() == title) {
                    return &book;
                }
            }
        }
        return nullptr;
    }
};

int main() {
    Library library("My Library");

    Book book1("The Great Gatsby", "F. Scott Fitzgerald", "Classic");
    Book book2("To Kill a Mockingbird", "Harper Lee", "Classic");
    Book book3("1984", "George Orwell", "Dystopian");

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    Student student1("John");
    Student student2("Emma");
    
    Book* foundBook = library.searchBook("1984");
    if (foundBook) {
        foundBook->displayInfo();
    }
    else {
        std::cout << "Book not found." << std::endl;
    }

    student1.borrowBook(foundBook);

    student2.borrowBook(foundBook);  // Trying to borrow the same book

    student1.returnBook(foundBook);

    return 0;
}

