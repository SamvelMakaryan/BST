template <typename T>
BST<T>::BST() : root(nullptr) {}

template <typename T>
BST<T>::BST(const T& val) {
    root = new BST<T>::Node(val);
}

template <typename T>
BST<T>::BST(const BST<T>& oth) {
    root = copy(oth.root);
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
    if (root){
        deleteHelper(root);
    }
}

template <typename T>
BST<T>& BST<T>::operator=(const BST& rhs) {
    if (this == &rhs) {
        return *this;
    }
    deleteHelper(root);
    root = copy(rhs.root);
    return *this;
}

template <typename T>
BST<T>& BST<T>::operator=(BST && rhs) noexcept {
    deleteHelper(root);
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
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
    if(this->get_number_of_nodes_helper(root) != oth.get_number_of_nodes_helper(oth.root)) {
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
        insert(root,val);
    }
}

template <typename T>
bool BST<T>::empty() const {
    return !root;
}

template <typename T>
int BST<T>::get_height_helper(const Node * cur) const {   
    if (cur == nullptr) {
        return 0;
    }
    else {
        int rightHeight = get_height_helper(cur->right);
        int leftHeight = get_height_helper(cur->left);
        if (rightHeight > leftHeight) {
            return rightHeight + 1;
        }
        else {
            return leftHeight + 1;
        }
    }
}

template <typename T>
inline int BST<T>::get_number_of_nodes_helper(const Node* cur) const
{
    if (cur == nullptr) {
        return 0;
    }
    int lNodes = get_number_of_nodes_helper(cur->left);
    int rNodes = get_number_of_nodes_helper(cur->right);
    return lNodes + rNodes + 1;
}

template <typename T>
bool BST<T>::contains(const T& val) const {
    return *find(val);
}

template <typename T>
int BST<T>::get_height() const {
    if (root == nullptr) {
        return 0;
    }
    return get_height_helper(root);
}

template <typename T>
int BST<T>::get_number_of_nodes() const  {
    if (root == nullptr) {
        return 0;
    }
    return get_number_of_nodes_helper(root);
}

template <typename T>
void BST<T>::inorder() const {
    if (root == nullptr) {
        return;
    }
    inorderHelper(root);
}

template <typename T>
void BST<T>::preorder() const {
    if (root == nullptr) {
        return;
    }
    preorderHelper(root);
}

template <typename T>
void BST<T>::postorder() const {
    if (root == nullptr) {
        return;
    }
    postorderHelper(root);
}

template <typename T>
void BST<T>::levelorder() const {
    int height = get_height();
    for (int i = 0; i <= height; ++i) {
        levelorder(root, i);
        std::cout << std::endl;
    }
}

template <typename T>
void BST<T>::clear() {
    deleteHelper(root);
}

template <typename T>
void BST<T>::erase(const T& val) {
    root = deleteElement(root, val);
}

template <typename T>
typename BST<T>::iterator BST<T>::find(const T& val) const {
    return iterator(find(root, val));
}

template <typename T>
BST<T> BST<T>::merge(BST<T> tree) {
    return *this + tree;
}

template <typename T>
const T& BST<T>::get_root_data() const {
    return root->data;
}

template <typename T>
void BST<T>::inorderHelper(const Node * root) const {
    if (root == nullptr) {
        return;
    }
    inorderHelper(root->left);
    std::cout << root->data << " ";
    inorderHelper(root->right);
}

template <typename T>
void BST<T>::preorderHelper(const Node* root) const {
    if (root == nullptr) {
        return;
    }
    std::cout << root->data << " ";
    preorderHelper(root->left);
    preorderHelper(root->right);
}

template <typename T>
void BST<T>::postorderHelper(const Node* root) const {
    if (root == nullptr) {
        return;
    }
    postorderHelper(root->left);
    postorderHelper(root->right);
    std::cout << root->data << " ";
}

template <typename T>
typename BST<T>::Node *BST<T>::copy(Node *node, Node *parent)
{
    if (node == nullptr) {
        return nullptr;
    }
    BST<T>::Node* newNode = new BST<T>::Node(node->data, parent);
    newNode->left = copy(node->left, newNode);
    newNode->right = copy(node->right, newNode);
    return newNode;
}

template <typename T>
void BST<T>::deleteHelper(Node*& node) {
    if (node == nullptr) {
        return;
    }
    deleteHelper(node->left);
    deleteHelper(node->right);
    delete node;
    node = nullptr;
}

template <typename T>
void BST<T>::insert(BST<T>::Node* cur, const T& val) {
    if (val == cur->data) {
        return;
    }
    if (val < cur->data) {
        if (cur->left == nullptr) {
            cur->left = new BST<T>::Node(val);
            cur->left->parent = cur;
        }
        else {
            insert(cur->left, val);
        }
    }
    else {
        if (cur->right == nullptr) {
            cur->right = new BST<T>::Node(val);
            cur->right->parent = cur;
        }
        else {
            insert(cur->right, val);
        }
    }
}

template <typename T>
void BST<T>::levelorder(const Node* cur, int level) const {
    if (cur == nullptr) {
        return;
    }
    if (level == 1) {
        std::cout << cur->data << "  ";
    }
    else if (level > 1) {
        levelorder(cur->left, level - 1);
        levelorder(cur->right, level - 1);
    }
}

template <typename T>
typename BST<T>::Node* BST<T>::findMinNode(Node * cur) {
    if (cur == nullptr) {
        return cur;
    }
    if (cur->left == nullptr) {
        return cur;
    }
    return findMinNode(cur->left);
}

template <typename T>
typename BST<T>::Node* BST<T>::deleteElement(Node * cur, const T& val) {
    if (cur == nullptr) {
        return nullptr;
    }
    if (val > cur->data) {
        cur->right = deleteElement(cur->right, val);
        return cur;
    }
    if (val < cur->data) {
        cur->left = deleteElement(cur->left, val);
        return cur;
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
    const Node* tmp = findMinNode(cur->right);
    cur->data = tmp->data;
    cur->right = deleteElement(cur->right, tmp->data);

    return cur;
}

template <typename T>
typename BST<T>::Node* BST<T>::find(Node * cur, const T& val) const {
    if (cur == nullptr) {
        return nullptr;
    }
    if (cur->data == val) {
        return cur;
    }
    if (cur->data > val) {
        return find(cur->left, val);
    }
    else {
        return find(cur->right, val);
    }
}

template <typename T>
typename BST<T>::iterator BST<T>::begin() const {
     return iterator(root);
}

template <typename T>
typename BST<T>::iterator BST<T>::end() const { 
    return iterator(nullptr);
}        

template <typename T>
BST<T>::iterator::iterator(Node* node) : cur(node), size(number_of_nodes(cur)) {
    if(cur) {
        while (cur->left) {
            cur = cur->left;
        }
    }
}

template <typename T>
typename BST<T>::iterator& BST<T>::iterator::operator++() {
    if (size <= 1) {
        cur = nullptr;
        return *this;
    }
    if (cur->right) {
        cur = cur->right;
        while (cur->left) {
            cur = cur->left;
        }
    }
    else {
        while (cur->parent && cur->parent->right == cur) {
            cur = cur->parent;
        }
        cur = cur->parent;
    }
    --size;
    return *this;
}

template <typename T>
bool BST<T>::iterator::empty() const {
        return !cur;
}

template <typename T>
T& BST<T>::iterator::operator*() {
    if (cur == nullptr) {
        throw std::invalid_argument("Dereferencing NULL pointer");
    }
    return cur->data;
}

template <typename T>        
const T& BST<T>::iterator::operator*() const {
    if (cur == nullptr) {
        throw std::invalid_argument("Dereferencing NULL pointer");
    }
    return cur->data;
}    

template <typename T>        
bool BST<T>::iterator::operator!=(const iterator& oth) const {
    return cur != oth.cur;
}

template <typename T>        
bool BST<T>::iterator::operator==(const iterator& oth) const {
    return !(operator!=(oth));
}

template <typename T>
int BST<T>::iterator::number_of_nodes(Node* cur) const {
    if (cur == nullptr) {
        return 0;
    }
    int lNodes = number_of_nodes(cur->left);
    int rNodes = number_of_nodes(cur->right);
    return lNodes + rNodes + 1;
}

template <typename T>        
BST<T>::Node::Node(T data, Node* parent) 
    : data(data),
    left(nullptr),
    right(nullptr),
    parent(parent) 
    {}