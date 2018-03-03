#include "Cat.hpp"

Cat::Cat(void): _name(""), _min(0), _max(0), _graphs(std::map< std::string, std::deque<float> >()), _data(std::map<std::string, std::string>())
{
}

Cat::Cat(Cat const &src)
{
    *this = src;
}

Cat::~Cat()
{
}

void Cat::update(void)
{
    // char buff[BUFFERLEN];
    // size_t buffLen = BUFFERLEN;

    // sysctlbyname("kern.hostname", &buff, &buffLen, NULL, 0);

    std::string name("cat");
    // // std::cout << name << std::endl;//WHO THE FUCK DID THIS!!???
    this->setName(name);
}

const float &Cat::getGraphMin(void) const
{
    return this->_min;
}

const float &Cat::getGraphMax(void) const
{
    return this->_max;
}

const std::map< std::string, std::deque<float> > &Cat::getGraphs(void) const
{
    return this->_graphs;
}

const std::map<std::string, std::string> &Cat::getData(void) const
{
    return this->_data;
}
const std::string &Cat::getName(void) const
{
    return this->_name;
}

void Cat::setName(std::string name)
{
    this->_name = name;
}

Cat &Cat::operator=(Cat const &rhs)
{
    this->_name = rhs.getName();
    this->_min = rhs.getGraphMin();
    this->_max = rhs.getGraphMax();
    this->_graphs = rhs.getGraphs();
    this->_data = rhs.getData();
    return *this;
}
