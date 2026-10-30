#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>

class ScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenWidget(QWidget* parent = nullptr)
        : QWidget(parent)
    {}

    virtual ~ScreenWidget() override = default;

    //! Called when screen becomes active.
    virtual void OnScreenActive() = 0;

    //! Called when screen is no longer active.
    virtual void OnScreenInactive() = 0;
};

#endif // SCREENWIDGET_H
