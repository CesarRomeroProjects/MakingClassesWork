#include <vector>
#include <unordered_map>
#include "GenericQueue.hpp"
#include "matchtas.hpp"

// You may want to #include others that we have talked about
#include <fstream>

int main()
{
    std::ifstream profsin{"test3_classprefs.txt"};
    std::ifstream tasin{"test3_taprefs.txt"};
    std::unordered_map<unsigned, unsigned> matching;
    constexpr unsigned NUM_TAS_and_CLASSES{3};

    matchTAs( NUM_TAS_and_CLASSES, tasin, profsin, matching );
    return 0;
}

