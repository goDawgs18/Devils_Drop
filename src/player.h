#ifndef __PLAYER_AGENT__H
#define __PLAYER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class PlayerController : public Process, public AgentInterface {

    public:
    PlayerController() : Process(), AgentInterface(), z(1), run(false) {}

    void init() {
        goal_x = 0;
        goal_y = 0;
        count = 0;
        rampCount = 0;
        velocity = 0;
        score = 0;
        prevent_rotation();
        //TODO: OVERRIDER THE DESCONSTRUCTOR TO DO THE SUPER BUT ALSO PRINT OUT THE FINAL SCORE

        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            // std::cout << "keyup event" << '\n';
            if ( k == "s" ) {
                velocity = 0;           
            } else if ( k == "a" ) {
                velocity += 4;
            } else if ( k == "d" ) {
                velocity += -4;
            } 
        });
        notice_collisions_with("Tree", [&](Event &e) {
            std::cout << "Great Job! You made it " << score <<  " Feet down Devils Drop! \n";
            std::cout << "Press \"Go Down Devil's Drop\" to try again \n";

            emit(Event("destroyBlocks",{}));
            teleport(0, -1000, -3.1415);
            rampCount = 0;
            score = 0;
            count = 0;
            run = false;
        }); 
        watch("button_click", [&](Event& e) {
            if ( e.value()["value"] == "start" ) {
                emit(Event("destroyBlocks",{}));
                std::cout<< "Good Luck! \n";
                run = true;
                teleport(0, -200, -3.1415);
                velocity = 0;
            } 
        });
    }
    void start() {}
    void update() {
        track_velocity(velocity,0);
        // move_toward(goal_x, 0);
        // center(0.0, y());
        if (run) {
            if (4 < count && 10 - rampCount < score %20 ) {
                count = 0;
                rampCount++;
                auto x = rand() % 640 - 320;
                auto y = rand() % 100 + 350;
                add_agent("Tree",x, y, -1.570796327, BLOCK_STYLE);
            }
            // std::cout << "count = " << count << '\n';
            // std::cout << "rampCount = " << rampCount << '\n';
            if (rampCount > 10) {
                count++;
            }
            count++;
            score++;
        }
    }
    void stop() {}

    double goal_x, goal_y;
    double z;
    bool run;
    long count;
    int rampCount;
    int velocity;
    long score;
    const json BLOCK_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "black"}
               };

};

class Player : public Agent {
    public:
    Player(json spec, World& world) : Agent(spec, world) {
        add_process(bc);
    }
    private:
    PlayerController bc;
};

DECLARE_INTERFACE(Player)

#endif