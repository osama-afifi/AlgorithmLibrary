#include <vector>
using namespace std;

class BIT {
    private:
    int n;
    vector<int> A;
    public:
    BIT() {
        n=0;
    }
    BIT(int n) {
        this->n=n;
        A.assign(n+10,0);
    }
    void update(int x, int v) {
        if (x<1 || x>n) return;
        for (;x<=n;x+=x&-x) A[x]+=v;
    }
    int get(int x) const {
        if (x<1 || x>n) return (0);
        int ret=0;
        for (;x>=1;x&=x-1) ret+=A[x];
        return (ret);
    }
};