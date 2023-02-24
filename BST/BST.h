#ifndef BST_H
#define BST_H
#include <initializer_list>
#include <iostream>

template <typename T>
class BST {
class Node;
public:
    class iterator {
    public:
        iterator(Node* cur);
    public:
        iterator& operator++();
        bool empty() const;
        T& operator*();
        const T& operator*() const;
        bool operator!=(const iterator&) const;
        bool operator==(const iterator&) const;
    private:
        int number_of_nodes(Node*) const;
    private:
        Node* cur;
        int size;
};
public:
    BST();
    BST(const T &);
    BST(const BST<T> &);  
    BST(BST<T> &&) noexcept;      
    BST(std::initializer_list<T>);
    ~BST();
public:
    BST<T>& operator=(const BST &);
    BST<T>& operator=(BST &&) noexcept;
    bool operator==(const BST &) const;
    bool operator!=(const BST &) const;
    BST<T> operator+(const BST &) const;
    BST<T>& operator+=(const BST &);
    template <typename L>
    friend std::ostream& operator<<(std::ostream &, const BST<L> &);
public:
    iterator begin() const;
    iterator end() const;     
public:
    void insert(const T &);
    bool empty() const;
    void inorder() const;
    void preorder() const;
    void postorder() const;
    void levelorder() const;
    void clear();
    void erase(const T &);
    iterator find(const T &) const;
    BST<T> merge(BST<T>);
    bool contains(const T &) const;
    int get_height() const;
    int get_number_of_nodes() const ;
    const T& get_root_data() const; 
private:
    class Node {
    public:
        Node(T data = T(), Node* parent = nullptr); 
    public:
        T data;
        Node* left;
        Node* right;
        Node* parent;  
};
private:
    void inorderHelper(const Node*) const;
    void preorderHelper(const Node*) const;
    void postorderHelper(const Node*) const;
    int get_height_helper(const Node*) const;
    int get_number_of_nodes_helper(const Node*) const ;
    Node* copy(Node*, Node* = nullptr);
    void deleteHelper(Node*&);
    void insert(Node*, const T &);
    void levelorder(const Node*, int) const;
    Node* findMinNode(Node*);
    Node* deleteElement(Node*, const T &); 
    Node* find(Node*, const T &) const;
private:
    Node* root;
};

#include "Implementation.h"
#endif


