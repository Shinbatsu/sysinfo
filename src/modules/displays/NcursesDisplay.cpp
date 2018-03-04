#include "NcursesDisplay.hpp"

NcursesDisplay::NcursesDisplay(void) :
    _module_separation_size(1),
    _module_height(MODULE_HEIGHT),
    _max_module_width(MODULE_WIDTH),
    _module_width(_max_module_width < COLS ? COLS : _max_module_width),
    _window_height(LINES),
    _window_width(COLS),
    _anime(0) {}

NcursesDisplay::NcursesDisplay(NcursesDisplay const& src) :
    _module_separation_size(1),
    _module_height(MODULE_HEIGHT),
    _max_module_width(MODULE_WIDTH),
    _module_width(_max_module_width),
    _window_height(LINES),
    _window_width(COLS),
    _anime(0) {
    *this = src;
}

NcursesDisplay::~NcursesDisplay() {}


NcursesDisplay& NcursesDisplay::operator=(NcursesDisplay const& rhs) {
    this->_window_height = rhs._window_height;
    this->_window_width  = rhs._window_width;
    this->_anime         = rhs._anime;
    this->_fenetres      = rhs.getWindow();

    return *this;
}

void NcursesDisplay::init(void) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    init_pair(DISP_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(DISP_RED, COLOR_RED, COLOR_BLACK);
    init_pair(DISP_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(DISP_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(DISP_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(DISP_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(DISP_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
}

void NcursesDisplay::init(const std::map<std::string, MonitorModule*>& modules) {
    this->init();

    int i            = 0;
    int height       = 0;
    int height_begin = _module_height;
    for (module_iterator it = modules.begin(); it != modules.end(); it++)
    {
        if (it->first != "cat")
        {
            if (it->second->getGraphs().size())
                height = _module_height;
            else if (it->second->getData().size())
                height = it->second->getData().size() + 3;
            else
                height = 3;
            _fenetres[it->first] = subwin(stdscr, height, _module_width, height_begin, 0);
            height_begin += _module_separation_size + height;
            i++;
        }
    }
}

bool NcursesDisplay::quit(void) {
    if (getch() == 27)
    {
        endwin();
        exit(0);
        return true;
    }
    return false;
}

std::map<std::string, WINDOW*> NcursesDisplay::getWindow() const { return this->_fenetres; }

void        NcursesDisplay::update(void) {}
inline void NcursesDisplay::_dispRefresh(void) {
    refresh();
    for (window_map_iterator it = _fenetres.begin(); it != _fenetres.end(); it++)
        wrefresh(it->second);
}

inline void NcursesDisplay::_dispWindows(const module_map& modules) {
    for (window_map_iterator it = _fenetres.begin(); it != _fenetres.end(); it++)
    {
        int             print_position = 1;
        module_iterator mainit         = modules.find(it->first);
        int             range_str_pos  = mainit->second->getName().length() + 4;

        //cat box
        if (mainit->second->getName() == "cat")
            continue;
        //module name
        wattron(it->second, COLOR_PAIR(MODULE_COLOR));
        box(it->second, ACS_VLINE, ACS_HLINE);
        mvwprintw(it->second, print_position, 1, ("[" + mainit->second->getName() + "]").c_str());
        wattroff(it->second, COLOR_PAIR(MODULE_COLOR));

        //range infos
        wattron(it->second, COLOR_PAIR(RANGE_INFO_COLOR));
        if (mainit->second->getGraphMin() < mainit->second->getGraphMax())
            mvwprintw(it->second, print_position++, range_str_pos, "(range %.2f to %.2f)",
                      mainit->second->getGraphMin(), mainit->second->getGraphMax());
        else
            print_position++;
        wattroff(it->second, COLOR_PAIR(RANGE_INFO_COLOR));

        //info percentages
        wattron(it->second, COLOR_PAIR(INFO_COLOR));
        int   i   = 0;
        float cpu = 0;
        for (std::map<std::string, std::deque<float>>::const_iterator secondit =
               mainit->second->getGraphs().begin();
             secondit != mainit->second->getGraphs().end(); secondit++)
        {
            for (std::deque<float>::const_iterator eqiter = secondit->second.begin();
                 eqiter != secondit->second.end() || i < 2; eqiter++, i++)
            {
                cpu += *eqiter;
            }
            mvwprintw(it->second, print_position++, INFO_PADDING, "[ %02i ] %s  ",
                      static_cast<int>(cpu / i), secondit->first.c_str());
        }

        for (std::map<std::string, std::string>::const_iterator datait =
               mainit->second->getData().begin();
             datait != mainit->second->getData().end(); datait++)
        {
            mvwprintw(it->second, print_position++, INFO_PADDING, "[ %s ] %s  ",
                      datait->second.c_str(), datait->first.c_str());
        }
        wattroff(it->second, COLOR_PAIR(INFO_COLOR));
    }
}

void NcursesDisplay::render(const module_map& modules, Core& core) {
    (void) core;
    erase();
    getmaxyx(stdscr, _window_height, _window_width);
    _dispWindows(modules);
    _dispRefresh();
    this->quit();
}
