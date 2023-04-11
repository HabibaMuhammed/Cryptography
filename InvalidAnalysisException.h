#include <exception>
#include<string>
using namespace std;
class InvalidAnalysisException :public _exception
{
public:string what();
};
