#pragma once

#include <QMainWindow>

namespace test {

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
};

}  // namespace test