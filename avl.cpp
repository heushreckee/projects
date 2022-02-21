#include <iostream>

struct Node {
    long long key;
    int height;
    Node *left;
    Node *right;

    Node(long long k) {
      key = k;
      left = right = nullptr;
      height = 1;
    }
};

struct Tree {
    Node *root = nullptr;
    int size = 0;

    int Height(Node *p) {
      return p != nullptr ? p->height : 0;
    }

    int Bfactor(Node *p) {
      return Height(p->right) - Height(p->left);
    }

    void Fixheight(Node *p) {
      unsigned char hl = Height(p->left);
      unsigned char hr = Height(p->right);
      p->height = (hl > hr ? hl : hr) + 1;
    }

    Node *Rotateright(Node *p) {
      Node *q = p->left;
      p->left = q->right;
      q->right = p;
      Fixheight(p);
      Fixheight(q);
      return q;
    }

    Node *Rotateleft(Node *q) {
      Node *p = q->right;
      q->right = p->left;
      p->left = q;
      Fixheight(q);
      Fixheight(p);
      return p;
    }

    Node *Balance(Node *p) {
      Fixheight(p);
      if (Bfactor(p) == 2) {
        if (Bfactor(p->right) < 0) {
          p->right = Rotateright(p->right);
        }
        return Rotateleft(p);
      }
      if (Bfactor(p) == -2) {
        if (Bfactor(p->left) > 0) {
          p->left = Rotateleft(p->left);
        }
        return Rotateright(p);
      }
      return p;
    }

    Node *Insert(Node *p, long long k) {
      ++size;
      if (p == nullptr) {
        return new Node(k);
      }
      if (k < p->key) {
        p->left = Insert(p->left, k);
      } else {
        p->right = Insert(p->right, k);
      }
      return Balance(p);
    }

    long long Findmin(Node *p, long long &x) {
      long long temp = -1;
      for (Node *node = root; node != nullptr;) {
        if (node->key == x) {
          return x;
        }
        if (x < node->key) {
          temp = node->key;
          node = node->left;
        } else {
          node = node->right;
        }
      }
      return temp;
    }

    bool Find(int needed) {
      for (Node *node = root; node != nullptr;) {
        if (node->key == needed) {
          return true;
        }
        if (needed < node->key) {
          node = node->left;
        } else {
          node = node->right;
        }
      }
      return false;
    }

    void Clear(Node *t) {
      if (t != nullptr) {
        Clear(t->left);
        Clear(t->right);
        delete t;
        t = nullptr;
      }
    }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  char sa;
  bool flag = true;
  Tree t;
  long long x;
  long long y = -1;
  for (int i = 0; i < n; ++i) {
    std::cin >> sa;
    if (sa == '+') {
      if (flag) {
        std::cin >> x;
        t.root = t.Insert(t.root, x);
      } else {
        std::cin >> x;
        x = (x + y) % 1000000000;
        t.root = t.Insert(t.root, x);
        flag = true;
      }
    } else {
      flag = false;
      std::cin >> x;
      y = t.Findmin(t.root, x);
      std::cout << y << '\n';
    }
  }

  t.Clear(t.root);
}
