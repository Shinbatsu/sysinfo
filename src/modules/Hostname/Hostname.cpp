#include "Hostname.hpp"

Hostname::Hostname(void): _name("Hostname"), _min(0), _max(0), _graphs(std::map< std::string, std::deque<float> >()), _data(std::map<std::string, std::string>())
{
}

Hostname::Hostname(Hostname const &src)
{
    *this = src;
}

Hostname::~Hostname()
{
}

void Hostname::update(void)
{
    char buff[BUFFERLEN];
    size_t buffLen = BUFFERLEN;

    sysctlbyname("kern.hostname", &buff, &buffLen, NULL, 0);

    std::string name(buff);
    // // std::cout << name << std::endl;//WHO THE FUCK DID THIS!!???
	this->_data["Hostname"] = name;

    // this->setName(name);
}

const float &Hostname::getGraphMin(void) const
{
    return this->_min;
}

const float &Hostname::getGraphMax(void) const
{
    return this->_max;
}

const std::map< std::string, std::deque<float> > &Hostname::getGraphs(void) const
{
    return this->_graphs;
}

const std::map<std::string, std::string> &Hostname::getData(void) const
{
    return this->_data;
}
const std::string &Hostname::getName(void) const
{
    return this->_name;
}

void Hostname::setName(std::string name)
{
    this->_name = name;
}

Hostname &Hostname::operator=(Hostname const &rhs)
{
    this->_name = rhs.getName();
    this->_graphs = rhs.getGraphs();
    this->_data = rhs.getData();
    this->_min = rhs.getGraphMin();
    this->_max = rhs.getGraphMax();
    return *this;
}
