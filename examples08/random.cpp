#include <chrono>
#include <iostream>
#include <random>
using namespace std;

int main() {
    // since we provided this one no seed, this will always print the same values
    cout << "static example" << endl;
    default_random_engine myStaticEngine;
    for (int i = 0; i < 5; ++i) {
        cout << myStaticEngine() << endl;
    }
    cout << endl;

    // a true pseudorandom generator that gives different numbers each time you run
    cout << "changing example" << endl;
    default_random_engine myChangingEngine(chrono::system_clock::now().time_since_epoch().count());  // makes a new engine with the time since the epoch
    for (int i = 0; i < 5; ++i) {
        cout << myChangingEngine() << endl;
    }
    cout << endl;

    // an example where you want uniform distribution
    cout << "uniform int distribution" << endl;
    uniform_int_distribution<int> mything(30, 35);  // random int from 0 to 5
    for (int i = 0; i < 5; ++i) {
        cout << mything(myChangingEngine) << endl;
    }
    cout << endl;

    cout << "uniform number distribution" << endl;
    uniform_real_distribution<double> myother(30, 35.1);
    for (int i = 0; i < 5; ++i) {
        cout << myother(myChangingEngine) << endl;
    }
}