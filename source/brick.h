#include "bannerbrick.h"
#include "mailbrick.h"

struct brick {
    int (*execute)();
    const char* name;
};

struct brick bricks[] = {
        {&bannerbrick_execute, "Bannerbrick"},
        {&mailbrick_execute, "Mailbrick"}
};

const int brick_count = sizeof(bricks) / sizeof(struct brick);