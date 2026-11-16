#ifndef R_COMMON_C_HASH_H
#define R_COMMON_C_HASH_H

#include <stdint.h>

// Thomas Wang's 32-bit integer hash. http://www.concentric.net/~Ttwang/tech/inthash.htm
inline int32_t int32_hash(int32_t inKey)
{
	uint32_t hash = (uint32_t)inKey;
	hash += ~(hash << 15U);
	hash ^= hash >> 10U;
	hash += hash << 3U;
	hash ^= hash >> 6U;
	hash += ~(hash << 11U);
	hash ^= hash >> 16U;
	return (int32_t)hash;
}

// Thomas Wang's 64-bit integer hash.
inline int64_t int64_hash(int64_t inKey)
{
	uint64_t hash = (uint64_t)inKey;
	hash += ~(hash << 32U);
	hash ^= (hash >> 22U);
	hash += ~(hash << 13U);
	hash ^= (hash >> 8U);
	hash += (hash << 3U);
	hash ^= (hash >> 15U);
	hash += ~(hash << 27U);
	hash ^= (hash >> 31U);
	return (int64_t)hash;
}

#endif
