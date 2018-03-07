#include "OSModule.hpp"

OSModule::OSModule(void) :
    _name("OS"),
    _graphMin(0),
    _graphMax(0),
    _graphs(std::map<std::string, std::deque<float>>()),
    _datas(std::map<std::string, std::string>()) {
    try
    {
        this->_name += " ";
        set_osname();
        this->_name += " ";
        set_osversion();
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(0);
    }
}

OSModule::~OSModule() {}

void OSModule::set_osname() {

    const char* strtmp = "sw_vers -productName";
    char        str[256];

    FILE* ret = popen(strtmp, "r");

    if (!ret)
        return;

    while (!feof(ret))
    {
        fgets(str, 256, ret);
    }

    this->_name += strtok(str, "\n");

    pclose(ret);
}

void OSModule::set_osversion() {
    const char* strtmp = "sw_vers -productVersion";
    char        str[256];

    FILE* ret = popen(strtmp, "r");

    if (!ret)
        throw std::runtime_error("sw_vers -productVersion not found !");

    while (!feof(ret))
    {
        fgets(str, 256, ret);
    }

    this->_name += strtok(str, "\n");

    pclose(ret);
}

void OSModule::update(void) {}

const std::map<std::string, std::deque<float>>& OSModule::getGraphs(void) const {
    return this->_graphs;
}

const float& OSModule::getGraphMin(void) const { return this->_graphMin; }
const float& OSModule::getGraphMax(void) const { return this->_graphMax; }

const std::map<std::string, std::string>& OSModule::getData(void) const { return this->_datas; }

OSModule::OSModule(OSModule const& src) { *this = src; }

const std::string& OSModule::getName(void) const { return (this->_name); }

OSModule& OSModule::operator=(OSModule const& rhs) {
    this->_name     = rhs.getName();
    this->_graphs   = rhs.getGraphs();
    this->_datas    = rhs.getData();
    this->_graphMin = rhs.getGraphMin();
    this->_graphMax = rhs.getGraphMax();
    return *this;
}
