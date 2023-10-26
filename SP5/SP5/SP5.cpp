#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

int main() 
{
    setlocale(LC_ALL, "ru");

    atomic<float> counter(0);
    thread thread1([&]() {
        for (int i = 0; i < 100; ++i) {
            counter.store(counter.load() + 2);;
        }
        });

    thread thread2([&]() {
        for (int i = 0; i < 100; ++i) {
            counter.store(counter.load() - 1.0);
        }
        });

    thread thread3([&]() {
        for (int i = 0; i < 10; ++i) {
            counter.store(counter.load() * 1.3);
        }
        });

    thread1.join();
    thread2.join();
    thread3.join();

    cout << "Значение переменной после операций " << counter.load() << endl;

    return 0;
}
