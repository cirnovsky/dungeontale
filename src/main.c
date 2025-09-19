#include "core/engine.h"
#include <locale.h>

int main() {
    engine_init();
    engine_run();
    engine_shutdown();
    return 0;
}
