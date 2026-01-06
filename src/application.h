#pragma once

#include <QApplication>

namespace test {

class Application : public QApplication {
	Q_OBJECT

public:
	explicit Application(int& argc, char** argv, int = ApplicationFlags);

protected:
	bool notify(QObject*, QEvent*) override;
};

}  // namespace test