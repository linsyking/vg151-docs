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

void get_suffix(std::string_view input, std::queue<char> &output) {
    // Generate the suffix expression and store it in output

    // ops is the stack of operators
    std::stack<char> ops;
    for (auto &c : input) {
        // Iterate each char in the string
        // std::cout << c;
        // TODO
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
    // Evaluate Suffix Expression
    // Return the result
    // TODO
}

int main() {
    std::queue<char> output;
    std::string      input;
    std::getline(std::cin, input);

    get_suffix(input, output);
    print_queue(output);
    std::cout << "The result is: " << evaluate_suffix(output) << "\n";
}
