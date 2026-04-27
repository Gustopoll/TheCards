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

    using ImageLoadedEvent = EventHandler<
        //! Name of the group that image is loaded from.
        const std::string&,
        //! Path of the loaded image.
        const std::string&,
        //! True when the image is succesfully loaded otherwise false.
        bool>;

    using ImageLoadingFinishedEvent = EventHandler<
        //! Name of the group that all the images is loaded from.
        //! Empty string when all the images are loaded.
        const std::string&>;

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

    //! Gets the size of the images to preload.
    size_t GetPreloadedImagesCount();

    ImageLoadedEvent::Subscriber& GetImageLoadedEvent()
    {
        return _imageLoadedEvent.GetSubscriber();
    }

    ImageLoadingFinishedEvent::Subscriber& GetImageLoadingFinishedEvent()
    {
        return _imageLoadingFinishedEvent.GetSubscriber();
    }
private:
    ImageLoadedEvent _imageLoadedEvent;
    ImageLoadingFinishedEvent _imageLoadingFinishedEvent;

    std::unordered_map<std::string, PreloadedImageData> _preloadedImages;
};

#endif // DATAPRELOADER_H
