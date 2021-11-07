// Copyright 2021 by FORTYSS

#ifndef INCLUDE_STACKSECOND_HPP_
#define INCLUDE_STACKSECOND_HPP_

#include <utility>
#include <memory>


template <typename T>
class StackTwo
{
 public:
  StackTwo(const StackTwo&) = delete;
  StackTwo& operator = (const StackTwo&) = delete;
  StackTwo(): ref(nullptr) {}
  ~StackTwo(){
    while (ref) {
      pop();
    }
  }
  template <typename ... Args>
  void push_emplace(Args&&... value) {
    ref = std::move(std::make_unique<StackObj>(
        StackObj(std::move(ref), std::move(T(std::forward<Args>(value)...)))));
  }
  void push(T&& value) {
    ref = std::move(std::make_unique<StackObj>(
        StackObj(std::move(ref), std::forward<T>(value))));
  }
  const T& head() const {
    return ref->val;
  }
  T pop() {
    if (ref!= nullptr) {
      T del = std::move(ref->val);
      ref = std::move(ref->last);
      return del;
    }
    throw std::runtime_error("Stack is empty");
  }
 private:
  struct StackObj{
    std::unique_ptr<StackObj> last;
    T val;
    explicit StackObj(std::unique_ptr<StackObj> ref = nullptr, T&& valu = T()) {
      val = std::forward<T>(valu);
      last = std::move(ref);
    }
  };
  std::unique_ptr<StackObj> ref;
};

#endif  // INCLUDE_STACKSECOND_HPP_


