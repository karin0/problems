void c_() { std::cerr << "\033[39;0m" << std::endl; }
template <typename T, typename... Args>
void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
#define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
#define ccd(args...) std::cerr << "\033[32;1m", c_(args)
#define ccf(args...) fprintf(stderr, args)
#define crep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
