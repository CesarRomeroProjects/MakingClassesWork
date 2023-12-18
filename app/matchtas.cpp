#include <vector>
#include <unordered_map>
#include "GenericQueue.hpp"
#include "matchtas.hpp"

// You may want to #include others that we have talked about
#include <fstream>
#include <string>
#include <sstream>

void matchTAs(unsigned n, std::istream &taPrefs, std::istream &classPrefs, std::unordered_map<unsigned, unsigned> & assignments)
{
    // A QUEUE OF TAs WHO ARE NOT ASSIGNED TO A CLASS YET.
    GenericQueue<unsigned> unassignedTAs;
    for ( unsigned i{1}; i <= n; i++ )
        unassignedTAs.enqueue(i);
    
    // A VECTOR, EACH REPRESENTING A TA, WHICH HOLDS A QUEUE OF CLASSES THEY HAVEN'T BEEN REJECT FROM YET.
    std::vector < GenericQueue<unsigned> > preferencesOfTheTA(n+1);
    for ( unsigned TA{1}; TA <= n; TA++) {
        unsigned preferredClass;
        for ( unsigned CL{1}; CL <= n; CL++ ) {
            taPrefs >> preferredClass;
            preferencesOfTheTA[TA].enqueue(preferredClass);
        }
    }

    std::string line, word;
    std::stringstream ss;

    // A VECTOR, EACH REPRESENTING A CLASS, WHICH HOLDS AN UNORDERED MAP OF CLASSES TO TAs.
    std::vector< std::unordered_map<unsigned, unsigned> > ClassPreferences(n+1);
    unsigned ctr2{1};
    while( getline(classPrefs, line) ) {
        // PREFERENCE NUMBER: 1 IS HIGHEST, 2 IS SECOND HIGHEST...
        unsigned prefNum{1};
        ss.clear();
        ss << line;
        while ( ss >> word )
        {
            unsigned conv = std::stoul( word );
            ClassPreferences[ctr2][conv] = prefNum;
            prefNum++;
        }
        ctr2++;
    }

    // ALGORITHM
    while ( !unassignedTAs.isEmpty() ) {
        unsigned currentTA{unassignedTAs.front()};
        unassignedTAs.dequeue();
        unsigned preferredTAClass{preferencesOfTheTA[currentTA].front()};
        bool matched{false};

        for ( auto it{assignments.begin()}; it != assignments.end(); it++) {
            if (it->second == preferredTAClass) {
                if (ClassPreferences[preferredTAClass][currentTA] < ClassPreferences[it->second][it->first]) {
                    assignments[currentTA] = it->second;
                    unassignedTAs.enqueue(it->first);
                    assignments.erase(it->first);
                    matched = true;
                    preferencesOfTheTA[currentTA].dequeue();
                    break;
                }
                else if (ClassPreferences[preferredTAClass][currentTA] > ClassPreferences[it->second][it->first]) {
                    preferencesOfTheTA[currentTA].dequeue();
                    unassignedTAs.enqueue(currentTA);
                    matched = true;
                }
            }
        }

        if (!matched) {
            assignments[currentTA] = preferredTAClass; // TENTATIVELY ASSIGNED
            preferencesOfTheTA[currentTA].dequeue();
        }
    }
}