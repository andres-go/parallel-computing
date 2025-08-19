#include<iostream>
#include<thread>
#include<string>
#include<print>
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

    int getSum() const { return sum; }
    int getId() const { return id; }

    bool operator<(const Adder &other) const {
        return sum < other.sum;
    }
};

Adder* find_max(std::vector<Adder>& adders) {
    if (adders.empty()) return nullptr;

    Adder* maxAdder = &adders[0];
    for (auto& adder : adders) {
        if (*maxAdder < adder) {
            maxAdder = &adder;
        }
    }
    return maxAdder;
}


int main() {
    srand(time(nullptr));

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
        std::println("Sum{} = {}", adder.getId(), adder.getSum());
    }

    Adder* maxAdder = find_max(adders);
    if (maxAdder) {
        std::println("Highest Sum{}: {}", maxAdder->getId(), maxAdder->getSum());
    }

}
