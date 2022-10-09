/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = y;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = y; 
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{

    if (subtree == nullptr) {
        return;
    }

    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (balance == -2) {
        int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if ( l_balance  == -1 ) {
            // one of the rotations
            rotateRight(subtree);
        } else {
            // other rotation
            rotateLeftRight(subtree);
        }
    } else if (balance == 2) {
        int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (r_balance  == 1 ) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here

    // now you have to recurse up the tree, if you find imbalance call the appropriate rotation . . .

    if (subtree == nullptr) {
        Node* tmp = new Node(key, value);
        subtree = tmp;
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
        rebalance(subtree);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
        rebalance(subtree);
    } else if (subtree->key == key) {
        subtree->value = value;
        return;
    }

    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) {
        return;
    }

    if (key < subtree->key) {
        // your code here
        // recursive call
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            // this is the hardest
            Node* tmp = subtree->left;
            while (tmp->right != nullptr) {
                tmp = tmp->right;
            }
            swap(subtree, tmp);
            remove(subtree->left, key);
            rebalance(subtree);
        } else {
            /* one-child remove */
            // your code here

            Node* tmp;
            if (subtree->right != nullptr) {
                tmp = subtree;
                subtree = subtree -> right;
                delete tmp;
                tmp = nullptr;
                rebalance(subtree);
            } else {
                tmp = subtree;
                subtree = subtree->left;
                delete tmp;
                tmp = nullptr;
                rebalance(subtree);
            }
        }
        subtree->height = 1 + std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
    }
}
