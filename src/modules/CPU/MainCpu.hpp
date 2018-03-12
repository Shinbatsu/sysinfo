#ifndef MAINCPU_HPP
#define MAINCPU_HPP

#include <map>
#include <deque>
#include <sys/sysctl.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>
#include "../MonitorModule.hpp"

#define WORLD_WIDE_MAX_CPU_ON_UNIT 100
#define BUFFERLEN 128

class MainCpu : public MonitorModule
{
    std::string _name;
    float _min, _max;
    std::map<std::string, std::deque<float> > _graphs;
    std::map<std::string, std::string> _data;

    size_t _oldWorkTicks, _oldTotalTicks;
    size_t _oldCpusWorkTicks[WORLD_WIDE_MAX_CPU_ON_UNIT], _oldCpusTotalTicks[WORLD_WIDE_MAX_CPU_ON_UNIT];  

    float calculateCPULoad(size_t newWorkTicks, size_t oldWorkTicks,  size_t newTotalTicks, size_t oldTotalTicks);
    void setCPUsLoad();
    void setCpuDatas();
    void dequeUpdate(std::string name, float ret);

  public:
    MainCpu(void);
    MainCpu(MainCpu const &src);
    virtual ~MainCpu(void);

    MainCpu &operator=(MainCpu const &rhs);

    void fetch(void);
    void update(void);

    void setName(std::string name);
    virtual const std::string &getName(void) const;

    virtual const std::map<std::string, std::deque<float> > &getGraphs(void) const;
    virtual const float &getGraphMin(void) const;
    virtual const float &getGraphMax(void) const;
    virtual const std::map<std::string, std::string> &getData(void) const;
};

#endif
