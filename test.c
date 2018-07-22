#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int _0[1] = {0,};
int _1[2] = {0,};
int _2[3] = {0,};
int _3[4] = {0,};
int _4[5] = {0,};
int _5[6] = {0,};
int _6[7] = {0,};
int _7[8] = {0,};
int _8[9] = {0,};
int _9[10] = {0,};
int _10[11] = {0,};

#define EitherFn(TYPE) _Generic((&_##TYPE),  \
                                int(*)[ 1]: either_getfn_data, \
                                int(*)[ 2]: either_getfn_str,  \
                                int(*)[ 3]: either_getfn_chr,  \
                                int(*)[ 4]: either_getfn_i8,   \
                                int(*)[ 5]: either_getfn_u8,   \
                                int(*)[ 6]: either_getfn_i16,  \
                                int(*)[ 7]: either_getfn_u16,  \
                                int(*)[ 8]: either_getfn_i32,  \
                                int(*)[ 9]: either_getfn_u32,  \
                                int(*)[10]: either_getfn_i64,  \
                                int(*)[11]: either_getfn_u64)

#define Okay(TYPE, DATA) { .as.TYPE = DATA, .type = _##TYPE, .is_okay = true  }
#define Err(TYPE, DATA)  { .as.TYPE = DATA, .type = _##TYPE, .is_okay = false }
#define Value(TYPE, e) ((e).as.TYPE)

enum SourceOfAnxietyType {
    _data,
    _str,
    _chr,
    _i8,
    _u8,
    _i16,
    _u16,
    _i32,
    _u32,
    _i64,
    _u64,
};

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
    enum SourceOfAnxietyType type;
    bool is_okay;
} Either;

void    *either_getfn_data(Either e) { return e.as.data; }
char    *either_getfn_str (Either e) { return e.as.str;  }
char     either_getfn_chr (Either e) { return e.as.chr;  }
int8_t   either_getfn_i8  (Either e) { return e.as.i8;   }
uint8_t  either_getfn_u8  (Either e) { return e.as.u8;   }
int16_t  either_getfn_i16 (Either e) { return e.as.i16;  }
uint16_t either_getfn_u16 (Either e) { return e.as.u16;  }
int32_t  either_getfn_i32 (Either e) { printf("i32!\n"); return e.as.i32;  }
uint32_t either_getfn_u32 (Either e) { return e.as.u32;  }
int64_t  either_getfn_i64 (Either e) { return e.as.i64;  }
uint64_t either_getfn_u64 (Either e) { printf("u64!\n"); return e.as.u64;  }

int main()
{
    Either a = Okay(i32, 1234);
    printf("a == %i (okay? %s)\n", a.as.i32, a.is_okay ? "yes" : "no");
    //printf("Value = %i\n", Value(a));

    Either e = Okay(i32, 1234);
    printf("e == %i\n", EitherFn(7)(e));

    Either b = Err(i32, -1);
    printf("b == %i   (okay? %s)\n", b.as.i32, b.is_okay ? "yes" : "no");

    return 0;
}
