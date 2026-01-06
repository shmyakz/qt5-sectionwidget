#pragma once

#include <QPainter>
#include <QStyleOptionToolButton>
#include <QToolButton>
#include <QWidget>

class QFrame;
class QParallelAnimationGroup;

namespace test {

class CheckableToolButton final : public QToolButton {
	Q_OBJECT
public:
	explicit CheckableToolButton(QWidget* parent = nullptr):
		QToolButton(parent),
		showCheckbox_{false}
	{
	}

	void setShowCheckbox(bool on)
	{
		if (showCheckbox_ == on)
			return;
		showCheckbox_ = on;
		update();
	}

protected:
	void paintEvent(QPaintEvent* event) override
	{
		QPainter painter(this);

		QStyleOptionToolButton styleOption;
		initStyleOption(&styleOption);
		style()->drawComplexControl(QStyle::CC_ToolButton, &styleOption, &painter, this);

		if (!showCheckbox_)
			return;

		QStyleOptionButton checkBox;
		checkBox.state = QStyle::State_Enabled;
		if (isChecked())
			checkBox.state |= QStyle::State_On;
		else
			checkBox.state |= QStyle::State_Off;

		const int indicatorWidth = style()->pixelMetric(QStyle::PM_IndicatorWidth, nullptr, this);
		checkBox.rect            = QRect(0, (height() - indicatorWidth) / 2, indicatorWidth, indicatorWidth);

		style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &checkBox, &painter, this);
	}

private:
	bool showCheckbox_;
};

class SectionWidget final : public QWidget {
	Q_OBJECT
public:
	explicit SectionWidget(const QString& title, QWidget* parent = nullptr);

public:
	QString title() const;

	QWidget* widget() const;

	bool isAnimationUsed() const;

	int animationDuration() const;

	bool isCheckable() const;

public:
	void setTitle(const QString& title);

	void setContentWidget(QWidget* content);

	void setAnimationEnabled(bool enabled);

	void setAnimationDuration(int msec);

	void setCheckable(bool checkable);

	void showHeaderLine(bool show);

public slots:
	void expand();

	void collapse();

private:
	CheckableToolButton*     indicator_;
	QFrame*                  headerLine_;
	QWidget*                 content_;
	QFrame*                  contentContainer_;
	QParallelAnimationGroup* animations_;

	bool isCheckable_;
	int  animationDurationInMsecs_;

private:
	void updateIndicatorType(bool checked);
};

}  // namespace test