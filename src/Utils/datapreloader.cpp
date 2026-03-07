#include "datapreloader.h"

DataPreloader::DataPreloader() {}

void DataPreloader::LoadAll()
{
    for (auto& [groupName, data] : _preloadedImages)
    {
        for (const auto& path : data.paths)
        {
            auto& image = data.images.emplace_back();
            image->load(path.c_str());
            _loadedImageEvent.Fire(groupName, path);
        }

        _allImagesLoadedEvent.Fire(groupName);
    }

    // Pass emptry string to indicate that all the images are loaded.
    _allImagesLoadedEvent.Fire("");
}

void DataPreloader::LoadImageGroup(const std::string& groupName)
{
    auto groupIter = _preloadedImages.find(groupName);
    if (groupIter == _preloadedImages.end())
        return;

    auto& group = groupIter->second;
    if (!group.images.empty())
    {
        // Images are already loaded.
        return;
    }

    for (const auto& path : groupIter->second.paths)
    {
        auto& image = groupIter->second.images.emplace_back();
        image->load(path.c_str());
        _loadedImageEvent.Fire(groupName, path);
    }

    _allImagesLoadedEvent.Fire(groupName);
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
