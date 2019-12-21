template<typename T>
struct segment_tree {
	const int n;
	const T op;
	vector<T> node;
	function<T(T,T)> fnc;

	segment_tree(int n, T init, function<T(T,T)> fnc, T op = T()) :
		n(n),
		op(op),
		node(n*2, init),
		fnc(fnc)
	{}
	segment_tree(vector<T> v, function<T(T,T)> f, T o = T()) {
		n = v.size();
		op = o;
		fnc = f;
		node.resize(n*2);

		for (int i = 0; i < n; i++)
			node[i+n] = v[i];
		for (int i = n-1; i >= 1; i--)
			node[i] = fnc(node[2*i], node[2*i+1]);
	}

	void set(int x, T val) {
		x += n;
		node[x] = val;
		while (x >>= 1)
			node[x] = fnc(node[x*2], node[x*2 + 1]);
	}

	void update(int x, T val) {
		x += n;
		node[x] = fnc(node[x], val);
		while (x >>= 1)
			node[x] = fnc(node[x*2], node[x*2 + 1]);
	}

	T get(int x, int y) {
		T val = op;
		for (x += n, y += n-1; x <= y; x >>= 1, y >>= 1) {
			if (x&1)
				val = fnc(val, node[x++]);
			if (y&1^1)
				val = fnc(val, node[y--]);
		}

		return val;
	}
};
