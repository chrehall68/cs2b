#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

int main() {
    // basic example
    auto start = chrono::system_clock::now();
    this_thread::sleep_for(chrono::seconds(1));
    auto end = chrono::system_clock::now();
    cout << "duration was " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;

    // example of timing push backs
    vector<int> myvector;
    for (int i = 0; i < 125; ++i) {
        start = chrono::high_resolution_clock::now();  // high res is more precise
        myvector.push_back(i);
        end = chrono::high_resolution_clock::now();
        cout << "duration in nanoseconds was " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    }
}