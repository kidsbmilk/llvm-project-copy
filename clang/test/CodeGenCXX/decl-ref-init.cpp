// RUN: %clang_cc1 -no-opaque-pointers -triple x86_64-apple-darwin -emit-llvm %s -o - | \
// RUN: FileCheck %s
// RUN: %clang_cc1 -no-opaque-pointers -triple i386-apple-darwin -emit-llvm %s -o - | \
// RUN: FileCheck %s

struct A {};

struct B 
{ 
  operator A&();
}; 


struct D : public B {
  operator A();
};

extern B f(); 
extern D d(); 

int main() {
	const A& rca = f();
	const A& rca2 = d();
}

// CHECK: call noundef nonnull align {{[0-9]+}} dereferenceable({{[0-9]+}}) %struct.A* @_ZN1BcvR1AEv
// CHECK: call noundef nonnull align {{[0-9]+}} dereferenceable({{[0-9]+}}) %struct.A* @_ZN1BcvR1AEv
