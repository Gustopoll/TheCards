#include "initloading.h"
#include "ui_initloading.h"

#include <QtConcurrent>

namespace
{

constexpr char kCardGroup[] = "CardGroup";

}

InitLoading::InitLoading(DataPreloader& dataPreloader, QWidget *parent)
    : ScreenWidget(parent)
    , ui(new Ui::InitLoading)
    , _dataPreloader(dataPreloader)
{
    ui->setupUi(this);

    watcher = new QFutureWatcher<void>();

    connect(
        watcher,
        &QFutureWatcher<void>::finished,
        this,
        []()
        {
            ScreenController::Get().ShowScreen(ScreenState::Game);
        });

    _dataPreloader.GetImageLoadedEvent().Subscribe(
        [this](const std::string& groupName, const std::string& path, const bool isLoaded)
        {
            Q_UNUSED(groupName);
            ++_countPreloadedData;

            if (!isLoaded)
            {
                qDebug() << "Failed to load image '" << path << "'.";
            }

            const auto text = QString::fromStdString(std::format("Loading data ... [{}/{}] {}",
                _countPreloadedData,
                _countDataToPreload,
                path));

            qDebug() << text;
            ui->textLoading->setText(text);
        });

}

InitLoading::~InitLoading()
{
    delete ui;
}

void InitLoading::OnScreenActive()
{
    _countDataToPreload = _dataPreloader.GetPreloadedImagesCount(kCardGroup);
    _countPreloadedData = 0;

    watcher->setFuture(QtConcurrent::run([this]()
    {
        _dataPreloader.LoadImageGroup(kCardGroup);
    }));
}

void InitLoading::OnScreenInactive()
{

}
