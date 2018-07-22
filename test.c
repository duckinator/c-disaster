#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define Value(e) (   (e.type == _data) ? (void* )e.as.data : \
                    ((e.type == _str ) ? (char* )e.as.str  : \
                    ((e.type == _chr ) ? (char)e.as.chr  : \
                    ((e.type == _i8  ) ? ( int8_t )e.as.i8   : \
                    ((e.type == _u8  ) ? (uint8_t )e.as.u8   : \
                    ((e.type == _i16 ) ? ( int16_t)e.as.i16  : \
                    ((e.type == _u16 ) ? (uint16_t)e.as.u16  : \
                    ((e.type == _i32 ) ? ( int32_t)e.as.i32  : \
                    ((e.type == _u32 ) ? (uint32_t)e.as.u32  : \
                    ((e.type == _i64 ) ? ( int64_t)e.as.i64  : \
                    ((e.type == _u64 ) ? (uint64_t)e.as.u64  : -1 )))))))))))

#define Okay(TYPE, DATA) { .as.TYPE = DATA, .type = _##TYPE, .is_okay = true  }
#define Err(TYPE, DATA)  { .as.TYPE = DATA, .type = _##TYPE, .is_okay = false }

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
    uint64_t *__hack;
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

typedef void *(*eithervoidptr)(Either e);

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
    Either e = Okay(i32, 1234);
    printf("okay? %s\n  a == %i\n", a.is_okay ? "yes" : "no", a.as.i32);
    printf("%i\n", a.type);
    printf("%i\n", _str);
    //printf("Value = %i\n", Value(a));
    e.__hack = (uint64_t*)&e.as.i32;

/*    printf("Value = %i\n", *(
        (e.type == _data && ((void**)  e.__hack)) ||
        (e.type == _str  && ((char**)  e.__hack)) ||
        (e.type == _i32  && ((int32_t*)e.__hack))
    ));*/

    printf("e == ");
    if (e.type == _data) {
        printf("%p\n", *(void**)e.__hack);
    } else if (e.type == _str) {
        printf("%s\n", *(char**)e.__hack);
    } else if (e.type == _i32) {
        printf("%i\n", *((int32_t*)e.__hack));
    } else {
        printf("other\n");
    }


    Either b = Err(i32, -1);
    printf("okay? %s\n  b == %i\n", b.is_okay ? "yes" : "no", b.as.i32);

    return 0;
}
