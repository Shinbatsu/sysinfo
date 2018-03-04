#ifndef NCURSESDISPLAY_H
#define NCURSESDISPLAY_H

#include <ncurses.h>
#include "../IMonitorDisplay.hpp"
#include "../../Core.hpp"


class NcursesDisplay: public IMonitorDisplay {

    typedef std::map<std::string, MonitorModule*>          module_map;
    typedef module_map::const_iterator                     module_iterator;
    typedef std::map<std::string, WINDOW*>::const_iterator window_map_iterator;

   public:
    NcursesDisplay(void);
    NcursesDisplay(NcursesDisplay const& src);
    virtual ~NcursesDisplay();

    NcursesDisplay& operator=(NcursesDisplay const& rhs);

    virtual void                   init(void);
    virtual void                   init(const module_map& disp);
    virtual void                   update(void);
    virtual void                   render(const module_map& disp, Core& core);
    bool                           quit(void);
    std::map<std::string, WINDOW*> getWindow() const;

   private:
    void _dispRefresh(void);
    void _dispWindows(const module_map& disp);

    std::map<std::string, WINDOW*> _fenetres;
    const int                      _module_separation_size;
    const int                      _module_height;
    const int                      _max_module_width;
    int                            _module_width;
    int                            _window_height;
    int                            _window_width;
    int                            _anime;
};

#define MODULE_HEIGHT 11
#define MODULE_WIDTH COLS
#define INFO_PADDING 5
#define ANIME_WIDTH 1

#define DISP_WHITE 0
#define DISP_RED 1
#define DISP_GREEN 2
#define DISP_BLUE 3
#define DISP_CYAN 4
#define DISP_YELLOW 5
#define DISP_MAGENTA 6

#define TITLE_COLOR DISP_RED
#define CATS_COLOR DISP_MAGENTA
#define MODULE_COLOR DISP_GREEN
#define RANGE_INFO_COLOR DISP_BLUE
#define INFO_COLOR DISP_MAGENTA

#define KEY_ESC 27

#endif
