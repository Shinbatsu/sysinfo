#ifndef CORE_HPP
# define CORE_HPP

#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Displays/MonitorDisplay.hpp"
#include "modules/MonitorModule.hpp"
#include "Displays/NcursesDisplay.hpp"

#include "modules/Time/TimeModule.hpp"
#include "modules/CPU/MainCpu.hpp"
#include "modules/Cat/Cat.hpp"
#include "modules/Memory/MainMemory.hpp"
#include "modules/Hostname/Hostname.hpp"
#include "modules/OS/OSModule.hpp"
#include "modules/Time/TimeModule.hpp"

#include "modules/Hostname/Hostname.hpp"

#define SIZE_OPT	10

class MonitorModule;
class MonitorDisplay;

class Core
{
private:
	bool									_running;
	std::vector<MonitorDisplay*>			_displays;
	std::map<std::string, MonitorModule*>	_modules;
	int										_activeDisplayIndex;


public:
	Core();

	Core(const Core &o);

	virtual ~Core();

	Core &operator=(const Core &o);

	void init(char display_options[SIZE_OPT]);
	void update();
	void render();

	void start(char display_options[SIZE_OPT]);
	void stop();
	void loop();

	void deleteModule(std::string);
	void addModule(std::string);
	void test(int iterations);
};

#endif
