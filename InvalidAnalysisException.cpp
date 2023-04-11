#include "InvalidAnalysisException.h"
#include<string>
using namespace std;
string InvalidAnalysisException::what() {

    string ret = "Matrix not invertible";
    return ret;
}