#include "mainwindow.h"

#include <QBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

#include "sectionwidget.h"

namespace test {

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags)
{
	setWindowTitle("Test main window for SectionWidget");
	setMinimumSize(640, 480);

	auto* centralWidget = new QWidget(this);
	auto* mainLayout    = new QVBoxLayout(centralWidget);
	setCentralWidget(centralWidget);
	centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	auto* switchButton = new QCheckBox("Switch section mode");

	auto* sectionWidget = new SectionWidget("This is a section");
	auto* innerSection  = new SectionWidget("Inner section");
	auto* content       = new QWidget;
	content->setObjectName("Content for section widget");
	auto* contentLayout = new QHBoxLayout;
	content->setLayout(contentLayout);
	contentLayout->addWidget(new QLabel("I am a label"));
	contentLayout->addWidget(new QLineEdit);

	innerSection->setContentWidget(content);
	sectionWidget->setContentWidget(innerSection);
	sectionWidget->setCheckable(true);
	sectionWidget->showHeaderLine(false);

	mainLayout->addSpacerItem(new QSpacerItem(20, 150, QSizePolicy::Expanding, QSizePolicy::Expanding));
	mainLayout->addWidget(switchButton);
	mainLayout->addWidget(sectionWidget);
	mainLayout->addSpacerItem(new QSpacerItem(20, 150, QSizePolicy::Expanding, QSizePolicy::Expanding));

	connect(switchButton, &QCheckBox::toggled, [this, sectionWidget](bool checked) {
		sectionWidget->setCheckable(checked);
	});
}

}  // namespace test