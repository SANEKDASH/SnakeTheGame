#include <unistd.h>

#include "../view/t_view.h"
#include "../model/model.h"
#include "../control/control.h"
#include "../view/g_view.h"

int main(int argc,  char * const *argv)
{
  int opt = -1;
  int botCount = 0;
  const char *player2Ctl = nullptr;

  Control ctl;
  Model model;
  View *view = nullptr;  
  
  while ((opt = getopt(argc, argv, "b:p:tg")) != -1) {
	switch (opt) {
	case 'b': {	  
	  botCount = atoi(optarg);
	  break;
	}

	case 'p': {
	  player2Ctl = optarg;
	  break;
	}

	case 't':{
	  if (view == nullptr) {
		TextView *tView = new TextView();
		tView->setControl(&ctl);
		
		view = tView;
	  }
	  
	  break;
	}

    case 'g': {
	  if (view == nullptr) {		
		view = new GraphicView();
	  }
	  
	  break;	  
	}
	  
	default:
	  break;  
    }
  }  

  if (view == nullptr) {
	TextView *tView = new TextView();
	tView->setControl(&ctl);
		
	view = tView;
  }
  
  model.setXWinSize(view->getWinWidth());
  model.setYWinSize(view->getWinHeight());

  model.initScene(botCount, player2Ctl);

  view->setModel(&model);
  
  view->run();

  delete view;
  
  return 0;
}
