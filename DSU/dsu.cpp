#include<iostream>
#include<vector>
#include<format>
#include<utility>
#include<string>

struct DSU {
  std::vector<int> parent;
  std::vector<int> size;
  int comps;

  // constructor
  DSU(int n) {
    parent.resize(n);
    size.resize(n);
    comps = n;
    for(int i = 0; i < n; i++) {
      parent[i] = i;
      size[i] = 1;
    }
  }

  int find(int x) {
    if (parent[x] != x){
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  bool union_nodes(int u, int v){
    int pu = find(u);
    int pv = find(v);
    // if they already have the same parent
    if (pv == pu) {
      return false;
    }
    
    // ensure that pu has the bigger  value
    // so that we can merge the bigger tree under the smaller one's root
    // to get closer to amortized time complexity
    if (size[pu] < size[pv]) {
      std::swap(pu, pv);
    }

    // update amount of components
    // and update the size's
    comps--;
    size[pu] += size[pv];
    size[pv] = 0;
    parent[pv] = pu;
    return true;
  }
};


void print_dsu(DSU &dsu) {
  for(int &num: dsu.parent){
    std::cout << num << ' ';
  }
  std::cout << '\n';
  for(int &num: dsu.size){
    std::cout << num << ' ';
  }
  std::cout << '\n' << std::format("Components: {}", dsu.comps) << '\n'; 
}

void print_inputs(int n, std::vector<std::pair<int, int>> &edges) {
  std::cout << "Inputs:\n\n" << std::format("N: {}", n) << '\n';
  for (std::pair<int, int> &edge: edges){
    std::string frmt_pair {std::format("{} <-> {}", edge.first, edge.second)};
    std::cout << frmt_pair << '\n';
  }
  std::cout << '\n';
}


int main() {
  int n = 5;
  std::vector<std::pair<int, int>> edges {{0, 1}, {0, 2}, {0, 3}, {1, 4}};
  DSU dsu(n);
  print_inputs(n, edges);
  print_dsu(dsu);

  for(std::pair<int, int> &p: edges) {
    dsu.union_nodes(p.first, p.second);
    print_dsu(dsu);
  }


  return 0;
}
