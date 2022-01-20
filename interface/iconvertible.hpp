#pragma once
//#include <format>
#include <string>
using namespace std;
namespace interface
{
    class IConvertible
    {
    public:
        virtual string ToString() { return ""; }
    };
}