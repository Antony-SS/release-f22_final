/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    BST<K, V>::Node*& found = find(root, key);
    if (found == nullptr) {
        return V();
    } else {
        return found->value;
    }
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{

    if (subtree != nullptr) {
        if (subtree->key == key) {
            return subtree;
        } else if (key < subtree->key) { 
            return find(subtree->left, key);
        } else {
            return find(subtree->right, key);
        }
    }
    return subtree;
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here

    BST<K, V>::Node*& found = find(subtree, key);

    if (found != nullptr) {
        return; // if other shit fails update value
    } else {
        BST<K, V>::Node* node = new Node(key, value);
        found = node;
    }

}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{


    // your code here
    // K fkey = first->key;
    // V fval = first->value;
    // K skey = second->key;
    // V sval = second->value;

    // first->key = skey;
    // first->value = sval;

    // second->key = fkey;
    // second->value = fval;

    // first will be IOP, second will be FOUND

    // BST<K, V>::Node* IOPtmpleft = found;

    // BST<K, V>::Node* IOPtmpleft = first->left;
    // BST<K, V>::Node* IOPtmpright = first->right;

    // BST<K, V>::Node* foundlefttmp = found->left;
    // BST<K, V>::Node* foundrighttmp = found->right;

    // // BST<K, V>::Node* foundleftrighttmp = found->left->right;

    // found = IOP;

    




}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    BST<K, V>::Node*& found = find(root, key);
    
    // not in tree case
    if (found == nullptr) {
        return;
    } 
    
    // leaf node case
    if (found->left == nullptr && found->right==nullptr) { 
        delete found;
        found = nullptr;
        return;
    }

    // single child cases
    if (found->left == nullptr && found->right != nullptr) { // one child case right
        BST<K, V>::Node* tmp = found->right;
        delete found;
        found = tmp;
        return;
    } else if (found->left != nullptr && found->right == nullptr) { // one child case left
        BST<K, V>::Node* tmp = found->left;
        delete found;
        found = tmp;
        return;
    } else if (found->left != nullptr && found->right != nullptr) { // two child case
        //TODO

        // first we find IOP
        BST<K, V>::Node* IOP = found->left;
        while (IOP->right != nullptr) {
            IOP = IOP->right;
        }

        // swap(found, IOP);

        // std::cout << "FUCK" << std::endl;

        // delete IOP;
        
        // return;
    }
    // process 
}



template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here

    // no helper function needed!
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V>* toReturn = new BST<K, V>();
    for (unsigned i = 0; i < inList.size(); i++) {
        K one = inList[i].first;
        // K one = i.first();
        V two = inList[i].second;
        toReturn->insert(one, two);
    }
    return *toReturn;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here

    return std::vector<int>();
}