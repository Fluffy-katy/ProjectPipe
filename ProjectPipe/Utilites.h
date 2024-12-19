#pragma once
#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <unordered_set>
#include <unordered_map>


#define ENTER std::cout << std::endl << std::endl;


//cerr
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



//check
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
        std::cout << "Enter a number from " << min << " to " << max << std::endl;
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


// free of choice
template <typename T>
std::unordered_set<int> GetKeys(const std::unordered_map<int, T>& container)
{
    std::unordered_set<int> keys;
    for (auto& [id, element] : container)
        keys.insert(id);
    return keys;
}