#include<iostream>
#include<memory>
#include<thread>
#include<string>
#include<print>
#include<mutex>
#include<condition_variable>
#include <cstdlib>
#include <ctime>
#include <vector>

class Adder {
private:
    int sum = 0;
    int id;
public:
    Adder(int id_): id(id_) {}
    int add() {
        sum = 0;
        for (int i = 0; i < 100; i++) {
            sum += rand() % 1000;
        }
        return sum;
    }

    int get_sum() const { return sum; }
    int get_id() const { return id; }

    bool operator<(const Adder &other) const {
        return sum < other.sum;
    }
};

Adder* find_max(std::vector<Adder>& adders) {
    if (adders.empty()) return nullptr;

    Adder* max_adder = &adders[0];
    for (auto& adder : adders) {
        if (*max_adder < adder) {
            max_adder = &adder;
        }
    }
    return max_adder;
}


int main() {
    srand(time(0));

    std::vector<Adder> adders;
    for (int i = 1; i <= 10; i++) {
        adders.emplace_back(i);
    }

    std::vector<std::thread> threads;
    for (auto& adder : adders) {
        threads.emplace_back([&adder]() {
            adder.add();
        });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    for (auto& adder : adders) {
        std::println("Sum{} = {}", adder.get_id(), adder.get_sum());
    }

    Adder* max_adder = find_max(adders);
    if (max_adder) {
        std::println("Highest Sum{}: {}", max_adder->get_id(), max_adder->get_sum());
    }

}
