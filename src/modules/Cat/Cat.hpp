#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>
#include <map>
#include <deque>
#include <sys/sysctl.h>

#include "../IMonitorModule.hpp"

#define BUFFERLEN 128

class Cat: public IMonitorModule
{
  public:
    Cat(void);
    Cat(Cat const &src);
    virtual ~Cat(void);

    Cat &operator=(Cat const &rhs);

    void update(void);

    void    setName(std::string name);
    virtual const std::string   &getName(void) const;
    virtual const std::map< std::string, std::deque<float> >    &getGraphs(void) const;
    virtual const float      &getGraphMin(void) const;
    virtual const float      &getGraphMax(void) const;
    virtual const std::map<std::string, std::string>    &getData(void) const;

  private:
    std::string _name;
    float _min;
    float _max;
    std::map< std::string, std::deque<float> > _graphs;
    std::map<std::string, std::string> _data;
};


#endif
