#include <gbdk/platform.h>
#include <gbdk/font.h>
#include <stdio.h>

#include "vm.h"

extern const UBYTE BYTECODE[];                  // defined in bytecode.s
BANKREF_EXTERN(BYTECODE)

typedef struct actor_t {
    INT16 x, y;
    INT16 ID;
} actor_t;

const actor_t ACTORS[2] = {
    { 
        .ID = 1
    },{
        .ID = 2
    }
};

void process_VM() {
    while (1) {
        switch (ScriptRunnerUpdate()) {
            case RUNNER_DONE: return;
            case RUNNER_IDLE: wait_vbl_done(); break;
//            case RUNNER_BUSY: ;
        }
    }
}

void main() {
    font_init();
    font_set(font_load(font_spect));
    
    ScriptRunnerInit();
    ExecuteScript(BANK(BYTECODE), BYTECODE, 0, 0);
    printf(">> VM START\n");
    process_VM();
    printf("<< VM DONE");
}
