// RUN: %clang_cc1 -fsyntax-only -verify %s
// expected-no-diagnostics

// PR8345
template<typename T> T f(T* value) {
  return __sync_add_and_fetch(value, 1);
}
int g(long long* x) { return f(x); }
int g(int* x) { return f(x); }

namespace PR11320 {
  template<typename T> 
  void g(unsigned *x) { 
    __sync_bool_compare_and_swap(x, 1, 4); 
  }
  void h() { g<int>(0); }
}

// Can pass value dependent integer to atomic builtin
template <int Order>
void fetchAdd(int *A, int V) {
  __atomic_fetch_add(A, V, Order);
}

void fetchAddUse(int *A, int V) {
  fetchAdd<__ATOMIC_ACQ_REL>(A, V);
}
