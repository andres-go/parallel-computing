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

    // use < operator from Adder and choose last
    std::sort(adders.begin(), adders.end());
    Adder* maxAdder = &adders.back();
    std::cout << "Highest Sum" << maxAdder->getId() << ": " << maxAdder->getSum() << std::endl;

}
