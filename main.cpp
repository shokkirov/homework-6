#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int num {};

template <typename T>
void consoleInput (T& var) {
    std::cin >> var;
}

template <typename T>
T consoleInput () {
    T a {};
    std::cin >> a;
    return a;
}

std::string getConsoleLineString () {
    std::string w = "";
    std::getline(std::cin, w);
    return w;
}

void getConsoleLineString (std::string& w) {
    std::getline(std::cin, w);
}

std::vector<int> splitStrIntoNum(const std::string& s, std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<int> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (std::stoi(token));
    }

    res.push_back (std::stoi(s.substr (pos_start)));
    return res;
}

namespace Problem1 {
    void execute () {
        int num {};
        consoleInput(::num);
        consoleInput(num);

        std::cout << (::num % num) << std::endl;
    }
}

namespace Problem2 {
    int checkHowManyTimes (std::string& str, char c) {
        int appears = 0;

        for (char& i : str) {
            if (i == c) ++appears;
        }

        return appears;
    }

    enum STR_STATUS { NOT_FOUND = -1, SAME = 0, STR_1 = 1, STR_2 = 2 };

    int func (std::string& v1, std::string& v2, char c, STR_STATUS* status) {
        int appears1 = checkHowManyTimes(v1, c);
        int appears2 = checkHowManyTimes(v2, c);

        if (appears2 == 0 && appears1 == 0) {
            *status = NOT_FOUND;
            return 0;
        } else if (appears2 == appears1) {
            *status = SAME;
            return appears1;
        } else if (appears1 > appears2) {
            *status = STR_1;
            return appears1;
        } else {
            *status = STR_2;
            return appears2;
        }
    }

    void execute () {
        std::string a = consoleInput<std::string>();
        std::string b = consoleInput<std::string>();
        char c = consoleInput<char>();

        STR_STATUS status; /// aaaaabbb

       int appearances = func(a, b, c, &status);

        switch (status) {
            case SAME:
                std::cout << "The string ”" << a << "” and ”" << b << "” contain the character ’" << c << "’ same times     (" << appearances << " times).";
                break;
            case NOT_FOUND:
                std::cout << "Not found" << std::endl;
                break;
            case STR_1:
            case STR_2:
                std::cout << "The string ”" << ( status == STR_1 ? a : b ) << "” contains the character ’" << c << "’ most times (" << appearances << " times).";
                break;
            default:
                break;
        }
        std::cout << '\n';
    }
}

namespace Problem3 {
    void func (std::string& str, int& numDigits) {
        for (int i = 0; i < str.size(); ++i) {
            if (isdigit(str[i])) {
                ++numDigits;
            } else if (isupper(str[i])) {
                str[i] = tolower(str[i]);
            } else if (islower(str[i])) {
                str[i] = toupper(str[i]);
            }
        }
    }

    void execute () {
        std::string str = "";

        while (str[str.size() - 1] != 'x') {
            consoleInput(str);
        }

        int numDigits {};

        func(str, numDigits);

        std::cout << str << " contains " << numDigits << " digits\n";
    }
}

namespace Problem4 {
    template <typename T>
    T func(T a, T b, T c) {
        return std::max(std::max(a + b, b + c), a + c);
    }

    template <typename T>
    void func(std::vector<T> arr, T& min, T& max) {
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] > max) max = arr[i];
            if (arr[i] < min) min = arr[i];
        }
    }

    void execute () {
        int channel = consoleInput<int>();

        if (channel == 1) {
            int a = consoleInput<int>();
            int b = consoleInput<int>();
            int c = consoleInput<int>();
            std::cout << func(a, b, c) << std::endl;
        } else {
            std::cin.ignore(256, '\n');
            std::string a = "";
            getConsoleLineString(a);
            std::string del = " ";
            std::vector<int> nums = splitStrIntoNum(a, del);
            int min { nums[0] };
            int max { nums[0] };
            func(nums, min, max);
            std::cout << "Min: " << min << " Max: " << max << std::endl;
        }
    }
}

namespace Problem5 {
    template <typename T>
    T& func (T& val1, T& val2) {
        T tmp = val1;
        val1 = val2;
        val2 = tmp;

        return (val1 >= val2 ? val1 : val2);
    }

    template <typename T>
    void func (std::vector<T>& val1, std::vector<T>& val2) {
        for (int i = 0; i < val1.size(); ++i) {
            func(val1[i], val2[i]);
        }
    }

    void execute () {
        std::string str = "";
        getConsoleLineString(str);
        std::string del = " ";
        std::vector<int> nums = splitStrIntoNum(str, del);
        if (nums.size() == 2) {
            std::cout << func(nums[0], nums[1]) << std::endl;
        } else {
            getConsoleLineString(str);
            std::vector<int> nums2 = splitStrIntoNum(str, del);
            func(nums, nums2);
            for (int& a : nums) {
                std::cout << a << ' ';
            }
            std::cout << '\n';
            for (int& a : nums2) {
                std::cout << a << ' ';
            }
            std::cout << '\n';
        }
    }
}

int main () {

    Problem1::execute();
    Problem2::execute();
    Problem3::execute();
    Problem4::execute();
    Problem5::execute();
    return 0;
}
