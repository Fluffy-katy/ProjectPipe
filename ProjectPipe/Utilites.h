#pragma once
#include <iostream> // Input-output stream
#include <fstream> // File stream
#include <string> 
#include <vector>
#include <unordered_map>
#include <unordered_set>

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

inline std::string input_string()
{
    std::cin.ignore(1000000, '\n');
    std::cin >> std::ws;
    std::string str;
    std::getline(std::cin, str);

    std::cerr << str << std::endl;
    return str;
}

// Function to check the value

template <typename T>
T GetCorrectNumber(T min, T max)
{
    T x;
    while ((std::cin >> x).fail()
        || std::cin.peek() != '\n'
        || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "\nInvalid input!" << std::endl;
        std::cout << "Enter a number between " << min << " and " << max << std::endl;
    }
    std::cerr << x << std::endl;
    return x;
}

inline int SwitchNumber(std::vector<int>& conteiner)
{
    for (int i = 0; i < conteiner.size(); i++)
    {
        std::cout << i + 1 << ". " << conteiner[i] << std::endl;
    }
    int answer = GetCorrectNumber(1, (int)conteiner.size());
    return conteiner[answer - 1];
}


// Used for convenient selection in console
template <typename T>
std::unordered_set<int> GetKeys(const std::unordered_map<int, T>& container)
{
    std::unordered_set<int> keys;
    for (auto& [id, element] : container)
        keys.insert(id);
    return keys;
}