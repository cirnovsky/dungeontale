#include "core/engine.h"

int main(int argc, char *argv[]) {
    Engine *engine = malloc(sizeof(Engine));
    engine_init(engine);
    engine_run(engine);
    /*
    engine_shutdown();
    */
    return 0;
}
