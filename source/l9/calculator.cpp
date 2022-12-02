#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <string_view>

bool is_greater(char a, char b) {
    // Judge the priority of the two operators
    // Return true if a is greater thean b

    if (a == '*' || a == '/') {
        if (b == '+' || b == '-') {
            return true;
        }
        return false;
    } else {
        return false;
    }
}

bool is_greater_or_equal(char a, char b) {
    // Judge the priority of the two operators
    // Return true if a is greater or equal than b
    return !(is_greater(b, a));
}

void move_op(char op1, std::queue<char> &output, std::stack<char> &ops) {
    // op1 is the incoming operator
    while (!ops.empty() && is_greater_or_equal(ops.top(), op1)) {
        output.push(ops.top());
        ops.pop();
    }
}

void get_suffix(std::string_view input, std::queue<char> &output) {
    std::stack<char> ops;
    for (auto &c : input) {
        // Iterate the string
        // std::cout << c;
        if (std::isdigit(c)) {
            output.push(c);
        } else {
            if (ops.empty()) {
                ops.push(c);
            } else {
                move_op(c, output, ops);
                ops.push(c);
            }
        }
    }
    while (!ops.empty()) {
        output.push(ops.top());
        ops.pop();
    }
}

void print_queue(std::queue<char> q) {
    // Make a copy of the queue
    std::cout << "The suffix expression is: ";
    while (!q.empty()) {
        std::cout << q.front();
        q.pop();
    }
    std::cout << "\n";
}

float evaluate_suffix(std::queue<char> &suffix) {
    std::stack<float> nums;
    while (!suffix.empty()) {
        if (std::isdigit(suffix.front())) {
            nums.push(suffix.front() - '0');
        } else {
            float a = nums.top();
            nums.pop();
            float b = nums.top();
            nums.pop();
            switch (suffix.front()) {
                case '+':
                    nums.push(a + b);
                    break;
                case '-':
                    nums.push(b - a);
                    break;
                case '*':
                    nums.push(a * b);
                    break;
                case '/':
                    nums.push(b / a);
                    break;
            }
        }
        suffix.pop();
    }
    return nums.top();
}

int main() {
    std::queue<char> output;
    std::string      input;
    std::getline(std::cin, input);

    get_suffix(input, output);
    print_queue(output);
    std::cout << "The result is: " << evaluate_suffix(output) << "\n";
}
