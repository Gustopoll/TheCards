#include "loadingscreen.h"
#include "ui_loadingscreen.h"

#include "src/Utils/assets.h"
#include "src/Screens/MainScreen/mainscreen.h"

#include <QtConcurrent>

LoadingScreen::LoadingScreen(DataPreloader& dataPreloader, MainScreen *parent)
    : QMainWindow(reinterpret_cast<QMainWindow*>(parent))
    , ui(new Ui::LoadingScreen)
    , _dataPreloader(dataPreloader)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);

    watcher = new QFutureWatcher<void>();
    _countPreloadedData = 0;
    _countDataToPreload = _dataPreloader.GetPreloadedImagesCount();
    ui->progressBar->setValue(_countPreloadedData);
    ui->progressBar->setMaximum(_countDataToPreload);

    connect(
        watcher,
        &QFutureWatcher<void>::finished,
        this,
        [parent]()
        {
            parent->OnLoadingFinished();
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
            ui->progressBar->setValue(_countPreloadedData);
            ui->textLoading->setText(text);
        });

    watcher->setFuture(QtConcurrent::run(
        [this]()
        {
            _dataPreloader.LoadAll();
        }));
}

LoadingScreen::~LoadingScreen()
{
    delete ui;
}

void LoadingScreen::on_closeButton_clicked()
{
    exit(0);
}

