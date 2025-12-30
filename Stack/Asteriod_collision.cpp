#include <iostream>
#include <vector>
using namespace std;

/*
    Function: asteroidCollision
    ---------------------------
    Simulates asteroid collisions based on directions and sizes.
    Positive values move right, negative values move left.

    Parameters:
        arr - vector of integers representing asteroids

    Returns:
        vector<int> - state of asteroids after all collisions
*/
vector<int> asteroidCollision(vector<int>& arr){
    vector<int> st;  // use vector as a stack

    for(int a : arr){
        if(a > 0) {
            // Right-moving asteroid, push to stack
            st.push_back(a);
        } else {
            // Left-moving asteroid
            while(!st.empty() && st.back() > 0 && st.back() < -a)
                st.pop_back();  // smaller right-moving asteroids explode

            if(!st.empty() && st.back() == -a)
                st.pop_back(); // equal collision, both explode
            else if(st.empty() || st.back() < 0)
                st.push_back(a); // no collision, push left-moving asteroid
        }
    }

    return st;
}

int main() {
    // Test cases
    vector<int> asteroids1 = {5, 10, -5};
    vector<int> asteroids2 = {8, -8};
    vector<int> asteroids3 = {10, 2, -5, -15, 20};

    vector<int> result1 = asteroidCollision(asteroids1);
    vector<int> result2 = asteroidCollision(asteroids2);
    vector<int> result3 = asteroidCollision(asteroids3);

    cout << "Result 1: ";
    for(int a : result1) cout << a << " ";
    cout << endl;

    cout << "Result 2: ";
    for(int a : result2) cout << a << " ";
    cout << endl;

    cout << "Result 3: ";
    for(int a : result3) cout << a << " ";
    cout << endl;

    return 0;
}
