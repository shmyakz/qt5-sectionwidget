# qt5-sectionwidget

Just another section widget implementation using Qt5

Class `SectionWidget` provides a widget that holds another widget, like `QGroupBox`, with exception that it hides or
shows it in frame when clicked with simple animation.

Requirements:

- Qt5.12 or newer;
- C++17 or newer.

Options:

- Show or hide header line;
- Change title text;
- Change animation duration;
- Change `isCheckable` status to change section indicator from arrow to checkbox;

Usage:

```c++
auto* sectionWidget = new SectionWidget("This is title text", parentWidget);
auto* contentWidget = new QWidget;
auto* contentLayout = new QVBoxLayout(contentWidget);
contentLayout->addWidget(new QLabel("I am content label 1"));
contentLayout->addWidget(new QLabel("I am content label 2"));

sectionWidget->setContentWidget(contentWidget);
```