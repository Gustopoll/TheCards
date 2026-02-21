#include "initloading.h"
#include "ui_initloading.h"

InitLoading::InitLoading(DataPreloader& dataPreloader, QWidget *parent)
    : ScreenWidget(parent)
    , ui(new Ui::InitLoading)
    , _dataPreloader(dataPreloader)
{
    ui->setupUi(this);
}

InitLoading::~InitLoading()
{
    delete ui;
}

void InitLoading::OnScreenActive()
{

}

void InitLoading::OnScreenInactive()
{

}
