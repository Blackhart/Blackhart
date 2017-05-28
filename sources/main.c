#include <stdlib.h>
#include <stdio.h>
#include "../includes/pil/pil.h"
#include "../includes/core/math/math.h"

int main()
{
    vec4 const a = { .x = 1.0, .y = 0.0, .z = 0.0, .w = 1.0 };
    vec4 const b = { .x = -1.0, .y = 0.0, .z = 0.0, .w = 1.0 };
    vec4 res = Max_vec4(&a, &b);
    printf("%f", Dot_vec4(&a, &b));
    return EXIT_SUCCESS;
}