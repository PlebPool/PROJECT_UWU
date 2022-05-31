#include <iostream>
#include <vector>

int main() {
    std::vector<int> v2{36,37,38};
    std::vector<int> v{1,2,3,4,5};
    v.insert(v.begin(), v2.begin(), v2.end());
//    for (int & i : v2)
//    {
//        v.insert(v.begin(), i);
//    }
    for (int i : v)
    {
        std::cout << i << ",";
    }
    return 0;
}
