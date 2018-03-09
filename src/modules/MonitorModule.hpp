#ifndef MonitorModule_HPP
#define MonitorModule_HPP

#include <iostream>
#include <exception>
#include <map>
#include <queue>

#define DEQUE_SIZE 400

class MonitorModule
{

public:
	virtual ~MonitorModule(void) {};

    virtual void update(void) = 0;

    virtual const std::string &getName(void) const = 0;
    virtual const std::map<std::string, std::deque<float> > &getGraphs(void) const = 0;
    virtual const float &getGraphMin(void) const = 0;
    virtual const float &getGraphMax(void) const = 0;
    virtual const std::map<std::string, std::string> &getData(void) const = 0;
};

#endif
