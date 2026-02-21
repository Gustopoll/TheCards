#include "datapreloader.h"

DataPreloader::DataPreloader() {}

void DataPreloader::LoadAll()
{
    for (auto& [name, data] : _preloadedImages)
    {
        for (const auto& path : data.paths)
        {
            auto& image = data.images.emplace_back();
            image->load(path.c_str());
        }
    }
}

void DataPreloader::PreloadImages(const std::string &name, const std::vector<std::string>& paths)
{
    _preloadedImages[name] = PreloadedImageData(paths, {});
}

std::vector<std::shared_ptr<QImage>> DataPreloader::GetPreloadedImages(const std::string& name)
{
    if (const auto& images = _preloadedImages.find(name);
        images != _preloadedImages.end())
    {
        return images->second.images;
    }
    return {};
}
