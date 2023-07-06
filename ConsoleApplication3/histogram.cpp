#include "histogram.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
void find_minmax(vector<double> numbers, double& min, double& max) {
    max = *max_element(numbers.begin(), numbers.end());
    min = *min_element(numbers.begin(), numbers.end());
}
