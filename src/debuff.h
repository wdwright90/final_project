#ifndef __DEBUFF_AGENT__H
#define __DEBUFF_AGENT__H 

#include "enviro.h"

using namespace enviro;

class debuffController : public Process, public AgentInterface {

    public:
    debuffController() : Process(), AgentInterface() {}

    void init() { //Here we only want to disappear when the player collides with us
        notice_collisions_with("Player", [&](Event &e) {
            remove_agent(id());
        });
    }
    void start() {}
    void update() {}
    void stop() {}

};

class debuff : public Agent {
    public:
    debuff(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    debuffController c;
};

DECLARE_INTERFACE(debuff)

#endif