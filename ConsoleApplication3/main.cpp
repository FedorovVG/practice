#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "histogram.h"



using namespace std;

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
//<rect x = '0' y = '0' width = '100' height = '200' / >: прямоугольник 100×200 с верхним левым углом
// в точке(0, 0).

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black"){
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "' />" << endl;
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" << endl;
}

void show_histogram_svg(vector<int>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    auto BLOCK_WIDTH = 0;

    cerr << "Enter the width of one block (not less than 3px and not more than 30px): ";
    cin >> BLOCK_WIDTH;
    while(BLOCK_WIDTH < 3 || BLOCK_WIDTH > 30){
        cerr << "Incorrect data entered, please re-enter: ";
        cin >> BLOCK_WIDTH;
    }

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "blue");
        top += BIN_HEIGHT;
    }
    svg_end();
}

void print_array(vector<int> arr) {
    double max = *max_element(arr.begin(), arr.end());
    double koeff = 1;
    if (max > 76) {
        koeff = 76.0 / max;
    }
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != 0) {
            string str = std::string(arr[i], '*');
            str = std::string((int)(arr[i] * koeff), '*');
            if (i != 0 && i != arr.size() - 1 && arr[i - 1] == arr[i + 1] && arr[i - 1] < arr[i] && arr[i - 1] != 0) {
                str[arr[i - 1] * koeff - 1] = 'N';
            }
            else {
                if ((i != 0) && (arr[i] > arr[i - 1]) && arr[i - 1] != 0) {
                    str[arr[i - 1] * koeff - 1] = '^';
                }
                if ((i != arr.size() - 1) && (arr[i + 1] < arr[i]) && arr[i + 1] != 0) {
                    str[arr[i] * koeff - 1] = 'v';
                }
            }
            cout << setw(3) << arr[i] << "|" << str << endl;
        }
        else {
            cout << setw(4) << "0|" << endl;
        }

    }
}

vector<int> basket_sorting(vector<double> array_of_numbers, int count_of_bins) {

    double min, max;
    find_minmax(array_of_numbers, min, max);

    vector<int> array_of_bins(count_of_bins);

    double bin_size = (max - min) / array_of_bins.size();
    for (int i = 0; i < array_of_numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < array_of_bins.size() - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            double a = array_of_numbers[i];
            if ((lo <= array_of_numbers[i]) && (array_of_numbers[i] < hi)) {
                array_of_bins[j]++;
                found = true;
            }
        }
        if (!found) {
            array_of_bins[array_of_bins.size() - 1]++;
        }
    }
    return array_of_bins;
}

vector<double> input_numbers(int count) {
    vector<double> numbers(count);
    for (size_t i = 0; i < count; i++) {
        cin >> numbers[i];
    }
    return numbers;
}

int main()
{
    setlocale(LC_ALL, "ru");
    int count_of_numbers;
    cin >> count_of_numbers;

    const auto array_of_numbers = input_numbers(count_of_numbers);

    int count_of_bins;
    cin >> count_of_bins;
    vector<int> array_of_bins = basket_sorting(array_of_numbers, count_of_bins);

    //print_array(array_of_bins);
    show_histogram_svg(array_of_bins);
}
