#ifndef BOOKINDEX_H
#define BOOKINDEX_H

#include "Book.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct BSTNode {
    Book book;
    BSTNode* left;
    BSTNode* right;
    int height;
    
    BSTNode(Book b) : book(b), left(nullptr), right(nullptr), height(1) {}
};

class BookIndex {
private:
    BSTNode* root;
    
    int getHeight(BSTNode* node) { return node ? node->height : 0; }
    
    int getBalance(BSTNode* node) { 
        return node ? getHeight(node->left) - getHeight(node->right) : 0; 
    }
    
    BSTNode* rotateRight(BSTNode* y) {
        BSTNode* x = y->left;
        BSTNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        
        return x;
    }
    
    BSTNode* rotateLeft(BSTNode* x) {
        BSTNode* y = x->right;
        BSTNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }
    
    BSTNode* insert(BSTNode* node, Book book) {
        if (!node) return new BSTNode(book);
        
        if (book.get_title() < node->book.get_title()) {
            node->left = insert(node->left, book);
        } else if (book.get_title() > node->book.get_title()) {
            node->right = insert(node->right, book);
        } else {
            return node;
        }
        
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);
        
        if (balance > 1 && book.get_title() < node->left->book.get_title()) {
            return rotateRight(node);
        }
        if (balance < -1 && book.get_title() > node->right->book.get_title()) {
            return rotateLeft(node);
        }
        if (balance > 1 && book.get_title() > node->left->book.get_title()) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && book.get_title() < node->right->book.get_title()) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    void inorderTraversal(BSTNode* node) {
        if (node) {
            inorderTraversal(node->left);
            node->book.display();
            inorderTraversal(node->right);
        }
    }
    
    BSTNode* searchByTitle(BSTNode* node, const string& title) {
        if (!node || node->book.get_title() == title) return node;
        if (title < node->book.get_title()) return searchByTitle(node->left, title);
        return searchByTitle(node->right, title);
    }
    
    void getAllBooksHelper(BSTNode* node, vector<Book>& books) {
        if (node) {
            getAllBooksHelper(node->left, books);
            books.push_back(node->book);
            getAllBooksHelper(node->right, books);
        }
    }
    
public:
    BookIndex() : root(nullptr) {}
    
    void addBook(Book book) { root = insert(root, book); }
    
    void displayAllBooks() {
        cout << "=== ALL BOOKS IN CATALOG ===" << endl;
        if (!root) {
            cout << "No books in catalog." << endl;
            return;
        }
        inorderTraversal(root);
    }
    
    Book* searchBook(const string& title) {
        BSTNode* result = searchByTitle(root, title);
        return result ? &(result->book) : nullptr;
    }
    
    vector<Book> getAllBooks() {
        vector<Book> books;
        getAllBooksHelper(root, books);
        return books;
    }
};

#endif
