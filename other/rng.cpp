seed_seq seq {
  (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
  (uint64_t) __builtin_ia32_rdtsc(),
  (uint64_t) (uintptr_t) unique_ptr<char>(new char).get()
};
mt19937 rng(seq);

int rand_int(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}
