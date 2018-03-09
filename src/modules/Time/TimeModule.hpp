#ifndef __TIME_MONITOR__
#define __TIME_MONITOR__

#include <time.h>
#include <sys/sysctl.h>
#include <ctime>

#include "../MonitorModule.hpp"

class TimeModule: public MonitorModule {
    std::string                              _name;
    std::map<std::string, std::string>       _data;
    std::map<std::string, std::deque<float>> _graphs;
    float                                    _min;
    float                                    _max;

    std::string now();
    std::string uptime();
    std::string timeToDate(time_t time);
    std::string timeToString(time_t time);

   public:
    TimeModule();
    TimeModule(TimeModule const& src);
    virtual ~TimeModule(void);

    TimeModule& operator=(TimeModule const& rhs);

    //From interface :
    virtual void fetch(void);
    virtual void update(void);

    virtual const std::string&                              getName(void) const;
    virtual const std::map<std::string, std::deque<float>>& getGraphs(void) const;
    virtual const float&                                    getGraphMin(void) const;
    virtual const float&                                    getGraphMax(void) const;
    virtual const std::map<std::string, std::string>&       getData(void) const;
};

#endif