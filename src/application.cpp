#include "application.h"

#include <QMessageBox>

namespace test {

Application::Application(int& argc, char** argv, int windowFlags):
	QApplication(argc, argv, windowFlags)
{
}

bool Application::notify(QObject* object, QEvent* event)
{
	try {
		return QApplication::notify(object, event);
	}
	catch (const std::exception& e) {
		QMessageBox::warning(nullptr, "Error", e.what());
	}
	return true;
}

}  // namespace test