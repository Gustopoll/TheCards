#include "datapreloader.h"

#include <QImage>

DataPreloader::DataPreloader() {}

void DataPreloader::LoadAll()
{
    for (auto& [groupName, data] : _preloadedImages)
    {
        if (!data.images.empty())
        {
            // Group is already loaded.
            continue;
        }

        for (const auto& path : data.paths)
        {
            auto& image = data.images.emplace_back(std::make_shared<QImage>());
            bool isLoaded = image->load(path.c_str());
            _imageLoadedEvent.Fire(groupName, path, isLoaded);
        }

        _imageLoadingFinishedEvent.Fire(groupName);
    }

    // Pass emptry string to indicate that all the images are loaded.
    _imageLoadingFinishedEvent.Fire("");
}

void DataPreloader::LoadImageGroup(const std::string& groupName)
{
    auto groupIter = _preloadedImages.find(groupName);
    if (groupIter == _preloadedImages.end())
    {
        return;
    }

    auto& group = groupIter->second;
    if (!group.images.empty())
    {
        // Images are already loaded.
        _imageLoadingFinishedEvent.Fire(groupName);
        return;
    }

    for (const auto& path : groupIter->second.paths)
    {
        auto& image = groupIter->second.images.emplace_back(std::make_shared<QImage>());
        bool isLoaded = image->load(path.c_str());
        _imageLoadedEvent.Fire(groupName, path, isLoaded);
    }

    _imageLoadingFinishedEvent.Fire(groupName);
}

void DataPreloader::PreloadImages(const std::string& groupName, const std::vector<std::string>& paths)
{
    _preloadedImages[groupName] = PreloadedImageData(paths, {});
}

std::vector<std::shared_ptr<QImage>> DataPreloader::GetPreloadedImages(const std::string& groupName)
{
    if (const auto& images = _preloadedImages.find(groupName);
        images != _preloadedImages.end())
    {
        return images->second.images;
    }
    return {};
}

size_t DataPreloader::GetPreloadedImagesCount()
{
    size_t totalCount = 0;
    for (const auto& item : _preloadedImages)
    {
        totalCount += item.second.paths.size();
    }

    return totalCount;
}
