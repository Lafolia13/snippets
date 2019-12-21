struct union_find {
	vector<int> par;

	union_find() {}
	union_find(int n) :
		par(n+1, -1)
	{}

	int root(int x) {
		if(par[x] < 0) return x;
		return par[x] = root(par[x]);
	}
	int size(int x) {
		return -par[root(x)];
	}
	bool same(int a, int b) {
		return root(a) == root(b);
	}
	bool marge(int a, int b) {
		a = root(a), b = root(b);
		if(a == b) return false;
		if(par[a] > par[b]) swap(a, b);
		par[a] += par[b];
		par[b] = a;
		return true;
	}
};
