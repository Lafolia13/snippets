struct data {
	llong place;
	llong cost;

	data() {};
	data(llong place, llong cost) :
		place(place),
		cost(cost)
	{}

	bool operator<(const data &ri) const {
		return cost < ri.cost;
	}
	bool operator<=(const data &ri) const {
		return cost <= ri.cost;
	}
	bool operator>(const data &ri) const {
		return cost > ri.cost;
	}
};

vector<vector<data> > edges;

vector<data> dijkstra(int start) {
	priority_queue<data, vector<data>, greater<data> > que;
	vector<data> dis(edges.size(), data(-1, inf));
	dis[start] = data(start, 0);

	que.push(dis[start]);
	while (que.size()) {
		data now = que.top();
		que.pop();
		if (dis[now.place] < now) continue;

		for (auto &edge: edges[now.place]) {
			data next(edge.place, now.cost + edge.cost);
			if(dis[next.place] <= next) continue;
			dis[next.place] = next;
			que.push(next);
		}
	}

	return dis;
}
