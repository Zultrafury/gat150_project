#pragma once

#include "Resource.h"
#include "Core/Singleton.h"
#include <map>
#include <iostream>
#include "Engine.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
    void RenderBind(SDL_Renderer* _r);
    void RenderGet(SDL_Renderer*& _r);

    void ASBind(FMOD::System* _r, FMOD::ChannelGroup* group);
    void ASGet(FMOD::System*& _r, FMOD::ChannelGroup*& group);

    
    template<typename T, typename ... TArgs>
    res_t<T> Get(const std::string& name, TArgs ... args);
    template<typename T, typename ... TArgs>
    res_t<T> GetR(const std::string& name, TArgs ... args);
    template<typename T, typename ... TArgs>
    res_t<T> GetS(const std::string& name, TArgs ... args);
    
 
    friend class Singleton;
 
protected:
    ResourceManager() = default;
 
private:
    SDL_Renderer* rm_renderer;
    FMOD::System* rm_as;
    FMOD::ChannelGroup* rm_asg;
    std::map<std::string, res_t<Resource>> m_resources;
};

inline void ResourceManager::RenderBind(SDL_Renderer* _r)
{
    rm_renderer = _r;
}
inline void ResourceManager::RenderGet(SDL_Renderer*& _r)
{
    _r = rm_renderer;
}

inline void ResourceManager::ASBind(FMOD::System* _r, FMOD::ChannelGroup* group)
{
    rm_as = _r; rm_asg = group;
}
inline void ResourceManager::ASGet(FMOD::System*& _r, FMOD::ChannelGroup*& group)
{
    _r = rm_as; group = rm_asg;
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
    if (!resource->Create(name, args... , rm_renderer))
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
inline res_t<T> ResourceManager::GetS(const std::string& name, TArgs ... args)
{
    
    // find resource in resource manager
    if (m_resources.find(name) != m_resources.end())
    {
        // return resource
        return std::dynamic_pointer_cast<T>(m_resources[name]);
    }
 
    // resource not found, create resource
    res_t<T> resource = std::make_shared<T>();
    if (!resource->Create(name, args... , rm_as, rm_asg))
    {
        // resource not created
        std::cerr << "Could not create resource: " << name << std::endl;
        return res_t<T>();
    }
 
    // add resource to resource manager
    m_resources[name] = resource;
 
    return resource;
}