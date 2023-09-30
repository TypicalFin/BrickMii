#include "brick/bannerbrick.h"
#include "brick/mailbrick.h"

struct brick {
    int (*execute)();
    const char* name;
};

struct brick bricks[] = {
        {&bannerbrick_execute, "Bannerbrick"},
        {&mailbrick_execute, "Mailbrick"}
};

const int brick_count = sizeof(bricks) / sizeof(bricks[0]);