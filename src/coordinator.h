#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 

#include "enviro.h"

using namespace enviro;

class CoordinatorController : public Process, public AgentInterface {

    public:
    CoordinatorController() : Process(), AgentInterface() {}

    void init() {
        //This watches for a connection event and then assigns a client ID, then we create a player agent 
        watch("connection", [&](Event e) {
            if ( ! e.value()["client_id"].is_null() ) {
                std::cout << "Connection from " << e.value() << "\n";
                Agent& a = add_agent("Player", x, 175, -1.57, {{"fill","black"},{"stroke","black"}});
                a.set_client_id(e.value()["client_id"]);
                x += 30; //incrementing this makes it so our created players aren't stacked
            }
        });
    }
    void start() {
            //Here we initialize the buffs around the track
            for (int i=0; i < 3; i++){
            //Make the buffs and debuffs on the bottom part of the track
            int randx = rand() % 700 - 350;
            int randy = rand() % 100 + 100;
            Agent& b_d = add_agent("buff", randx, randy, 0, BUFF_STYLE);
            randx = rand() % 700 - 350;
            randy = rand() % 100 + 100;
            Agent& d_d = add_agent("debuff", randx, randy, 0, DEBUFF_STYLE);

            //Make the buffs and debuffs on the top part of the track
            randx = rand() % 700 - 350;
            randy = rand() % 100 - 200;
            Agent& b_u = add_agent("buff", randx, randy, 0, BUFF_STYLE);
            randx = rand() % 700 - 350;
            randy = rand() % 100 - 200;
            Agent& d_u = add_agent("debuff", randx, randy, 0, DEBUFF_STYLE);
        }
        for (int i=0; i < 2; i++) {
            //Make the buffs and debuffs on the left part of the track
            int randx = rand() % 100 - 350;
            int randy = rand() % 400 - 200;
            Agent& b_l = add_agent("buff", randx, randy, 0, BUFF_STYLE);
            randx = rand() % 100 - 350;
            randy = rand() % 400 - 200;
            Agent& d_l = add_agent("debuff", randx, randy, 0, DEBUFF_STYLE); 

            //Make buffs and debuffs on the right part of track
            randx = rand() % 100 + 250;
            randy = rand() % 400 - 200;
            Agent& b_r = add_agent("buff", randx, randy, 0, BUFF_STYLE);
            randx = rand() % 100 + 250;
            randy = rand() % 400 - 200;
            Agent& d_r = add_agent("debuff", randx, randy, 0, DEBUFF_STYLE);
        }
    }
    void update() {}
    void stop() {}


    //This is our initial x position and the buff/debuff style
    double x = 260;
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

class Coordinator : public Agent {
    public:
    Coordinator(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    CoordinatorController c;
};

DECLARE_INTERFACE(Coordinator)

#endif