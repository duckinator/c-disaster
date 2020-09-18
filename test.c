//usr/bin/env clang -S -emit-llvm $0 -o- | lli; exit $?

#include <stdio.h>

#define Result(TYPE) struct { TYPE value; int is_ok; int is_err; }
#define Ok(VALUE) {.value=VALUE, .is_ok=1, .is_err=0}
#define Err(VALUE)  {.value=VALUE, .is_ok=0, .is_err=1}
#define Value(VALUE) (VALUE.value)

int main()
{
    Result(int) a = Ok(1234);
    printf("a == %i (okay? %s; error? %s)\n", Value(a),
            a.is_ok ? "yes" : "no",
            a.is_err? "yes": "no");

    Result(char) b = Err('x');
    printf("b == %c (okay? %s; error? %s)\n", Value(b),
            b.is_ok ? "yes" : "no",
            b.is_err? "yes" : "no");

    return 0;
}
