#ifndef __ROCK_AGENT__H
#define __ROCK_AGENT__H 

#include "enviro.h"

using namespace enviro;

class RockController : public Process, public AgentInterface {

    public:
    RockController() : Process(), AgentInterface() {}

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
};

class Rock : public Agent {
    public:
    Rock(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    RockController c;
};

DECLARE_INTERFACE(Rock)

#endif