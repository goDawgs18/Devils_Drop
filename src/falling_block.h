#ifndef __FALLING_BLOCK_AGENT__H
#define __FALLING_BLOCK_AGENT__H 

#include "enviro.h"

// #include <nlohmann/json.hpp>

// for convenience
// using json = nlohmann::json;

using namespace enviro;

class FallingBlockController : public Process, public AgentInterface {

    public:
    FallingBlockController() : Process(), AgentInterface() {}

    void init() {
        velocity = 100;
        removeSelf = false;
        prevent_rotation();
        watch("destroyBlocks", [this](Event e) {
            removeSelf = true;
        });
    }
    void start() {}
    void update() {
        track_velocity(velocity,0);
        if (y() <= -350 || removeSelf) {
            remove_agent(id());
        }
    }
    void stop() {}
    int velocity;
    bool removeSelf;
    const json dummy = {  };

};

class FallingBlock : public Agent {
    public:
    FallingBlock(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    FallingBlockController c;
};

DECLARE_INTERFACE(FallingBlock)

#endif