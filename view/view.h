#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "../control/control.h"
#include "../model/model.h"


class View {
public:
  virtual void run() = 0;

  virtual int getWinWidth()  = 0;
  virtual int getWinHeight() = 0;

  virtual void setModel(Model *model) = 0;
};

#endif /* VIEW_HEADER */
