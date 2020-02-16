ret_type beam_search() {
	constexpr int beam_width = 100;
	constexpr int beam_depth = 10;

	priority_queue<node, vector<node>, greater<node>> now_que, next_que;

	node root_node = {};
	now_que.push(root_node);
	for (int &&turn = 0; turn < beam_depth; ++turn) {
		while (now_que.size()) {
			const node now_node = now_que.top();
			now_que.pop();

			vector<action> actions = get_action();
			for (auto act: actions) {
				node next_node = transition(now_node, act);
				next_node.get_evaluation();

				next_que.push(next_node);
				if (next_que.size() > beam_width)
					next_que.pop();
			}
		}
		swap(now_que, next_que);
	}

	while (now_que.size() > 1) now_que.pop();

	return now_que.top();
}
