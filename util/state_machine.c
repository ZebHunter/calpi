#include "state_machine.h"


stat_t stat_init() {
    return 0;
}
stat_t stat_inc(stat_t stat) {
    return stat + 1;
}
void stat_apply(state_t* state, stat_t (*stat_fun)(stat_t)){
    state->stats = stat_fun(state->stats);
}
