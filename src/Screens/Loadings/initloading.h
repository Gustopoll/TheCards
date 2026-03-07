#ifndef INITLOADING_H
#define INITLOADING_H

#include "src/Screens/screencontroller.h"
#include "src/Utils/datapreloader.h"
#include <QWidget>
#include <QFutureWatcher>

namespace Ui {
class InitLoading;
}

class InitLoading : public ScreenWidget
{
    Q_OBJECT

public:
    InitLoading(DataPreloader& dataPreloader, QWidget *parent = nullptr);
    ~InitLoading();

    void OnScreenActive() override;
    void OnScreenInactive() override;

private:
    Ui::InitLoading *ui;

    QFutureWatcher<void>* watcher;

    size_t _countPreloadedData = 0;
    size_t _countDataToPreload = 0;

    DataPreloader& _dataPreloader;
};

#endif // INITLOADING_H
