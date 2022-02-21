#include <iostream>

int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  return b;
}

struct Node {
    //Node *parent;
    Node *left_child = nullptr;
    Node *right_child = nullptr;
    int data;
};

struct Tree {
    Node *root = nullptr;

    bool Find(int needed) {
      for (Node *node = root; node;) {
        if (node->data == needed) {
          return true;
        }
        if (needed < node->data) {
          node = node->left_child;
        } else {
          node = node->right_child;
        }
      }
      return false;
    }

    void Insert(int data) {
      Node *pv = new Node;
      pv->data = data;
      if (root == nullptr) {
        root = pv;
        return;
      }
      Node *current = root;
      while (current != nullptr) {
        //pv->parent = current;
        if (data >= current->data) {
          if (current->right_child != nullptr) {
            current = current->right_child;
          } else {
            current->right_child = pv;
            return;
          }
        } else {
          if (current->left_child != nullptr) {
            current = current->left_child;
          } else {
            current->left_child = pv;
            return;
          }
        }
      }
    }

    void Clear(Node *t) {
      if (t != nullptr) {
        Clear(t->left_child);
        Clear(t->right_child);
        delete t;
        t = nullptr;
      }
    }
};

int Heigh(Node *node) {
  if (node == nullptr) {
    return 0;
  }

  return 1 + max(Heigh(node->right_child), Heigh(node->left_child));
}

void InorderWalk(Node *x) {
  if (x != nullptr) {
    InorderWalk(x->left_child);
    std::cout << x->data << '\n';
    InorderWalk(x->right_child);
  }
}
