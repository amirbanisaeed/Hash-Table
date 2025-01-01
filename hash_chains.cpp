#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<string> elems;
    vector<vector<string>> hashTable;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {
        hashTable.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        //  cout << "In The ProcessQuery" << endl;
        if (query.type == "check")
        {
            // use reverse order, because we append strings to the end
            if (hashTable[query.ind].size() == 0)
            {
                std::cout << "\n";
            }
            else
            {
                for (int i = 0; i < hashTable[query.ind].size() - 1; i++)
                {
                    std::cout << hashTable[query.ind][i] << " ";
                }
                std::cout << "\n";
            }
        }
        else
        {
            //vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            size_t hashOfQuery = hash_func(query.s);
            vector<string>::iterator it = std::find(hashTable[hashOfQuery].begin(), hashTable[hashOfQuery].end(), query.s);

            if (query.type == "find")
            {
                //                size_t hashOfQuery = hash_func(query.s);
                //                vector<string>::iterator it = std::find(hashTable[hashOfQuery].begin(), hashTable[hashOfQuery].end(), query.s);
                writeSearchResult(it != hashTable[hashOfQuery].end());
            }

            else if (query.type == "add") {
                //   cout << "Heyyyyy";
   //                size_t hashOfQuery = hash_func(query.s);
                if (it != hashTable[hashOfQuery].end())
                {

                }
                else
                {
                    size_t NewVectorSize = hashTable[hashOfQuery].size() + 1;
                    hashTable[hashOfQuery].resize(NewVectorSize);
                    //  cout << hashTable[hashOfQuery].size()<< endl;
                    hashTable[hashOfQuery].insert(hashTable[hashOfQuery].begin(), query.s);
                    //  cout << hashTable[hashOfQuery][0] << endl;
                    // if (it == elems.end())
                    //   elems.push_back(query.s);
                }

            }
            else if (query.type == "del") {
                size_t hashOfQuery = hash_func(query.s);
                vector<string>::iterator it = std::find(hashTable[hashOfQuery].begin(), hashTable[hashOfQuery].end(), query.s);
                if (it != hashTable[hashOfQuery].end())
                {
                    hashTable[hashOfQuery].erase(it);
                }


            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
