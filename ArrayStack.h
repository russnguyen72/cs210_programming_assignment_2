#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class ArrayStack {
private:
    std::vector<T> data;

public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (data.empty()) {
            throw std::runtime_error("Stack is empty");
            return;
        }
        data.pop_back();
    }

    T top() const {
        if (data.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

#endif
