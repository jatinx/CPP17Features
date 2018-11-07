#include <iostream>
#include <memory> // <- unique pointer
#include <chrono> // <- time related shit
#include <tuple> // <- more than 2 piece together
#include <type_traits>
#include <vector>
#include <string>
#include <map>

using namespace std::chrono_literals;
//Automatic return type decuction
auto Area(int a, int b) { return a*b; }

//constexpr functions - at compile time
//in C++11 no if statements in these, C++14 .. :)
constexpr int DoSomething(int x) { return x * (x+1); }

//Variable template
template <typename T>
constexpr T pi = T(3.141231231232);

//deprecated func - warning on usage
[[deprecated("Use something else")]] int depfunc() { return 0; } //raises warning on func usage

//constexpr wala if
//if no constexpr in if, it doesnt compile as int needs to check for both if and else
template<typename T>
auto length(T const& value) {
        if constexpr (std::is_integral<T>::value) {
                return value;
        } else {
                return value.length();
        }
}
int main ()
{
        //Digit Sep
        {
                long x = 10'00'000; 
                std::cout<< x << '\n';
        }

        //binary literals
        {
                auto x = 0b0010'0101;
                x = 0B0001010110010011;
                std::cout<< x << '\n';
        }

        //constexpr - computation at compile time - performance
        {
                constexpr int x = DoSomething(100);
                std::cout<< x << '\n';

                static_assert(x == 10100); //Eval compile time
        }

        //Variable templates
        {
                std::cout<< pi<int> << '\n';
        }

        //dep func
        {
                auto x = depfunc();
        }

        //pointers raw
        {
                int n{64}; //fucking declaration now can look like this
                int x{};
                std::cout<<x<<'\n';
                //make unique pointer, calls destrutor when goes out of scope
                auto px = std::make_unique<int>(0);
                std::cout<<*px<<'\n';
                //unique ptr can be copied, only can be moved std::move
        }

        //unit of measurement
        {
                std::chrono::seconds s{}; //0 init
                std::chrono::seconds s1; //garbage
                auto s2 = 10s; //10 seconds
                std::cout << (s2 > s1)<<'\n';
        }

        //tuple
        {
                std::tuple<int, int, int> t;
                t = std::make_tuple(1,2,3);
                std::cout<<std::get<0>(t)<<'\n';
        }

        //lambdas bitch
        {
                //polymorphic lambdas
                std::cout<<"\nLambda OP::";
                auto y = [](auto x) { return x+2; };
                std::cout<<y(2)<<'\t';

                // [] <- capturelist of lambda
                // [x, y] <- pass by value
                // [&x, &y] <- capture by reference
                // [value = 64] <- init capture
                // [uniqptr{std::move(x)}]
                // [=] <- capture all

                auto z = [&y,xx = y(2)](){ return y(xx); };
                std::cout<<z()<<'\n';
                
        }

        {
                //nested namespace allowed
                //eg: namespace lol::jabe::bhadve { ... }
        }

        //init in if - also in switch
        {
                int x = 2;
                
                if(auto y = x+2; y<=5) {
                        std::cout<<y<<'\n';
                } else {
                        std::cout<<y+1<<'\n';
                }
        }

        //constexpr wala if - same compile time shit
        {
                int x = 0;
                std::string s{"lalala"};
                std::cout<<length(x)<<" "<<length(s)<<'\n';
        }

        {
                std::map<int,int> m;
                auto x = m.insert({1,1});
                std::cout<<" "<<x.second<<'\n';
                auto [l,n] = m.insert({1,1});
                std::cout<<" "<<n<<'\n';
        }
        return 0;
}

