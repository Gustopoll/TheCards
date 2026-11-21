#include "loadingscreen.h"
#include "ui_loadingscreen.h"

#include "src/Screens/MainScreen/mainscreen.h"

#include <QtConcurrent>

LoadingScreen::LoadingScreen(DataPreloader& dataPreloader, MainScreen *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoadingScreen)
    , _dataPreloader(dataPreloader)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);

    watcher = new QFutureWatcher<void>(this);
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

    _imageLoadedSubId = _dataPreloader.GetImageLoadedEvent().Subscribe(
        [this](const std::string& groupName, const std::string& path, const bool isLoaded)
        {
            Q_UNUSED(groupName);
            const size_t count = ++_countPreloadedData;

            if (!isLoaded)
            {
                qDebug() << "Failed to load image '" << path << "'.";
            }

            const auto text = QString::fromStdString(std::format("Loading data ... [{}/{}] {}",
                count,
                _countDataToPreload,
                path));

            qDebug() << text;

            // Fire onto the main thread – this callback runs in a QtConcurrent worker thread.
            QMetaObject::invokeMethod(this, [this, count, text]()
            {
                ui->progressBar->setValue(count);
                ui->textLoading->setText(text);
            }, Qt::QueuedConnection);
        });

    watcher->setFuture(QtConcurrent::run(
        [this]()
        {
            _dataPreloader.LoadAll();
        }));
}

LoadingScreen::~LoadingScreen()
{
    _dataPreloader.GetImageLoadedEvent().Unsubscribe(_imageLoadedSubId);
    delete ui;
}

void LoadingScreen::on_closeButton_clicked()
{
    qApp->quit();
}
