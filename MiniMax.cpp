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

    int Size() {
      return size;
    }

    int GetMin() {
      return array[0].data;
    }

    int GetMax() {
      int max = 0;
      for (int j = 0; j < size; ++j) {
        if (array[j].data > max) {
          max = array[j].data;
        }
      }
      return max;
    }

    int ExtractMin() {
      int min = array[0].data;
      Copy(array[0], array[size - 1]);
      --size;
      SiftDown(0);
      return min;
    }

    int ExtractMax() {
      Node max;
      max.data = 0;
      int i;
      for (int j = 0; j < size; ++j) {
        if (array[j].data >= max.data) {
          max = array[j];
          i = j;
        }
      }
      Delete(i);
      return max.data;
    }

    void Delete(int i) {
      Copy(array[i], array[size - 1]);
      --size;
      SiftDown(i);
      SiftUp(i);
    }

    void Push(int value) {
      ++f;
      array[size].data = value;
      array[size].k = f;
      ++size;
      SiftUp(size - 1);

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
      std::cout << "ok" << '\n';
    }
    if (sa == "extract_min") {
      if (heap.size != 0) {
        std::cout << heap.ExtractMin() << '\n';
      } else {
        std::cout << "error" << '\n';
      }
    }
    if (sa == "extract_max") {
      if (heap.size == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << heap.ExtractMax() << '\n';
      }
    }
    if (sa == "get_min") {
      if (heap.size != 0) {
        std::cout << heap.GetMin() << '\n';
      } else {
        std::cout << "error" << '\n';
      }
    }
    if (sa == "get_max") {
      if (heap.size == 0) {
        std::cout << "error" << '\n';
      } else {
        std::cout << heap.GetMax() << '\n';
      }
    }
    if (sa == "size") {
      std::cout << heap.Size() << '\n';
    }
    if (sa == "clear") {
      heap.Clear();
      std::cout << "ok" << '\n';
    }
  }
  delete[] heap.array;
}
