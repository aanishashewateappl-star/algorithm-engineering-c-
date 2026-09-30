#include <iostream> // for printing
#include <vector>  // we need dynamic storage
#include <numeric> // for std::iota 
#include <cassert> // for assert
#include <random>  // for random number generation - in code we have used std::mt19937 and std::uniform_int_distribution
#include <chrono>  // for timing

using namespace std;

class UnionFind {

    private:
        std:: vector<int> parent;
        std:: vector<int> rank;

    public: 
        explicit UnionFind(int n) : parent(n), rank(n, 0) {
            iota(parent.begin(), parent.end(), 0); //parent[i] = i for all i , ie everyone starts as their own group
        }
        
        int find(int x) {
            if (parent[x] != x) {
                // return find(parent[x]); // no compression — just walk up, don't reattach
                parent[x] = find(parent[x]); // path compression - every node visited along the way gets directly reattached to the root
            }
            return parent[x];
        }

        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if(rootX == rootY) return; // already in the same group

            // parent[rootY] = rootX; // always attach y's root under x's root, no rank check
            
            if(rank[rootX] < rank[rootY]) swap (rootX, rootY); // make sure rootX is always the deeper/taller tree
            parent[rootY] = rootX;
            if(rank[rootX] == rank[rootY]) rank[rootX]++; // if they were the same depth, the new tree is now deeper and it is incremented by 1
        }

        bool connected(int x, int y) { // check if two nodes are int the same group
            return find(x) == find(y);
        }

};

// manual correctness check
void run_test() {
    UnionFind uf(10);

    assert(!uf.connected(0,1)); // if we don't invert from False to True, then the assert will fail and give assertion error
    uf.unite(0,1);
    assert(uf.connected(0,1)); // now they should be connected

    uf.unite(1,2);
    assert(uf.connected(0,2)); //checking transitivity, as 0 was connected to 1 and 1 was connected to 2

    uf.unite(3,4);
    uf.unite(4,5);

    assert(uf.connected(3,5)); //checking transitivity
    assert(!uf.connected(0,3)); //checking that 0 and 3 are connected or not as they belong to different groups

    cout<< "All tests passed!" <<endl;
}

// timing benchmark

void benchmark() {
    int n = 1'000'000; // 1 million
    UnionFind uf(n);

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, n - 1);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        uf.unite(dist(rng), dist(rng));
    }
    auto end = std::chrono::high_resolution_clock::now();

    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "1M unites took " << ms << " ms\n";
}

int main() {
    run_test();
    benchmark();
    return 0;
}