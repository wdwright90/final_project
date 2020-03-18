#ifndef __PLAYER_AGENT__H
#define __PLAYER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class PlayerController : public Process, public AgentInterface {

    public:
    PlayerController() : Process(), AgentInterface(), f(0), tau(0), buff_timer(0) {}

    void init() {
        //The below block of code looks for key down and key up
        std::cout << "Made a player " << "\n";
        watch("keydown", [&](Event &e) {
            if ( e.value()["client_id"] == get_client_id() ) {
                auto k = e.value()["key"].get<std::string>();
                if ( k == "w" ) {
                    f = magnitude;              
                } else if ( k == "s" ) {
                    f = -magnitude;  
                } else if ( k == "a" ) {
                    tau = -magnitude;
                } else if ( k == "d" ) {
                    tau = magnitude;
                }
            } 
        });        
        watch("keyup", [&](Event &e) {
            if ( e.value()["client_id"] == get_client_id() ) {
                auto k = e.value()["key"].get<std::string>();
                if ( k == "w" || k == "s" ) {
                    f = 0;               
                } else if ( k == "a" ) {
                    tau = 0;
                } else if ( k == "d" ) {
                    tau = 0;
                } 
            }
        });

        //We also want to notice when our player collides with a buff or a debuff
        //When we collide we start the buff/debuff timer and set the speed multiplier
        notice_collisions_with("buff", [&](Event &e) {
            buff_timer = 0;
            buff_multi = 1.25;
        });
        notice_collisions_with("debuff", [&](Event &e) {
            buff_timer = 0;
            buff_multi = .75;
        });
    }
    void start() {}
    void update() {
        //On each update we want to apply force and increment the timer
        //When the timer reaches 30 we set the multiplier back to 1 and the timer out of our timing constraint
        apply_force(buff_multi*f,buff_multi*tau);
        if (buff_timer > 30) {
            buff_timer = -1;
            buff_multi = 1.0;
        } else if (buff_timer == 1) { //Here we check if we consumed a buff and then randomly create a new one to replace it
            buff_timer++;
            int r = rand() % 4;
            int randx;
            int randy;
            if (buff_multi < 1) {
                if (r == 0) {
                    //Create a new debuff on the bottom part of the track
                    randx = rand() % 700 - 350;
                    randy = rand() % 100 + 100;
                    Agent& d = add_agent("debuff", randx, randy, 0, DEBUFF_STYLE);
                } else if (r == 1) {
                    //Create a new debuff on the top part of the track
                    randx = rand() % 700 - 350;
                    randy = rand() % 100 - 200;
                    Agent& d = add_agent("debuff", randx, randy, 0, DEBUFF_STYLE);
                } else if (r == 2) {
                    //Create new debuff on the left part of the track
                    int randx = rand() % 100 - 350;
                    int randy = rand() % 400 - 200;
                    Agent& d = add_agent("debuff", randx, randy, 0, DEBUFF_STYLE);
                } else {
                    //Create new debuff on the right part of track
                    randx = rand() % 100 + 250;
                    randy = rand() % 400 - 200;
                    Agent& d = add_agent("debuff", randx, randy, 0, DEBUFF_STYLE);
                }
            } else {
                if (r == 0) {
                    //Create a new buff on the bottom part of the track
                    randx = rand() % 700 - 350;
                    randy = rand() % 100 + 100;
                    Agent& b = add_agent("buff", randx, randy, 0, BUFF_STYLE);
                } else if (r == 1) {
                    //Create a new buff on the top part of the track
                    randx = rand() % 700 - 350;
                    randy = rand() % 100 - 200;
                    Agent& b = add_agent("buff", randx, randy, 0, BUFF_STYLE);
                } else if (r == 2) {
                    //Create new buff on the left part of the track
                    int randx = rand() % 100 - 350;
                    int randy = rand() % 400 - 200;
                    Agent& b = add_agent("buff", randx, randy, 0, BUFF_STYLE);
                } else {
                    //Create new buff on the right part of track
                    randx = rand() % 100 + 250;
                    randy = rand() % 400 - 200;
                    Agent& b = add_agent("buff", randx, randy, 0, BUFF_STYLE);
                }
            }
        } else if (buff_timer > -1) { //This just makes sure we want our timer to run
            buff_timer++;
        }
    }
    void stop() {}

    //Here we have our player variables like force, torque and buff effects
    double f, tau;
    double buff_multi = 1.0;
    int buff_timer = 0;
    double const magnitude = 200;
    const json BUFF_STYLE = { 
                   {"fill", "lightgreen"}, 
                   {"stroke", "black"}, 
                   {"strokeWidth", "1px"},
                   {"strokeOpacity", "1"}
               },
               DEBUFF_STYLE = { 
                   {"fill", "red"}, 
                   {"stroke", "black"}, 
                   {"strokeWidth", "1px"},
                   {"strokeOpacity", "1"}
               }; 

};

class Player : public Agent {
    public:
    Player(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    PlayerController c;
};

DECLARE_INTERFACE(Player)

#endif