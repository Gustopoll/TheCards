#ifndef STYLESHEETCONTROLLER_H
#define STYLESHEETCONTROLLER_H

#include <QString>
#include <unordered_map>

constexpr char kStyleInformationalDialogPath[] = "Data/Styles/InfoDialog.qss";

class StyleSheetController
{
public:
    StyleSheetController();

    //! Gets the style sheet based on file path.
    //!
    //! @param path Path to the file.
    //! @retval 'Style sheet' If file exists on the given path.
    //! @retval 'Empty string' Otherwise.
    const QString GetStyleSheet(const QString& path);

private:

    //! Stored previously loaded style sheets.
    std::unordered_map<std::string, QString> _cache;
};

#endif // STYLESHEETCONTROLLER_H
