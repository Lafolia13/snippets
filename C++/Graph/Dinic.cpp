struct dinic {
	struct edge {
		llong to;
		llong cap;
		llong rev;

		edge(llong to, llong cap, llong rev) :
			to(to),
			cap(cap),
			rev(rev)
		{}
	};

	vector<vector<edge> > edges;
	vector<llong> level;
	vector<llong> iter;

	dinic() {}
	dinic(int N) :
		edges(N+1),
		level(N+1),
		iter(N+1)
	{}

	void add_edge(llong from, llong to, llong cap) {
		edges[from].push_back(edge(to, cap, edges[to].size()));
		edges[to].push_back(edge(from, 0, edges[from].size()-1));
	}

	void bfs(llong s) {
		fill_n(level.begin(), level.size(), -1);
		level[s] = 0;
		queue<llong> q;
		q.push(s);
		while (q.size()) {
			llong now = q.front();
			q.pop();
			for (int i = 0; i < edges[now].size(); i++) {
				edge next = edges[now][i];
				if (next.cap > 0 && level[next.to] == -1)
					level[next.to] = level[now] + 1, q.push(next.to);
			}
		}
	}

	llong dfs(llong s, llong t, llong flow) {
		if(s == t) return flow;

		while(iter[s] < edges[s].size()) {
			edge &next = edges[s][iter[s]];
			if (next.cap > 0 && level[next.to] > level[s]) {
				llong d = dfs(next.to, t, min(flow, next.cap));
				if (d > 0) {
					next.cap -= d;
					edges[next.to][next.rev].cap += d;
					return d;
				}
			}

			iter[s]++;
		}

		return 0;
	}

	llong max_flow(llong s, llong t) {
		llong ret = 0;
		while (true) {
			bfs(s);
			if (level[t] < 0) return ret;
			fill_n(iter.begin(), iter.size(), 0);
			llong f;
			while (f = dfs(s,t,inf), f > 0) ret += f;
		}
	}
};
