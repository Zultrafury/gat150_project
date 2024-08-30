#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <Math/Vector2.h>

#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Framework/Actor.h"
#include "Input/FRead.h"
#include "Resources/ResourceManager.h"

#define READ_DATA(value, data) Json::Read(value, #data, data)

namespace Json
{
    inline bool Load(const std::string& filename, rapidjson::Document& document)
    {
        // convert the string into a json stream
        std::stringstream stream(FRead::ReadFile(filename));
        rapidjson::IStreamWrapper istream(stream);

        // set the json document from the stream
        document.ParseStream(istream);
        // check if the parse was successful
        if (!document.IsObject())
        {
            std::cerr << "Could not parse Json: " << filename << '\n';
            return false;
        }

        return true;
    }
    
    inline bool Read(const rapidjson::Value& value, const std::string& name, int& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()))
        {
            std::cerr << "Could not read Json value: " << name << '\n';
            return false;
        }

        data = value[name.c_str()].GetInt();
        
        return true;
    }

    inline bool Read(const rapidjson::Value& value, const std::string& name, float& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()))
        {
            std::cerr << "Could not read Json value: " << name << '\n';
            return false;
        }

        data = value[name.c_str()].GetFloat();
        
        return true;
    }
    
    inline bool Read(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()))
        {
            std::cerr << "Could not read Json value: " << name << '\n';
            return false;
        }

        data = value[name.c_str()].GetBool();
        
        return true;
    }

    inline bool Read(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()))
        {
            std::cerr << "Could not read Json value: " << name << '\n';
            return false;
        }

        data = value[name.c_str()].GetString();
        
        return true;
    }

    inline bool Read(const rapidjson::Value& value, const std::string& name, FVector2& data)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            switch(i)
            {
            case 0:
                data.x = array[i].GetFloat(); break;
            case 1:
                data.y = array[i].GetFloat(); break;
            }
        }

        return true;
    }

    inline bool Read(const rapidjson::Value& value, const std::string& name, SDL_Color& data)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            switch(i)
            {
            case 0:
                data.r = array[i].GetInt(); break;
            case 1:
                data.g = array[i].GetInt(); break;
            case 2:
                data.b = array[i].GetInt(); break;
            case 3:
                data.a = array[i].GetInt(); break;
            }
        }

        return true;
    }

    inline bool Read(const rapidjson::Value& value, const std::string& name, std::vector<Component*>& data)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsObject())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }
            
            std::string ctype = array[i].GetObject()["type"].GetString();
            if (ctype == "SpriteComponent")
            {
                std::string link = array[i].GetObject()["texture"].GetString();
                res_t<Texture> tex = ResourceManager::Instance().Get<Texture>(link);

                int frames = array[i].GetObject()["frames"].GetInt();
                int fps = array[i].GetObject()["fps"].GetInt();
                data.push_back(new SpriteComponent(tex,frames,fps));
            }
            else if (ctype == "TextComponent")
            {
                std::string link = array[i].GetObject()["font"].GetString();
                int size = array[i].GetObject()["fontsize"].GetInt();
                res_t<Font> font = ResourceManager::Instance().Get<Font>(link,size);

                std::string text = array[i].GetObject()["text"].GetString();
                SDL_Color color;
                READ_DATA(array[i], color);
                data.push_back(new TextComponent(font,text,color));
            }
        }

        return true;
    }
}