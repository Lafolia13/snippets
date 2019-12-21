void simulated_annealing() {
	constexpr double simulate_time = 2800;
	constexpr double start_temp = 100;
	constexpr double end_temp = 10;

	clock_t s = clock(), f;

	int now_score = all_calculation();
	int max_score = now_score;
	int changed_score;
	int diff_score;
	num before;
	double temp;
	double probability;
	bool force;

	while (f = clock(), f - s < simulate_time) {
		temp = start_temp + (end_temp - start_temp) * (f - s) / simulate_time;
		for (int &&i = 0; i < 100; ++i) {

			static pos change_pos;
			static num change_num;
			do {
				change_pos = xor128();
				change_num = xor128();
			} while (!check(change_pos, change_num));
			before = state[change_pos];

			diff_score = calculation(change_pos);
			state[change_pos] = change_num;
			changed_score = now_score - diff_score + calculation_diff(change_pos);

			probability = exp((changed_score - now_score*1.0) / temp);
			force = probability > (xor128() % 1000 * 1.0 / 1000.0);
			if (changed_score > now_score || force) {
				now_score = changed_score;
				if (now_score > max_score) {
					max_score = now_score;
					ret_state = now_state;
				}
			} else {
				state[change_pos] = before_num;
			}
		}
	}

	return;
}
