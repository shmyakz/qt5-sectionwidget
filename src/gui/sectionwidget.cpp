#include "sectionwidget.h"

#include <QBoxLayout>
#include <QGroupBox>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QStyleOptionToolButton>
#include <QToolButton>

namespace {

void clearLayout(QLayout* layout)
{
	if (!layout)
		throw std::runtime_error("provided layout is nullptr");

	if (layout->isEmpty())
		return;

	QLayoutItem* child;
	while ((child = layout->takeAt(0)) != nullptr) {
		delete child->widget();
		delete child;
	}
}

}  // namespace

namespace test {

SectionWidget::SectionWidget(const QString& title, QWidget* parent):
	QWidget{parent},
	isCheckable_{false},
	animationDurationInMsecs_{300},
	content_{nullptr}
{
	auto* mainLayout   = new QVBoxLayout(this);
	auto* headerLayout = new QHBoxLayout;
	animations_        = new QParallelAnimationGroup(this);

	indicator_  = new CheckableToolButton(this);
	headerLine_ = new QFrame(this);
	headerLine_->setFrameStyle(QFrame::HLine);
	indicator_->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	indicator_->setStyleSheet("border:none;");
	indicator_->setCheckable(true);
	indicator_->setArrowType(Qt::RightArrow);
	indicator_->setText(title);

	headerLayout->addWidget(indicator_, 0, Qt::AlignLeft);
	headerLayout->addWidget(headerLine_);
	headerLayout->setSpacing(0);

	contentContainer_ = new QFrame(this);
	contentContainer_->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
	contentContainer_->setLayout(new QVBoxLayout);
	contentContainer_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	mainLayout->addLayout(headerLayout, Qt::AlignLeft);
	mainLayout->addWidget(contentContainer_);

	connect(indicator_, &QToolButton::toggled, [&](bool checked) {
		updateIndicatorType(checked);
		if (!content_)
			return;

		if (checked) {
			expand();
		}
		else {
			collapse();
		}
	});
}

QString SectionWidget::title() const
{
	return indicator_->text();
}

QWidget* SectionWidget::widget() const
{
	return content_;
}

bool SectionWidget::isAnimationUsed() const
{
	return animationDurationInMsecs_ == 0;
}

int SectionWidget::animationDuration() const
{
	return animationDurationInMsecs_;
}

bool SectionWidget::isCheckable() const
{
	return isCheckable_;
}

void SectionWidget::setTitle(const QString& title)
{
	indicator_->setText(title);
}

void SectionWidget::setContentWidget(QWidget* content)
{
	if (!content)
		throw std::runtime_error("received nullptr content");

	content_ = content;
	clearLayout(contentContainer_->layout());
	contentContainer_->layout()->addWidget(content);

	animations_->stop();
	animations_->clear();

	auto* animation = new QPropertyAnimation(contentContainer_, "maximumHeight");
	animation->setStartValue(0);
	animation->setEndValue(content_->geometry().height() + 10);
	animation->setEasingCurve(QEasingCurve::InOutQuad);
	animation->setDuration(animationDurationInMsecs_);
	animations_->addAnimation(animation);

	if (!indicator_->isChecked()) {
		contentContainer_->setMaximumHeight(0);
	}
}

void SectionWidget::setAnimationEnabled(bool enabled)
{
	for (auto i = 0; i < animations_->animationCount(); ++i) {
		auto* animation = qobject_cast<QPropertyAnimation*>(animations_->animationAt(i));
		if (!animation)
			throw std::runtime_error("failed to cast animation to QPropertyAnimation");
		animation->setDuration(enabled ? animationDurationInMsecs_ : 0);
	}
}

void SectionWidget::setAnimationDuration(int msec)
{
	for (auto i = 0; i < animations_->animationCount(); ++i) {
		auto* animation = qobject_cast<QPropertyAnimation*>(animations_->animationAt(i));
		if (!animation)
			throw std::runtime_error("failed to cast animation to QPropertyAnimation");
		animation->setDuration(msec);
	}
	animationDurationInMsecs_ = msec;
}

void SectionWidget::setCheckable(bool checkable)
{
	if (isCheckable_ == checkable)
		return;

	isCheckable_ = checkable;
	indicator_->setShowCheckbox(checkable);
}

void SectionWidget::showHeaderLine(bool show)
{
	headerLine_->setVisible(show);
}

void SectionWidget::expand()
{
	animations_->setDirection(QAbstractAnimation::Forward);
	animations_->start();
}

void SectionWidget::collapse()
{
	animations_->setDirection(QAbstractAnimation::Backward);
	animations_->start();
}

void SectionWidget::updateIndicatorType(bool checked)
{
	indicator_->setArrowType(checked ? Qt::DownArrow : Qt::RightArrow);
}

}  // namespace test