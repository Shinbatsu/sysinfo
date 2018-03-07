#ifndef MonitorDisplay_HPP
#define MonitorDisplay_HPP

#include "../modules/MonitorModule.hpp"

class Core;

class MonitorDisplay {
   public:
    virtual ~MonitorDisplay(void) {};

    virtual void init(void)                                                            = 0;
    virtual void update(void)                                                          = 0;
    virtual void render(const std::map<std::string, MonitorModule*>& disp, Core& core) = 0;
};

#endif
