#ifndef MAINMEMORY_HPP
#define MAINMEMORY_HPP

#include <map>
#include <deque>
#include <sys/sysctl.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>

#include "../MonitorModule.hpp"

#define BUFFERLEN 128
//#define DEQUE_SIZE 100
#define WORLD_WIDE_MAX_CPU_ON_UNIT 100

class MainMemory : public MonitorModule
{
    std::string _name;
    float _min, _max;
    std::map<std::string, std::deque<float> > _graphs;
    std::map<std::string, std::string> _data;

    float _frame;

    void dequeUpdate(std::string name, float ret);

    float getSystemMemoryUsagePercentage();
    double parseMemValue(const char * b);

  public:
    MainMemory(void);
    MainMemory(MainMemory const &src);
    virtual ~MainMemory(void);

    MainMemory &operator=(MainMemory const &rhs);

    void update(void);

    void setName(std::string name);
    virtual const std::string &getName(void) const;

    virtual const std::map<std::string, std::deque<float> > &getGraphs(void) const;
    virtual const float &getGraphMin(void) const;
    virtual const float &getGraphMax(void) const;
    virtual const std::map<std::string, std::string> &getData(void) const;
};

#endif
