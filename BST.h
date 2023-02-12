#ifndef BST_H
#define BST_H
#include <initializer_list>
#include <iostream>
#include <stack>

template <typename T>
class BST {

    public:

        struct Node {
            
            T data;
            Node* left;
            Node* right;
            Node* parent;  

            Node(T data = T()) 
            : data(data),
            left(nullptr),
            right(nullptr),
            parent(nullptr) 
            {}
        };

        class iterator {
            
            public:

                iterator(Node* cur) {
                    if(cur) {
                        s.push(cur);
                        while (cur->left) {
                            cur = cur->left;
                            s.push(cur);
                        }
                    }
                }

            public:

                iterator& operator++() {
                    Node* tmp = s.top();
                    s.pop();
                     if (tmp->right) {
                    auto node = tmp->right;
                    while (node) {
                    s.push(node);
                    node = node->left;
                    }
                  }
                    return *this;
                }

                bool empty() {
                    return s.empty();
                }

                T operator*() {
                    return s.top()->data;
                }

                bool operator!=(const iterator& oth) {
                    return s != oth.s;
                }
                
            private:

                std::stack<Node*> s;
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
        void inorder(const Node*) const;
        void preorder(const Node*) const;
        void postorder(const Node*) const;
        void levelorder(const Node*) const;
        void clear();
        void erase(const T &);
        iterator find(const T &) const;
        BST<T> merge(BST<T>);
        bool contains(const T &) const;
        int get_height(const Node*) const;
        int get_number_of_nodes(const Node*) const ;
        Node* get_root() const;
        const T& get_root_data() const; 

    private:
         Node* root;

        Node* _copy(Node*);
        void _delete(Node*);
        void _insert(Node*, const T &);
        void _printLevel(const Node*, int) const;
        Node* _findMinNode(Node*);
        Node* _deleteElement(Node*, const T &); 
        Node* _find(Node*, const T &) const;
};

template <typename T>
BST<T>::BST() : root(nullptr) {}

template <typename T>
BST<T>::BST(const T& val) {
    root = new BST<T>::Node(val);
}

template <typename T>
BST<T>::BST(const BST <T>& oth) {
    root = _copy(oth.root);
}

template <typename T>
BST<T>::BST(BST<T> && oth) noexcept {
    root = oth.root;
    oth.root = nullptr;
}

template <typename T>
BST<T>::BST(std::initializer_list<T> init) {
    for (auto& i : init) {
        insert(i);
    }
}

template <typename T>
BST<T>::~BST() {
    _delete(root);
}

template <typename T>
BST<T>& BST<T>::operator=(const BST& rhs) {
    if (this = &rhs) {
        return this;
    }
    _delete(root);
    root = _copy(rhs.root);

}

template <typename T>
BST<T>& BST<T>::operator=(BST && rhs) noexcept {
    _delete(root);
    root = rhs.root;
    rhs.root = nullptr;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const BST<T>& cur) {
    typename BST<T>::iterator it(cur.root);
    while(!it.empty()) {
        out << *it << "  ";
        ++it;
    }
    return out;
}

template <typename T>
bool BST<T>::operator==(const BST& oth) const {
    if(this->get_number_of_nodes(root) != oth.get_number_of_nodes(oth.get_root())) {
        return false;
    }
    auto j = begin();
    for (auto i = oth.begin(); i != oth.end(); ++i, ++j) {
        if (*i != *j) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool BST<T>::operator!=(const BST & rhs) const {
    return !(*this == rhs);
}

template <typename T>
BST<T> BST<T>::operator+(const BST& oth) const {
    BST<T> tmp = *this;
    for (const auto& i : oth) {
        tmp.insert(i);
    }
    return tmp;
}

template <typename T>
BST<T>& BST<T>::operator+=(const BST& oth) {
    *this = *this + oth;
    return *this;
}

template <typename T>
void BST<T>::insert(const T& val) {
    if (root == nullptr) {
        root = new BST<T>::Node(val);
    }
    else {
        _insert(root,val);
    }
}

template <typename T>
bool BST<T>::empty() const {
    return !root;
}

template <typename T>
int BST<T>::get_height(const Node * cur) const {   
    if (cur == nullptr) {
        return 0;
    }
    else {
        int rightHeight = get_height(cur->right);
        int leftHeight = get_height(cur->left);
        if (rightHeight > leftHeight) {
            return rightHeight + 1;
        }
        else {
            return leftHeight + 1;
        }
    }
}
template <typename T>
bool BST<T>::contains(const T& val) const {
    return *find(val);
}

template <typename T>
int BST<T>::get_number_of_nodes(const Node * cur) const  {
    if (cur == nullptr) {
        return 0;
    }
    int lcount = get_number_of_nodes(cur->left);
    int rcount = get_number_of_nodes(cur->right);
    return lcount + rcount + 1;
}

template <typename T>
void BST<T>::inorder(const Node* cur) const {
    if (cur == nullptr) {
        return;
    }
    inorder(cur->left);
    std::cout << cur->data << "  ";
    inorder(cur->right);
}

template <typename T>
void BST<T>::preorder(const Node* cur) const {
    if (cur == nullptr) {
        return;
    }
    std::cout << cur->data << "  ";
    preorder(cur->left);
    preorder(cur->right);
}

template <typename T>
void BST<T>::postorder(const Node* cur) const {
    if (cur == nullptr) {
        return;
    }
    postorder(cur->left);
    postorder(cur->right);
    std::cout << cur->data << "  ";
}

template <typename T>
void BST<T>::levelorder(const Node* cur) const {
    int height = get_height(cur);
    for (int i = 0; i <= height; ++i) {
        _printLevel(cur, i);
        std::cout << std::endl;
    }
}

template <typename T>
void BST<T>::clear() {
    _delete(root);
}


template <typename T>
void BST<T>::erase(const T& val) {
    root = _deleteElement(root, val);
}

template <typename T>
typename BST<T>::iterator BST<T>::find(const T& val) const {
    return iterator(_find(root, val));
}

template <typename T>
BST<T> BST<T>::merge(BST<T> tree) {
    return *this + tree;
}

template <typename T>
typename BST<T>::Node *BST<T>::get_root() const {
    return root;
}

template <typename T>
const T& BST<T>::get_root_data() const {
    return root->data;
}

template <typename T>
typename BST<T>::Node* BST<T>::_copy(BST<T>::Node* node) {
    if (node == nullptr) {
        return nullptr;
    }
    BST<T>::Node* newNode = new BST<T>::Node(node->data);
    newNode->left = _copy(node->left);
    newNode->right = _copy(node->right);
    newNode->parent = nullptr;
    return newNode;
}

template <typename T>
void BST<T>::_delete(BST<T>::Node* node) {
    if (node == nullptr) {
        return;
    }
    _delete(node->left);
    _delete(node->right);
    delete node;
    node = nullptr;
    
}

template <typename T>
void BST<T>::_insert(BST<T>::Node* cur, const T& val) {
    if (val == cur->data) {
        return;
    }
    if (val < cur->data) {
        if (cur->left == nullptr) {
            cur->left = new BST<T>::Node(val);
            cur->left->parent = cur;
        }
        else {
            _insert(cur->left, val);
        }
    }
    else {
        if (cur->right == nullptr) {
            cur->right = new BST<T>::Node(val);
            cur->right->parent = cur;
        }
        else {
            _insert(cur->right, val);
        }
    }
}
template <typename T>
void BST<T>::_printLevel(const Node* cur, int level) const {
    if (cur == nullptr) {
        return;
    }
    if (level == 1) {
        std::cout << cur->data << "  ";
    }
    else if (level > 1) {
        _printLevel(cur->right, level - 1);
        _printLevel(cur->left, level - 1);
    }
}

template <typename T>
typename BST<T>::Node* BST<T>::_findMinNode(Node * cur) {
    if (cur == nullptr) {
        return cur;
    }
    if (cur->left == nullptr) {
        return cur;
    }
    return _findMinNode(cur->left);
}

template <typename T>
typename BST<T>::Node* BST<T>::_deleteElement(Node * cur, const T& val) {
    if (cur == nullptr) {
        return nullptr;
    }
    if (val > cur->data) {
        cur->right = _deleteElement(cur->right, val);
    }
    if (val < cur->data) {
        cur->left = _deleteElement(cur->left, val);
    }
    if (!cur->right && !cur-> left) {
        delete cur;
        return nullptr;
    }
    if (!cur->right) {
        Node* tmp = cur->left;
        delete cur;
        return tmp;
    }
    if (!cur->left) {
        Node* tmp = cur->right;
        delete cur;
        return tmp;
    }
    const Node* tmp = _findMinNode(cur->right);
    cur->data = tmp->data;
    cur->right = _deleteElement(cur->right, tmp->data);

    return cur;
}
template <typename T>
typename BST<T>::Node* BST<T>::_find(Node * cur, const T& val) const {
    if (cur == nullptr) {
        return nullptr;
    }
    if (cur->data == val) {
        return cur;
    }
    if (cur->data > val) {
        return _find(cur->left, val);
    }
    else {
        return _find(cur->right, val);
    }
}

template <typename T>
typename BST<T>::iterator BST<T>::begin() const { return iterator(root); }

template <typename T>
typename BST<T>::iterator BST<T>::end() const { return iterator(nullptr);}        


#endif


