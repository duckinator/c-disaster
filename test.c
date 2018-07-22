#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

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
int32_t  either_getfn_i32 (Either e) { return e.as.i32;  }
uint32_t either_getfn_u32 (Either e) { return e.as.u32;  }
int64_t  either_getfn_i64 (Either e) { return e.as.i64;  }
uint64_t either_getfn_u64 (Either e) { return e.as.u64;  }

struct either_getfns_s {
    void       *(* _0)(Either e);
    char       *(* _1)(Either e);
    char        (* _2)(Either e);
    int8_t      (* _3)(Either e);
    uint8_t     (* _4)(Either e);
    int16_t     (* _5)(Either e);
    uint16_t    (* _6)(Either e);
    int32_t     (* _7)(Either e);
    uint32_t    (* _8)(Either e);
    int64_t     (* _9)(Either e);
    uint64_t    (*_10)(Either e);
};

struct either_getfns_s EitherGetFns = {
    &either_getfn_data,
    &either_getfn_str,
    &either_getfn_chr,
    &either_getfn_i8,
    &either_getfn_u8,
    &either_getfn_i16,
    &either_getfn_u16,
    &either_getfn_i32,
    &either_getfn_u32,
    &either_getfn_i64,
    &either_getfn_u64,
};

int main()
{
    Either a = Okay(i32, 1234);
    printf("a == %i (okay? %s)\n", a.as.i32, a.is_okay ? "yes" : "no");
    //printf("Value = %i\n", Value(a));

    Either e = Okay(i32, 1234);
    printf("Value = %i\n", EitherGetFns._7(e));
    printf("Value = %i\n", Value(i32, e));

    Either b = Err(i32, -1);
    printf("b == %i   (okay? %s)\n", b.as.i32, b.is_okay ? "yes" : "no");

    return 0;
}
