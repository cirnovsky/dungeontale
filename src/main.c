#include "core/engine.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");

    engine_init();
    engine_run();
    engine_shutdown();
    return 0;
}
