map<llong, int> prime_factorization(llong n) {
	map<llong, int> ret;
	while (n % 2 == 0) {
		ret[2]++;
		n /= 2;
	}
	for (llong i = 3; i*i <= n; i += 2) {
		while (n%i == 0) {
			ret[i]++;
			n /= i;
		}
	}
	if (n != 1) ret[n]++;

	return ret;
}
