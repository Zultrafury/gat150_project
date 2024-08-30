#pragma once

#include "Resource.h"
#include "Core/Singleton.h"
#include <map>
#include <iostream>
 
class ResourceManager : public Singleton<ResourceManager>
{
public:
    void RenderBind(SDL_Renderer* _r);
    
    template<typename T, typename ... TArgs>
    res_t<T> Get(const std::string& name, TArgs ... args);
    template<typename T, typename ... TArgs>
    res_t<T> GetR(const std::string& name, TArgs ... args);
 
    friend class Singleton;
 
protected:
    ResourceManager() = default;
 
private:
    SDL_Renderer* rm_renderer;
    std::map<std::string, res_t<Resource>> m_resources;
};

inline void ResourceManager::RenderBind(SDL_Renderer* _r)
{
    rm_renderer = _r;
}

template<typename T, typename ... TArgs>
inline res_t<T> ResourceManager::Get(const std::string& name, TArgs ... args)
{
    // find resource in resource manager
    if (m_resources.find(name) != m_resources.end())
    {
        // return resource
        return std::dynamic_pointer_cast<T>(m_resources[name]);
    }
 
    // resource not found, create resource
    res_t<T> resource = std::make_shared<T>();
    if (!resource->Create(name, args...))
    {
        // resource not created
        std::cerr << "Could not create resource: " << name << std::endl;
        return res_t<T>();
    }
 
    // add resource to resource manager
    m_resources[name] = resource;
 
    return resource;
}

template<typename T, typename ... TArgs>
inline res_t<T> ResourceManager::GetR(const std::string& name, TArgs ... args)
{
    
    // find resource in resource manager
    if (m_resources.find(name) != m_resources.end())
    {
        // return resource
        return std::dynamic_pointer_cast<T>(m_resources[name]);
    }
 
    // resource not found, create resource
    res_t<T> resource = std::make_shared<T>();
    if (!resource->Create(name, rm_renderer, args...))
    {
        // resource not created
        std::cerr << "Could not create resource: " << name << std::endl;
        return res_t<T>();
    }
 
    // add resource to resource manager
    m_resources[name] = resource;
 
    return resource;
}