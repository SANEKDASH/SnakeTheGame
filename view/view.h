#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "../control/control.h"

class View {
public:
    virtual void run(Control &ctl) = 0;
};

#endif /* VIEW_HEADER */
