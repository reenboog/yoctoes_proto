#ifndef __FUNC_H__
#define __FUNC_H__

#define ARC4RANDOM_MAX 0x100000000

static inline float randInRangef(float low, float high) {
    assert(low <= high);
    return (((float) rand() / ARC4RANDOM_MAX) * (high - low)) + low;
}

std::string stringWithFormat(const char *fmt, ...) {    //todo:: ЛЕША, ПОСМОТРИ НА МЕНЯ!
    char buf[1024];
    sprintf(buf, "");

    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf + strlen(buf), fmt, ap);

    return buf;
}

#endif // __FUNC_H__