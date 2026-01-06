#include "src/application.h"
#include "src/gui/mainwindow.h"

int main(int argc, char* argv[])
{
	test::Application a(argc, argv);

	test::MainWindow mainWindow;
	mainWindow.show();

	return a.exec();
}
