#include "Core.hpp"

Core::Core() :
    _running(false),
    _displays(std::vector<MonitorDisplay*>()),
    _modules(std::map<std::string, MonitorModule*>()),
    _activeDisplayIndex(0) {}

Core::Core(const Core& o) { *this = o; }

Core::~Core() {}

Core& Core::operator=(const Core& o) {
    if (this != &o)
    {
        _running            = o._running;
        _displays           = o._displays;
        _modules            = o._modules;
        _activeDisplayIndex = o._activeDisplayIndex;
    }
    return *this;
}

void Core::init(char display_options[SIZE_OPT]) {
    static int modules = 0;
    int        i = 0, l = 0;
    char       rank = 48;
    char       name[30];
    while (display_options[i])
    {
        bzero(name, 30);
        if (modules >= 7)
            break;

        if (display_options[i] == 'h' && (name[0] = rank))
        {
            strcpy(&(name[1]), "Intel(R) Core(TM) i5-3470S");
            _modules[name] = new Hostname();
            modules++;
        }
        if (display_options[i] == 't' && (name[0] = rank))
        {
            strcpy(&(name[1]), "uptime");
            _modules[name] = new TimeModule();
            modules++;
        }
        if (display_options[i] == 'c' && (name[0] = rank))
        {
            strcpy(&(name[1]), "CPU");
            _modules[name] = new MainCpu();
            modules++;
        }
        if (display_options[i] == 'r' && (name[0] = rank))
        {
            strcpy(&(name[1]), "Memory");
            _modules[name] = new MainMemory();
            modules++;
        }
        if (display_options[i] == 'n' && (name[0] = rank))
        {
            strcpy(&(name[1]), "Network");
            _modules[name] = new NetworkModule();
            modules++;
        }
        if (display_options[i] == 'a' && (name[0] = rank))
        {
            _modules["cat"] = new Cat();
            modules++;
        }
        if (display_options[i] == 'o' && (name[0] = rank))
        {
            strcpy(&(name[1]), "OS");
            _modules[name] = new OSModule();
            modules++;
        }
        rank++;
        i++;
    }
    i = 0;
    while (display_options[i])
    {
        if (l == 0 && display_options[i] == 'l')
        {
            l++;
            NcursesDisplay* ncurses = new NcursesDisplay();
            ncurses->init(_modules);
            _displays.push_back(ncurses);
        }
        i++;
    }
    if (l == 0)
        _displays.push_back(new BeautifulDisplay());
}

void Core::update() {
    typedef std::map<std::string, MonitorModule*>::iterator iterator;

    for (iterator modul = _modules.begin(); modul != _modules.end(); modul++)
        modul->second->update();

    if (!_displays.empty())
        _displays[_activeDisplayIndex]->update();
}

void Core::render() {
    if (!_displays.empty())
        _displays[_activeDisplayIndex]->render(_modules, *this);
}

void Core::start(char display_options[SIZE_OPT]) {
    _running = true;

    init(display_options);
    loop();
}

void Core::stop() { _running = false; }

void Core::deleteModule(std::string name) {
    std::map<std::string, MonitorModule*>::iterator it;

    for (it = _modules.begin(); it != _modules.end(); it++)
    {
        if ((std::isalpha(it->first.front()) ? it->first.c_str()
                                             : it->first.substr(1, it->first.length()).c_str())
            == name)
        {
            _modules.erase(it);
            return;
        }
    }
    return;
}

void Core::addModule(std::string name) {
    std::map<std::string, MonitorModule*>::iterator it;

    for (it = _modules.begin(); it != _modules.end(); it++)
    {
        if ((std::isalpha(it->first.front()) ? it->first.c_str()
                                             : it->first.substr(1, it->first.length()).c_str())
            == name)
        {
            return;
        }
    }
    if (name == "Intel(R) Core(TM) i5-3470S")
    {
        _modules[name] = new Hostname();
    }
    if (name == "uptime")
    {
        _modules[name] = new TimeModule();
    }
    if (name == "CPU")
    {
        _modules[name] = new MainCpu();
    }
    if (name == "Memory")
    {
        _modules[name] = new MainMemory();
    }
    if (name == "Network")
    {
        _modules[name] = new NetworkModule();
    }
    if (name == "OS")
    {
        _modules[name] = new OSModule();
    }
}

void Core::loop() {
    double  tickTime   = 1000000.0 / 60.0;
    clock_t beforeTime = clock();
    while (_running)
    {
        clock_t currentTime = clock();
        if (currentTime - beforeTime > tickTime)
        {
            update();
            render();
            beforeTime = clock();
        }
    }
}
