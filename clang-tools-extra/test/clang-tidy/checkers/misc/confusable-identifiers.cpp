// RUN: %check_clang_tidy %s misc-confusable-identifiers %t

int fo;
// CHECK-MESSAGES: :[[#@LINE-1]]:5: warning: fo is confusable with ðo [misc-confusable-identifiers]
int ðo;
// CHECK-MESSAGES: :[[#@LINE-1]]:5: note: other declaration found here

void no() {
  int ðoo;
}

void worry() {
  int foo;
}

int ði;
// CHECK-MESSAGES: :[[#@LINE-1]]:5: warning: ði is confusable with fi [misc-confusable-identifiers]
int fi;
// CHECK-MESSAGES: :[[#@LINE-1]]:5: note: other declaration found here

// should not print anything
namespace ns {
struct Foo {};
} // namespace ns
auto f = ns::Foo();
