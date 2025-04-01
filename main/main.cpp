#include "../view/t_view.h"
#include "../model/model.h"
#include "../control/control.h"

int main(int argc, const char *argv[])
{
    Control  ctl;
    Model    model;
    TextView view;

	model.setXWinSize(view.getWinCols());
	model.setYWinSize(view.getWinRows());

	model.initScene();
	
    view.setModel(&model);

    view.run(ctl);

    return 0;
}
