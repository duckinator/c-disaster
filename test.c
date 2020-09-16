#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define TypeToId(e) _Generic(e, \
                    char*:      2, \
                    char:       3, \
                    int8_t:     4, \
                    uint8_t:    5, \
                    int16_t:    6, \
                    uint16_t:   7, \
                    int32_t:    8, \
                    uint32_t:   9, \
                    int64_t:   10, \
                    uint64_t:  11, \
                    default:    1)

static int _data[TypeToId((void*)1)]    = {0};
static int _str [TypeToId((char*)1)]    = {0};
static int _chr [TypeToId((char)1)]     = {0};
static int _i8  [TypeToId((int8_t)1)]   = {0};
static int _u8  [TypeToId((uint8_t)1)]  = {0};
static int _i16 [TypeToId((int16_t)1)]  = {0};
static int _u16 [TypeToId((uint16_t)1)] = {0};
static int _i32 [TypeToId((int32_t)1)]  = {0};
static int _u32 [TypeToId((uint32_t)1)] = {0};
static int _i64 [TypeToId((int64_t)1)]  = {0};
static int _u64 [TypeToId((uint64_t)1)] = {0};

#define Value(e) _Generic( (&(e.type)),\
                            int(*)[ 1]: e.as.data,  \
                            int(*)[ 2]: e.as.str,   \
                            int(*)[ 3]: e.as.chr,   \
                            int(*)[ 4]: e.as.i8,    \
                            int(*)[ 5]: e.as.u8,    \
                            int(*)[ 6]: e.as.i16,   \
                            int(*)[ 7]: e.as.u16,   \
                            int(*)[ 8]: e.as.i32,   \
                            int(*)[ 9]: e.as.u32,   \
                            int(*)[10]: e.as.i64,   \
                            int(*)[11]: e.as.u64)

union SourceOfAnxiety {
    void    *data;
    char    *str;
    char     chr;
    int8_t   i8;
    uint8_t  u8;
    int16_t  i16;
    uint16_t u16;
    int32_t  i32;
    uint32_t u32;
    int64_t  i64;
    uint64_t u64;
};

#define Okay(TYPE, DATA) {.as.TYPE=DATA, .is_okay=true, .type={0}}
#define Err(TYPE, DATA)  {.as.TYPE=DATA, .is_okay=false, .type={0}}

struct {union SourceOfAnxiety as;} distress = {.as.chr = 'a'};
#define Either(TYPE) \
    struct { union SourceOfAnxiety as; bool is_okay; int type[TypeToId(distress.as.TYPE)]; }

int main()
{
    //struct {union SourceOfAnxiety as; _Bool is_okay; int type[8];} a = { .as.i32=1234, .is_okay=1, .type={0}};
    Either(i32) a = Okay(i32, 1234);
    printf("a == %i (okay? %s)\n", Value(a), a.is_okay ? "yes" : "no");

    Either(chr) b = Err(chr, 'x');
    printf("b == %c (okay? %s)\n", Value(b), b.is_okay ? "yes" : "no");

    return 0;
}
