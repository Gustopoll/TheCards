#ifndef DATAPRELOADER_H
#define DATAPRELOADER_H

#include <QImage>

#include <unordered_map>
#include <string>

class DataPreloader
{
    struct PreloadedImageData
    {
        std::vector<std::string> paths;
        std::vector<std::shared_ptr<QImage>> images;
    };

public:
    DataPreloader();

    void LoadAll();

    //! Preloads the image data.
    //! @param name Name of the data to preload.
    //! @param paths Paths to the images to preload.
    void PreloadImages(const std::string& name, const std::vector<std::string>& paths);

    std::vector<std::shared_ptr<QImage>> GetPreloadedImages(const std::string& name);
private:

    std::unordered_map<std::string, PreloadedImageData> _preloadedImages;
};

#endif // DATAPRELOADER_H
