#ifndef __BUFF_AGENT__H
#define __BUFF_AGENT__H 

#include "enviro.h"

using namespace enviro;

class buffController : public Process, public AgentInterface {

    public:
    buffController() : Process(), AgentInterface() {}

    void init() { //Here we only want to disappear when the player collides with us
        notice_collisions_with("Player", [&](Event &e) {
            remove_agent(id());
        });            
    }
    void start() {}
    void update() {}
    void stop() {}

};

class buff : public Agent {
    public:
    buff(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    buffController c;
};

DECLARE_INTERFACE(buff)

#endif