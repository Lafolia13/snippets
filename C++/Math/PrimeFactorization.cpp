std::map<long long, int> prime_factorization(long long n) {
	std::map<long long, int> ret;
	while (n % 2 == 0) {
		ret[2]++;
		n /= 2;
	}
	for (long long i = 3; i*i <= n; i += 2) {
		while (n%i == 0) {
			ret[i]++;
			n /= i;
		}
	}
	if (n != 1) ret[n]++;

	return ret;
}
