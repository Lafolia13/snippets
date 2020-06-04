template<typename T, typename U>
inline decltype(auto) get_multivector(T n, U v) noexcept {
	static_assert(is_integral<T>::value, "1st argument is not integer type");
	return vector<U>(forward<T>(n), forward<U>(v));
}

template<typename T, typename... Args>
inline decltype(auto) get_multivector(T n, Args ...args) noexcept {
	static_assert(is_integral<T>::value, "1st argument is not integer type");
	return vector<decltype(get_multivector(forward<Args>(args)...))>(forward<T>(n), get_multivector(forward<Args>(args)...));
}

template<typename T, long long N, typename enable_if<(N > 0), nullptr_t>::type = nullptr>
struct multivector_impl {
	using type = vector<typename multivector_impl<T, N-1>::type>;
};
template<typename T>
struct multivector_impl<T, 1> {
	using type = vector<T>;
};

template<typename T, size_t N>
using multivector = typename multivector_impl<T, N>::type;${0:}
