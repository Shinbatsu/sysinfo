#include "TimeModule.hpp"

TimeModule::TimeModule() :
    _name("uptime"),
    _min(0),
    _max(0) {
    this->update();
}
TimeModule::TimeModule(TimeModule const& src) { *this = src; }
TimeModule::~TimeModule(void) {}

void TimeModule::fetch(void) {}
void TimeModule::update(void) {
    _data["boot_time"]   = this->uptime();
    _data["actual_time"] = this->now();
}

const std::string& TimeModule::getName(void) const { return _name; }

const std::map<std::string, std::deque<float>>& TimeModule::getGraphs(void) const {
    return _graphs;
}

const std::map<std::string, std::string>& TimeModule::getData(void) const { return _data; }

const float& TimeModule::getGraphMin(void) const { return _min; }

const float& TimeModule::getGraphMax(void) const { return _max; }\

std::string TimeModule::uptime() {
    struct timeval boottime;
    size_t         len    = sizeof(boottime);
    int            mib[2] = {CTL_KERN, KERN_BOOTTIME};
    if (sysctl(mib, 2, &boottime, &len, NULL, 0) < 0)
        return "-1.0";

    return this->timeToDate(boottime.tv_sec);
}

std::string TimeModule::now() { return this->timeToDate(std::time(NULL)); }

std::string TimeModule::timeToDate(time_t time) {
    std::tm* ptm = std::localtime(&time);
    char     buffer[32];
    std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
    std::string result(buffer);
    return result;
}

std::string TimeModule::timeToString(time_t time) {
    std::stringstream ss;
    ss << time;
    return ss.str();
}

TimeModule& TimeModule::operator=(TimeModule const& rhs) {
    this->_name   = rhs.getName();
    this->_graphs = rhs.getGraphs();
    this->_data   = rhs.getData();
    this->_min    = rhs.getGraphMin();
    this->_max    = rhs.getGraphMax();
    return *this;
}
