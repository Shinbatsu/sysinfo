#ifndef OSMODULE_HPP
#define OSMODULE_HPP

#include <mach-o/dyld.h>
#include <sys/sysctl.h>

#include "../MonitorModule.hpp"

class OSModule: public MonitorModule {
   public:
    OSModule(void);
    OSModule(OSModule const& src);
    virtual ~OSModule(void);

    OSModule& operator=(OSModule const& rhs);

    virtual void update(void);

    virtual const std::string&                              getName(void) const;
    virtual const std::map<std::string, std::deque<float>>& getGraphs(void) const;
    virtual const std::map<std::string, std::string>&       getData(void) const;
    virtual const float&                                    getGraphMin(void) const;
    virtual const float&                                    getGraphMax(void) const;

   private:
    void set_osname(void);
    void set_osversion(void);

    std::string                              _name;
    float                                    _graphMin;
    float                                    _graphMax;
    std::map<std::string, std::deque<float>> _graphs;
    std::map<std::string, std::string>       _datas;
};

#endif
