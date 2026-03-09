#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include "src/Screens/Dialogs/infodialog.h"
#include "src/Screens/stylesheetcontroller.h"

#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>
#include <unordered_map>
#include <memory>
#include <functional>

enum class ScreenState
{
    Main,
    Game,
    Settings
};

struct ScreenStateHash
{
    std::size_t operator()(const ScreenState& screen) const noexcept
    {
        return std::hash<int>()(static_cast<int>(screen));
    }
};

class ScreenWidget : public QWidget
{
public:
    ScreenWidget(QWidget* parent)
        : QWidget(parent)
    {};

    //! Calls when screen became active.
    virtual void OnScreenActive() = 0;

    //! Calls when screen is no longer active.
    virtual void OnScreenInactive() = 0;
};

class ScreenController : public QObject
{
public:
    //! Returns the singleton instance of the ScreenController.
    static ScreenController& Get();

    //! Initializes the screen controller.
    //! Must be called before using other methods.
    //!
    //! @param mainWidget Main widget of whole application.
    //! @param stackedWidget Widget where all screens are.
    void Initialize(QWidget* mainWidget, QStackedWidget* stackedWidget);

    //! Creates a new screen after the controller has been initialized.
    //!
    //! @param screen Screen state associated with the given widget.
    //! @param widget Widget that represet whole screen.
    //! @retval true if screen is created.
    //! @retval false if the ScreenController is not initialized or
    //!               the screen already exists or
    //!               the widget is null.
    bool CreateScreen(ScreenState screen, ScreenWidget* widget);

    //! Shows the widget based on given screen state.
    //!
    //! @param screen State of the screen to be displayed.
    //! @retval true if scene is shown.
    //! @retval false if the ScreenController is not initialized or
    //!               the screen does not exists.
    bool ShowScreen(ScreenState screen);

    //! Shows the warning dialog in top left corenr.
    //!
    //! @param text Text to be displayed.
    void ShowWarningDialog(const QString& text);

    //! Cleans the screens.
    void CleanAll();

private:
    void OnUpdate();

    QTimer* _timer = nullptr;

    bool _initialized = false;

    //! Maps screen names to their corresponding indexes in the QStackedWidget.
    std::unordered_map<ScreenState, int, ScreenStateHash> _screenIndexes;

    QWidget* _mainWidget = nullptr;
    QStackedWidget* _stackedWidget = nullptr;

    //! All currectly shown informational dialogs.
    std::vector<std::shared_ptr<InfoDialog>> _infoDialog;

    //! Collection of all positions of info dialog to delete next update (in OnUpdate).
    std::vector<uint32_t> _infoDialogToDelete;

    StyleSheetController _styleSheetController;
};

#endif // SCREENCONTROLLER_H
