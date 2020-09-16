#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define Either(TYPE) struct { TYPE value; bool is_okay; }
#define Okay(VALUE) {.value=VALUE, .is_okay=true}
#define Err(VALUE)  {.value=VALUE, .is_okay=false}
#define Value(VALUE) (VALUE.value)

int main()
{
    Either(int32_t) a = Okay(1234);
    printf("a == %i (okay? %s)\n", Value(a), a.is_okay ? "yes" : "no");

    Either(char) b = Err('x');
    printf("b == %c (okay? %s)\n", Value(b), b.is_okay ? "yes" : "no");

    return 0;
}
