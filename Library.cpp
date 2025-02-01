#include <iostream>
#include <vector>
#include <string>
#include <fstream> // File handling
#include <limits> // Input validation
using namespace std;

// Structure to store book details
struct Book {
    string name;
    string author;
    int year;
    string ISBN; // ISBN for the book (its unique)
    int copies;// number of available copies of the book
};

struct Borrower {
    string userName;
    string phoneNumber;
    string ISBN;
    string bookName;
};

// clear the screen (works only on windows)
void clearScreen() {
   system("cls");
}

// pause and wait for user input before continuing the program
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); // wait for Enter key to continue program
}

// load books from a file
void loadBooks(vector<Book>& library) {
    ifstream file("library.txt"); // open file for reading
    if (!file) {
        cout << "No existing library file found. The program will start with an empty library.\n";
        return;
    }

    Book book;
    while (getline(file, book.name)) {
        getline(file, book.author);
        file >> book.year;
        file >> book.ISBN;
        file >> book.copies;
        file.ignore(); // ignore newline
        library.push_back(book); // store in vector
    }

    file.close();
    cout << "Loaded " << library.size() << " books from the library file.\n";
}

//save books to a file
void saveBooks(const vector<Book>& library) {
    ofstream file("library.txt"); // Opens a  file for writing
    if (!file) {
        cout << "ERROR: Could not save library data.\n";
        return;
    }

    for (const auto& book : library) {
        file << book.name << "\n"
             << book.author << "\n"
             << book.year << "\n"
             << book.ISBN << "\n"
             << book.copies << "\n";
    }

    file.close();
}

// add a book to the library
void addBook(vector<Book>& library) {
    clearScreen();
    Book newBook;

    cout << "ADD A NEW BOOK \n";

    cout << "Enter book name: ";
    getline(cin >> ws, newBook.name);

    cout << "Enter author: ";
    getline(cin, newBook.author);

    cout << "Enter year of publication: ";
    while (!(cin >> newBook.year)) {
        cout << "Invalid input. Enter a valid year: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter ISBN: ";
    cin >> newBook.ISBN;

    cout << "Enter number of copies: ";
    while (!(cin >> newBook.copies) || newBook.copies < 0) {
        cout << "Invalid input. Enter a valid number of copies: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    library.push_back(newBook);
    saveBooks(library); // saving the updated library to file
    cout << "\n Book added successfully and saved!\n";
    pause();
}

// borrow book from library
void borrowBook(vector<Book>& library) {
    clearScreen();
    if (library.empty()) {
        cout << "No books available for borrowing.\n";
        pause();
        return;
    }

    Borrower borrower;

    cout << "BORROW A BOOK\n";
    cout << "Enter your name: ";
    getline(cin >> ws, borrower.userName);

    cout << "Enter your phone number: ";
    getline(cin, borrower.phoneNumber);

    cout << "Enter ISBN of the book you want to borrow: ";
    cin >> borrower.ISBN;

    for (auto& book : library) {
        if (book.ISBN == borrower.ISBN) {
            if (book.copies > 0) {
                cout << "\nThe book is available.\n";
                book.copies--; // Reduce the number of copies
                borrower.bookName = book.name;

                ofstream borrowFile("borrowed_books.txt", ios::app);
                if (borrowFile) {
                    borrowFile << borrower.userName << "\n"
                               << borrower.phoneNumber << "\n"
                               << borrower.bookName << "\n"
                               << borrower.ISBN << "\n";
                    borrowFile.close();
                }

                saveBooks(library);
                cout << "\nThe user (" << borrower.userName << ") has borrowed \"" << book.name << "\" successfully.\n";
                pause();
                return;
            } else {
                cout << "\nThe book is not available.\n";
                pause();
                return;
            }
        }
    }

    cout << "\nBook not found.\n";
    pause();
}

// display all books in the library
void displayBooks(const vector<Book>& library) {
    clearScreen();
    cout << "LIBRARY COLLECTION is :\n";

    if (library.empty()) {
        cout << "\n No books in the library.\n";
    } else {
        for (size_t i = 0; i < library.size(); ++i) {
            cout << "\n Book #" << i + 1 << "\n";
            cout << "Name: " << library[i].name << "\n";
            cout << "Author: " << library[i].author << "\n";
            cout << "Year: " << library[i].year << "\n";
            cout << "ISBN: " << library[i].ISBN << "\n";
            cout << "Copies: " << library[i].copies << "\n";
            cout << "----------------------------------";
        }
        cout << "\n";
    }

    pause();
}

// search for a book by name
void searchByName(const vector<Book>& library) {
    clearScreen();
    if (library.empty()) {
        cout << " No books available.\n";
        pause();
        return;
    }

    string searchName;
    cout << " SEARCH BY BOOK NAME \n";
    cout << "Enter book name: ";
    getline(cin >> ws, searchName);

    bool found = false;
    for (const auto& book : library) {
        if (book.name == searchName) {
            cout << "\n Book Found!\n";
            cout << "Name: " << book.name << "\n";
            cout << "Author: " << book.author << "\n";
            cout << "Year: " << book.year << "\n";
            cout << "ISBN: " << book.ISBN << "\n";
            cout << "Copies: " << book.copies << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n Book not found.\n";
    }

    pause();
}

// search for a book by ISBN
void searchByISBN(const vector<Book>& library) {
    clearScreen();
    if (library.empty()) {
        cout << " No books in the library to search.\n";
        pause();
        return;
    }

    string searchISBN;
    cout << "  SEARCH BY ISBN \n";
    cout << "Enter ISBN: ";
    cin >> searchISBN;

    bool found = false;
    for (const auto& book : library) {
        if (book.ISBN == searchISBN) {
            cout << "\n Book Found!\n";
            cout << "Name: " << book.name << "\n";
            cout << "Author: " << book.author << "\n";
            cout << "Year: " << book.year << "\n";
            cout << "ISBN: " << book.ISBN << "\n";
            cout << "Copies: " << book.copies << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n Book not found.\n";
    }

    pause();
}

// remove book by ISBN
void removeBookByISBN(vector<Book>& library) {
    clearScreen();
    if (library.empty()) {
        cout << "No books in the library to remove.\n";
        pause();
        return;
    }

    string searchISBN;
    cout << "REMOVE BOOK BY ISBN\n";
    cout << "Enter ISBN: ";
    cin >> searchISBN;

    for (auto it = library.begin(); it != library.end(); ++it) {
        if (it->ISBN == searchISBN) {
            cout << "\nThe book (" << it->name << ") is removed successfully.\n";
            library.erase(it);
            saveBooks(library); // Save updated library
            pause();
            return;
        }
    }

    cout << "\nBook not found.\n";
    pause();
}

// edit a special book in library
void editBookByISBN(vector<Book>& library) {
    clearScreen();
    if (library.empty()) {
        cout << "No books available to edit.\n";
        pause();
        return;
    }

    string searchISBN;
    cout << "EDIT BOOK DETAILS\n";
    cout << "Enter ISBN of the book to edit: ";
    cin >> searchISBN;

    for (auto& book : library) {
        if (book.ISBN == searchISBN) {
            cout << "\nEditing book: " << book.name << "\n";

            string newName, newAuthor;
            int newYear, newCopies;

            cin.ignore();
            cout << "Enter new book name (leave empty to keep the same): ";
            getline(cin, newName);
            if (!newName.empty() && newName != book.name) book.name = newName;

            cout << "Enter new author (leave empty to keep the same): ";
            getline(cin, newAuthor);
            if (!newAuthor.empty() && newAuthor != book.author) book.author = newAuthor;

            cout << "Enter new year of publication (enter 0 to keep the same): ";
            cin >> newYear;
            if (newYear != 0 && newYear != book.year) book.year = newYear;

            cout << "Enter new number of copies (enter -1 to keep the same): ";
            cin >> newCopies;
            if (newCopies >= 0 && newCopies != book.copies) book.copies = newCopies;

            saveBooks(library);
            cout << "\nThe details of (" << book.name << ") have been edited successfully.\n";
            pause();
            return;
        }
    }

    cout << "\nBook not found.\n";
    pause();
}

// check all borrowed books
void checkBorrowedBooks() {
    clearScreen();
    ifstream file("borrowed_books.txt");
    if (!file) {
        cout << "No borrowed books found.\n";
        pause();
        return;
    }

    cout << "Borrowed Books List:\n";
    string name, phone, bookName, ISBN;
    bool found = false;

    while (getline(file, name)) {
        getline(file, phone);
        getline(file, bookName);
        getline(file, ISBN);
        cout << "User: " << name << " | Phone: " << phone << " | Book: " << bookName << " | ISBN: " << ISBN << "\n";
        found = true;
    }

    if (!found) {
        cout << "No borrowed books found.\n";
    }
    file.close();
    pause();
}

// View all unreturned books
void viewUnreturnedBooks() {
    clearScreen();
    ifstream file("borrowed_books.txt");
    if (!file) {
        cout << "No borrowed books found.\n";
        pause();
        return;
    }

    cout << "UNRETURNED BOOKS LIST:\n";
    string name, phone, bookName, ISBN;
    bool found = false;

    while (getline(file, name)) {
        getline(file, phone);
        getline(file, bookName);
        getline(file, ISBN);
        cout << "User: " << name << " | Phone: " << phone
             << " | Book: " << bookName << " | ISBN: " << ISBN << "\n";
        found = true;
    }

    if (!found) {
        cout << "All books have been returned.\n";
    }
    file.close();
    pause();
}

// return a book back to library
void returnBook(vector<Book>& library) {
    clearScreen();

    Borrower returner;
    cout << "RETURN A BOOK\n";
    cout << "Enter your name: ";
    getline(cin >> ws, returner.userName);
    cout << "Enter your phone number: ";
    getline(cin, returner.phoneNumber);
    cout << "Enter ISBN of the book you want to return: ";
    cin >> returner.ISBN;

    ifstream file("borrowed_books.txt");
    if (!file) {
        cout << "No borrowed records found.\n";
        pause();
        return;
    }

    vector<Borrower> borrowers;
    Borrower borrower;
    bool returned = false;
    string returnedBookName;

    while (getline(file, borrower.userName)) {
        getline(file, borrower.phoneNumber);
        getline(file, borrower.bookName);
        getline(file, borrower.ISBN);

        if (borrower.userName == returner.userName && borrower.phoneNumber == returner.phoneNumber &&
            borrower.ISBN == returner.ISBN) {
            returned = true;
            returnedBookName = borrower.bookName;

            // Check if the book exists in the library
            bool bookExists = false;
            for (auto& book : library) {
                if (book.ISBN == returner.ISBN) {
                    book.copies++; // Increase copies when returned
                    saveBooks(library);
                    bookExists = true;
                    break;
                }
            }

            // If the book doesn't exist in the library, add it as a new entry
            if (!bookExists) {
                Book newBook;
                newBook.name = borrower.bookName;
                newBook.ISBN = borrower.ISBN;
                newBook.copies = 1;
                library.push_back(newBook);
                saveBooks(library);
            }
        } else {
            borrowers.push_back(borrower); // Keep other borrowers
        }
    }
    file.close();

    // Save updated borrower list
    ofstream outFile("borrowed_books.txt");
    for (const auto& b : borrowers) {
        outFile << b.userName << "\n" << b.phoneNumber << "\n" << b.bookName << "\n" << b.ISBN << "\n";
    }
    outFile.close();

    if (returned) {
        cout << "\nThe book \"" << returnedBookName << "\" has been returned successfully.\n";
    } else {
        cout << "\nNo matching borrowed record found.\n";
    }
    pause();
}

//menu display
void displayMenu() {
    clearScreen();
    cout << "\nLibrary System\n";
    cout << "==================================\n";
    cout << "1)Add a Book\n";
    cout << "2)View All Books\n";
    cout << "3)Search book by Name\n";
    cout << "4)Search book by ISBN\n";
    cout << "5)Remove book by ISBN\n";
    cout << "6)Edit book by ISBN\n";
    cout << "7)Borrow book by ISBN\n";
    cout << "8)Check Borrowed Books and Borrowers\n";
    cout << "9)View Unreturned Books\n";
    cout << "10)Return a Book\n";
    cout << "11)Exit\n";
    cout << "==================================\n";
    cout << "choose an option: ";
}

int main() {
    vector<Book> library;
    loadBooks(library); // load books from file when program starts

    int option;
    do {
        displayMenu();
        while (!(cin >> option)) {
            cout << "Invalid option. Enter a number (1-5): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore();

        switch (option) {
            case 1: addBook(library);
            break;
            case 2: displayBooks(library);
            break;
            case 3: searchByName(library);
            break;
            case 4: searchByISBN(library);
            break;
            case 5: removeBookByISBN(library);
            break;
            case 6: editBookByISBN(library);
            break;
            case 7: borrowBook(library);
            break;
            case 8: checkBorrowedBooks();
            break;
            case 9: viewUnreturnedBooks();
            break;
            case 10: returnBook(library);
            break;
            case 11:  clearScreen();
                cout << " Library closed. Goodbye!\n";
            break;
            default:
                cout << " Invalid option. Please Try again.\n";
            pause();
        }
    } while (option != 11);

    return 0;
}
