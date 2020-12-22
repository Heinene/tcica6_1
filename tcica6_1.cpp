#include <iostream>
#include<iomanip>
#include <map>
#include <vector>
#include <algorithm>

struct gr {
public:
    int n;
    std::map<gr, int> start;
    std::map<gr, int> finish;

    gr(const int& n) : n(n) {}
    bool nu(const gr& n);
    int pol(const gr& n);
    friend bool operator<(const gr& lev, const gr& pra)
    {
        return lev.n < pra.n;
    }

};
int gr::pol(const gr& n)
{
    for (const auto& i : finish) {
        if (i.first.n == n.n) return i.second;
    }
    return 0;
}

void ris(gr& lev, gr& pra, int w) {
    lev.finish.insert(std::make_pair(pra, w));
    pra.start.insert(std::make_pair(lev, w));
}

void print(const std::vector<std::vector<int>>& mat) {
    for (const auto& i : mat) {
        for (const auto& m : i) {
            std::cout << ' ' << std::setw(3) << m << std::setw(1) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int FloydAlgorithm(std::vector<gr>& gr) {
    int inf = 100;
    std::vector<std::vector<int>> mat(gr.size());
    for (auto& i : mat) {
        i.resize(gr.size());
    }
    for (int i = 0; i < gr.size(); ++i) {
        for (int j = 0; j < gr.size(); ++j) {
            if (i == j) {
                mat[i][j] = 0;
            }
            else if (gr[i].nu(gr[j])) {
                mat[i][j] = gr[i].pol(gr[j]);
            }
            else {
                mat[i][j] = inf;
            }
        }
    }
    std::cout << "¹0" << std::endl;
    print(mat);

    for (int k = 0; k < gr.size(); ++k) {
        for (int i = 0; i < gr.size(); ++i) {
            for (int j = 0; j < gr.size(); ++j) {
                if (mat[i][k] != inf && mat[k][j] != inf) {
                    mat[i][j] = (mat[i][j] == inf ? mat[i][k] + mat[k][j] :
                        std::max(mat[i][j], mat[i][k] + mat[k][j]));
                }
            }
        }
        std::cout << "¹ " << k + 1<< std::endl;
        print(mat);
    }
    return mat[0][gr.size() - 1];
}

bool gr::nu(const gr& n) {
    for (const auto& i : finish) {
        if (i.first.n == n.n) return true;
    }
    return false;
}



int main()
{
    int a = 3, b = 5, f = 1, c = 2,  h = 3, e = 3, d = 4, g = 4, j = 2, i = 3, k = 5;
    gr n1(1); gr n2(2); gr n3(3); gr n4(4); gr n5(5); gr n6(6); gr n7(7); gr n8(8);
    ris(n1, n2, a); ris(n2, n3, e); ris(n2, n4, b); ris(n3, n4, f); ris(n1, n5, i); ris(n5, n6, j); ris(n4, n6, g); ris(n6, n7, h); ris(n4, n7, c); ris(n6, n8, k); ris(n7, n8, d);
    std::vector<gr> gr = { n1, n2, n3, n4, n5, n6, n7 };
    int l = FloydAlgorithm(gr);
    std::cout << "krit = " << l << std::endl;
    return 0;
}