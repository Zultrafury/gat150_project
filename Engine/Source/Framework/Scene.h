#pragma once
#include <vector>
#include <rapidjson/document.h>

#include "Core/Json.h"
#include "Resources/Resource.h"

class Scene
{
public:
    std::vector<res_t<Resource>> Components;
    

    bool Initialize(std::string filename, rapidjson::Document document)
    {
        Json::Load(filename, document);
        return false;
    }
};
