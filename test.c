#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int _data[ 1] = {0,};
int _str [ 2] = {0,};
int _chr [ 3] = {0,};
int _i8  [ 4] = {0,};
int _u8  [ 5] = {0,};
int _i16 [ 6] = {0,};
int _u16 [ 7] = {0,};
int _i32 [ 8] = {0,};
int _u32 [ 9] = {0,};
int _i64 [10] = {0,};
int _u64 [11] = {0,};

#define Value(e) _Generic(((int(*)[sizeof(e.typeary)])(e.typeary)),  \
                            int(*)[ 1]: e.as.data, \
                            int(*)[ 2]: e.as.str,  \
                            int(*)[ 3]: e.as.chr,  \
                            int(*)[ 4]: e.as.i8,   \
                            int(*)[ 5]: e.as.u8,   \
                            int(*)[ 6]: e.as.i16,  \
                            int(*)[ 7]: e.as.u16,  \
                            int(*)[ 8]: e.as.i32,  \
                            int(*)[ 9]: e.as.u32,  \
                            int(*)[10]: e.as.i64,  \
                            int(*)[11]: e.as.u64)

#define Okay(TYPE, DATA) { .as.TYPE = DATA, .typeary = &_##TYPE, .is_okay = true  }
#define Err(TYPE, DATA)  { .as.TYPE = DATA, .typeary = &_##TYPE, .is_okay = false }

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

typedef struct either_s {
    union SourceOfAnxiety as;
    int (*typeary)[];
    bool is_okay;
} Either;

int main()
{
    Either a = Okay(i32, 1234);
    printf("a == %i (okay? %s)\n", a.as.i32, a.is_okay ? "yes" : "no");
    //printf("Value = %i\n", Value(a));

    Either e = Okay(i32, 1234);
    printf("e == %i\n", Value(e));

    Either b = Err(i32, -1);
    printf("b == %i   (okay? %s)\n", b.as.i32, b.is_okay ? "yes" : "no");

    return 0;
}
