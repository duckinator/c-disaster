#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef int _data[1];
typedef int _str[2];
typedef int _chr[3];
typedef int _i8[4];
typedef int _u8[5];
typedef int _i16[6];
typedef int _u16[7];
typedef int _i32[8];
typedef int _u32[9];
typedef int _i64[10];
typedef int _u64[11];

_u64 sadness = {0,};

#define Value(e) _Generic(  ((int(*)[sizeof(e.type) / sizeof(int)])&sadness),\
                            int(*)[ 1]: either_getfn_data,  \
                            int(*)[ 2]: either_getfn_str,   \
                            int(*)[ 3]: either_getfn_chr,   \
                            int(*)[ 4]: either_getfn_i8,    \
                            int(*)[ 5]: either_getfn_u8,    \
                            int(*)[ 6]: either_getfn_i16,   \
                            int(*)[ 7]: either_getfn_u16,   \
                            int(*)[ 8]: either_getfn_i32,   \
                            int(*)[ 9]: either_getfn_u32,   \
                            int(*)[10]: either_getfn_i64,   \
                            int(*)[11]: either_getfn_u64)(e)

#define Okay(TYPE, DATA) {.as.TYPE = DATA, .type = (_##TYPE*)&sadness, .is_okay = true}
#define Err(TYPE, DATA)  {.as.TYPE = DATA, .type = (_##TYPE*)&sadness, .is_okay = false}

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
    int (*type)[];
    bool is_okay;
} Either;

void    *either_getfn_data(Either e) { printf("data\n"); return e.as.data; }
char    *either_getfn_str (Either e) { printf("str\n"); return e.as.str;  }
char     either_getfn_chr (Either e) { printf("chr\n"); return e.as.chr;  }
int8_t   either_getfn_i8  (Either e) { printf("i8\n");  return e.as.i8;   }
uint8_t  either_getfn_u8  (Either e) { printf("u8\n");  return e.as.u8;   }
int16_t  either_getfn_i16 (Either e) { printf("i16\n"); return e.as.i16;  }
uint16_t either_getfn_u16 (Either e) { printf("u16\n"); return e.as.u16;  }
int32_t  either_getfn_i32 (Either e) { printf("i32\n"); return e.as.i32;  }
uint32_t either_getfn_u32 (Either e) { printf("u32\n"); return e.as.u32;  }
int64_t  either_getfn_i64 (Either e) { printf("i64\n"); return e.as.i64;  }
uint64_t either_getfn_u64 (Either e) { printf("u64\n"); return e.as.u64;  }

int main()
{
    Either a = Okay(i32, 1234);
    printf("a == %i (okay? %s)\n", a.as.i32, a.is_okay ? "yes" : "no");
    printf("Value = %i\n", Value(a));

    Either e = Okay(str, "awoo");
    printf("e.type = %lu\n", sizeof(e.type));
    printf("e == %s\n", Value(e));

    Either b = Err(i32, -1);
    printf("b == %i   (okay? %s)\n", b.as.i32, b.is_okay ? "yes" : "no");

    return 0;
}
