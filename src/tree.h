#ifndef __TREE_AGENT__H
#define __TREE_AGENT__H 

#include "enviro.h"

// #include <nlohmann/json.hpp>

// for convenience
// using json = nlohmann::json;

using namespace enviro;

class TreeController : public Process, public AgentInterface {

    public:
    TreeController() : Process(), AgentInterface() {}

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

class Tree : public Agent {
    public:
    Tree(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    TreeController c;
};

DECLARE_INTERFACE(Tree)

#endif