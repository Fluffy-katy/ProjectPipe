#pragma once
#include <iostream> // Input-output stream
#include <fstream> // File stream
#include <string> 
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>

#include <Windows.h> // clear
#include <conio.h>
#include <sstream>
#include <filesystem>
#include <format>

#define ENTER std::cout << std::endl << std::endl;


// Wrapper for cerr
template <typename Stream>
class redirect_stream_wrapper
{
    Stream& stream;
    std::streambuf* const old_buf;
public:
    redirect_stream_wrapper(Stream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_stream_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(Stream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};


inline std::string input_string(std::istream& in)
{
    in.ignore(1000000, '\n');
    in >> std::ws;
    std::string str;
    std::getline(std::cin, str);

    std::cerr << str << std::endl;
    return str;
}



// Function to check the value
template <typename T>
T GetCorrectNumber(std::istream& in, T min, T max)
{
    T x;
    while ((in >> x).fail()
        || in.peek() != '\n'
        || x < min || x > max)
    {
        in.clear();
        in.ignore(10000, '\n');
        std::cout << "\nInvalid input!" << std::endl;
        std::cout << "Enter a number between " << min << " and " << max << std::endl;
    }
    std::cerr << x << std::endl;
    return x;
}



// Used for convenience in console selection
template <typename T>
std::vector<int> GetKeys(const std::unordered_map<int, T>& container)
{
    std::vector<int> keys;
    keys.reserve(container.size());
    int i = 0;
    for (auto& [id, element] : container)
        keys.push_back(id);
    return keys;
}


//---------------Function selection-------------------
using Function = void(*)();

inline void Switch(std::vector<Function> functions)
{
    int size = functions.size();
    int answer = GetCorrectNumber(std::cin, 0, size);
    if (answer)
    {
        functions[answer - 1]();
    }
    return;
}