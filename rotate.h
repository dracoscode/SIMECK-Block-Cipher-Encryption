
/*
 * rotate shift right n-bit on x(a 64-bit block)
 */
static inline uint64_t ror64(uint64_t x, int n) { return x>>n | x<<(64-n); }

/*
 * rotate shift left x by n bits
 */
static inline uint32_t rol32(uint32_t x, int n) { return x<<n | x>>(32-n); }

/*
 * rotate shift right x by n bits
 */
static inline uint32_t ror32(uint32_t x, int n) { return x>>n | x<<(32-n); }

static inline uint16_t ror16(uint16_t x, int n) { return x>>n | x<<(16-n); }

static inline uint16_t rol16(uint16_t x, int n) { return x<<n | x>>(16-n); }

static inline uint24_t ror24(uint24_t x, int n) { return x>>n | x<<(24-n); }

static inline uint24_t rol16(uint24_t x, int n) { return x<<n | x>>(24-n); }
