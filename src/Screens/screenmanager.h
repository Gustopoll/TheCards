#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "src/Screens/screenwidget.h"

#include <QObject>
#include <QStackedWidget>
#include <unordered_map>
#include <vector>
#include <optional>

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

class ScreenManager : public QObject
{
    Q_OBJECT
public:
    explicit ScreenManager(QObject* parent = nullptr);
    ~ScreenManager() override = default;

    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;

    //! Initializes the screen manager.
    //! Must be called before using other methods.
    //! @param mainWidget Main widget of whole application.
    //! @param stackedWidget Widget where all screens are.
    void Initialize(QWidget* mainWidget, QStackedWidget* stackedWidget);

    //! Creates a new screen after the manager has been initialized.
    //! @param screen Screen state associated with the given widget.
    //! @param widget Widget that represents the screen.
    //! @retval true if screen is created.
    //! @retval false if the ScreenManager is not initialized or
    //!               the screen already exists or
    //!               the widget is null.
    bool CreateScreen(ScreenState screen, ScreenWidget* widget);

    //! Shows the widget based on given screen state.
    //! @param screen State of the screen to be displayed.
    //! @param recordHistory Whether to save the previous screen to back history.
    //! @retval true if scene is shown.
    //! @retval false if the ScreenManager is not initialized or
    //!               the screen does not exist.
    bool ShowScreen(ScreenState screen, bool recordHistory = true);

    //! Navigates to the previously displayed screen.
    //! @retval true if navigation succeeded.
    //! @retval false if no history is available.
    bool GoBack();

    //! Gets the currently active screen state.
    std::optional<ScreenState> GetCurrentScreen() const { return _currentScreen; }

    //! Cleans up all screens.
    void CleanAll();

private:
    bool _initialized = false;

    //! Maps screen states to their corresponding indexes in the QStackedWidget.
    std::unordered_map<ScreenState, int, ScreenStateHash> _screenIndexes;

    //! History for navigation.
    std::vector<ScreenState> _history;

    //! Current screen.
    std::optional<ScreenState> _currentScreen;

    QWidget* _mainWidget = nullptr;
    QStackedWidget* _stackedWidget = nullptr;
};

#endif // SCREENMANAGER_H
