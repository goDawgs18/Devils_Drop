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

        //do not want it to rotate
        prevent_rotation();

        // Will change how the player moves based on the keys
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "s" ) {
                velocity = 0;           
            } else if ( k == "a" ) {
                velocity += 4;
            } else if ( k == "d" ) {
                velocity += -4;
            } 
        });

        // Makes sure everything ends when a tree gets hit
        notice_collisions_with("Tree", [&](Event &e) {
            std::cout << "Great Job! You made it " << score <<  " Feet down Devils Drop! \n";
            std::cout << "Press \"Go Down Devil's Drop\" to try again \n";

            emit(Event("destroyBlocks",{}));
            teleport(0, -10000, -3.1415);
            rampCount = 0;
            score = 0;
            count = 0;
            run = false;
        }); 

        // makes sure everything ends when a rock gets hit
        notice_collisions_with("Rock", [&](Event &e) {
            std::cout << "Great Job! You made it " << score <<  " Feet down Devils Drop! \n";
            std::cout << "Press \"Go Down Devil's Drop\" to try again \n";

            emit(Event("destroyBlocks",{}));
            teleport(0, -10000, -3.1415);
            rampCount = 0;
            score = 0;
            count = 0;
            run = false;
        }); 

        // Will start the game flow
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

        // This if statement will only make everything start once user presses start
        if (run) {
            // this if statment is used to control when objs get generated
            if (4 < count && 10 - rampCount < score %20 ) {
                count = 0;
                rampCount++;
                //These will randomize locations of the obstacles
                auto x = rand() % 640 - 320;
                auto y = rand() % 100 + 350;
                
                //randomizes if a tree or rock gets generated
                if (rand() %2 == 1) {
                    add_agent("Tree",x, y, -1.570796327, TREE_STYLE);
                } else {
                    add_agent("Rock",x, y, -1.570796327, ROCK_STYLE);
                }
            }

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
    const json TREE_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "black"}
               };

    const json ROCK_STYLE = { 
                   {"fill", "gray"}, 
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