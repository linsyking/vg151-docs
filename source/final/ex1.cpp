#include <string>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>


using namespace std;

void ex1_reverse_array() {
    array<string, 10000> re;
    string               word;
    size_t               count = 0;
    while (cin >> word) re[count++] = word;
    for (auto iter = re.cbegin() + count - 1; iter != re.cbegin() - 1; --iter) {
    }
}
void ex1_reverse_vector() {
    vector<string> re;
    string         word;
    while (cin >> word) re.push_back(word);
    for (auto iter = re.crbegin(); iter != re.crend(); ++iter) {
    }
}
void ex1_reverse_stack() {
    stack<string> re;
    string        word;
    while (cin >> word) re.push(word);
    for (; !re.empty(); re.pop()) {
    };
}
void ex1_ordered_queue() {
    queue<string> re;
    string        word;
    while (cin >> word) re.push(word);
    for (; !re.empty(); re.pop()) {
    };
}
