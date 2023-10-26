#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int main() {

    setlocale(LC_ALL, "ru");
    float counter = 0;
    mutex counterMutex;
    thread thread1([&]() {
        for (int i = 0; i < 100; ++i) {
            counterMutex.lock();
            counter += 2;
            counterMutex.unlock();
        }
        });

    thread thread2([&]() {
        for (int i = 0; i < 100; ++i) {
            counterMutex.lock();
            counter -= 1;
            counterMutex.unlock();
        }
        });

    thread thread3([&]() {
        for (int i = 0; i < 10; ++i) {
            counterMutex.lock();
            counter *= 1.3;
            counterMutex.unlock();
        }
        });

    thread1.join();
    thread2.join();
    thread3.join();

    cout << "Значение переменной после операций " << counter << endl;

    return 0;
}