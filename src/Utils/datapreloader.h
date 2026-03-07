#ifndef DATAPRELOADER_H
#define DATAPRELOADER_H

#include "src/Utils/eventhandler.h"

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

    using LoadedImageEvent = EventHandler<
        //! Name of the group that image is loaded from.
        std::string,
        //! Path of the loaded image.
        std::string>;

    using AllImagesLoadedEvent = EventHandler<
        //! Name of the group that all the images is loaded from.
        //! Emtpty string when all the images are loaded.
        std::string>;

public:
    DataPreloader();

    void LoadAll();

    //! Loads all the images from given group.
    //! @param groupName Name of the group.
    void LoadImageGroup(const std::string& groupName);

    //! Preloads the image data.
    //! @param name Group name of the data to preload.
    //! @param paths Paths to the images to preload.
    void PreloadImages(const std::string& groupName, const std::vector<std::string>& paths);

    //! Gets all the preloaded images by the group name.
    std::vector<std::shared_ptr<QImage>> GetPreloadedImages(const std::string& groupName);

    LoadedImageEvent::Subscriber& GetLoadedImageEvent()
    {
        return _loadedImageEvent.GetSubscriber();
    }

    AllImagesLoadedEvent::Subscriber& GetAllImagesLoadedEvent()
    {
        return _allImagesLoadedEvent.GetSubscriber();
    }
private:
    LoadedImageEvent _loadedImageEvent;
    AllImagesLoadedEvent _allImagesLoadedEvent;

    std::unordered_map<std::string, PreloadedImageData> _preloadedImages;
};

#endif // DATAPRELOADER_H
