#include <iostream>
#include <string>

struct Node {
    int data;
    int k;
};

void Swap(Node &a, Node &b) {
  Node tmp;
  tmp.data = a.data;
  tmp.k = a.k;

  a.data = b.data;
  a.k = b.k;
  b.data = tmp.data;
  b.k = tmp.k;

}

void Copy(Node &a, Node &b) {
  a.data = b.data;
  a.k = b.k;
}

struct BinaryHeap {
    Node *array;
    int size = 0;
    int f = 0;

    void Size() {
      std::cout << size << '\n';
    }

    void GetMin() {
      std::cout << array[0].data << '\n';
    }

    void ExtractMin() {
      int min = array[0].data;
      Copy(array[0], array[size - 1]);
      --size;
      std::cout << min << '\n';
      SiftDown(0);

    }

    void Delete(int i) {
      Copy(array[i], array[size - 1]);
      --size;
      SiftDown(i);
      SiftUp(i);
      std::cout << "ok" << '\n';
    }

    void Change(int i, int n) {
      array[i].data = n;
      SiftDown(i);
      SiftUp(i);
      std::cout << "ok" << '\n';
    }

    void Push(int value) {
      ++f;
      array[size].data = value;
      array[size].k = f;
      ++size;
      SiftUp(size - 1);
      std::cout << "ok" << '\n';
    }

    void SiftDown(int idx) {
      if (idx >= size) {
        return;
      }
      int idx_of_max = idx;
      int left_son = 2 * idx + 1;
      int right_son = 2 * idx + 2;
      if (left_son < size && array[left_son].data < array[idx_of_max].data) {
        idx_of_max = left_son;
      }
      if (right_son < size && array[right_son].data < array[idx_of_max].data) {
        idx_of_max = right_son;
      }
      if (idx_of_max != idx) {
        Swap(array[idx], array[idx_of_max]);
        SiftDown(idx_of_max);
      }
    }

    void SiftUp(int idx) {
      while (idx > 0 && array[(idx - 1) / 2].data > array[idx].data) {
        Swap(array[(idx - 1) / 2], array[idx]);
        idx = (idx - 1) / 2;
      }
    }

    void Clear() {
      size = 0;
      for (int i = 0; i < size; ++i) {
        array[i].data = 0;
        array[i].k = 0;
      }
      std::cout << "ok" << '\n';
    }
};

int main() {
  int m;
  std::cin >> m;
  BinaryHeap heap;
  heap.array = new Node[m];
  std::string sa;
  int n, x;
  for (int i = 0; i < m; ++i) {
    std::cin >> sa;

    if (sa == "insert") {
      std::cin >> n;
      heap.Push(n);
    }

    if (sa == "extract_min") {
      if (heap.size != 0) {
        heap.ExtractMin();
      } else {
        std::cout << "error" << '\n';
      }
    }

    if (sa == "delete") {
      std::cin >> n;
      x = -1;
      for (int j = 0; j < heap.size; ++j) {
        if (heap.array[j].k == n) {
          x = j;
          break;
        }
      }
      if (x != -1) {
        heap.Delete(x);
      } else {
        std::cout << "error" << '\n';
      }
    }

    if (sa == "change") {
      std::cin >> n;
      x = -1;
      for (int j = 0; j < heap.size; ++j) {
        int t = heap.array[j].k;
        if (heap.array[j].k == n) {
          x = j;
          break;
        }
      }
      std::cin >> n;
      if (x != -1) {
        heap.Change(x, n);
      } else {
        std::cout << "error" << '\n';
      }
    }

    if (sa == "get_min") {
      if (heap.size != 0) {
        heap.GetMin();
      } else {
        std::cout << "error" << '\n';
      }
    }

    if (sa == "size") {
      heap.Size();
    }

    if (sa == "clear") {
      heap.Clear();
    }
  }
  delete[] heap.array;
}
