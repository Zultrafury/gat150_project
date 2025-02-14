﻿#pragma once
#include <vector>

#include "Renderer/Texture.h"
#include "Resources/Resource.h"

class Sprite
{
public:
    int currentframe = 0;
    int frametimer = -1;
    int fps = 1;
    bool loop = true;
    
    ~Sprite()
    {
        
    }
    Sprite() = default;
    Sprite(res_t<Texture> tex, int frames, int _fps, bool _loop)
    {
        m_texture = tex;
        fps = _fps;
        loop = _loop;

        int width, height;
        SDL_QueryTexture(m_texture->m_texture, nullptr, nullptr, &width, &height);

        frames = std::max(frames,1);
        int framesize = width/frames;
        for (int i = 0; i < frames; ++i)
        {
            m_slices.push_back(SDL_Rect{ i*framesize, 0 ,framesize, height });
        }
    }

    void SetTexture(res_t<Texture> texture) { m_texture = texture; }
    
    void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale)
    {
        //Timing
        if (fps > 0)
        {
            frametimer++;
            if (frametimer >= fps)
            {
                frametimer = 0;
                currentframe++;
                if (currentframe > m_slices.size()-1)
                {
                    if (loop)
                    {
                        currentframe = 0;
                    }
                    else {
                        currentframe =  m_slices.size()-1;
                    }
                }
            }
        }
        
        //Prepare current frame for render
        SDL_Rect srect = m_slices[currentframe];

        SDL_Rect srcrect {
            srect.x,srect.y,
            srect.w, srect.h
        };
        SDL_FRect rect {
            static_cast<float>(x) - static_cast<float>(srect.w * scale)/2,
            static_cast<float>(y) - static_cast<float>(srect.h * scale)/2,
            static_cast<float>(srect.w * scale), static_cast<float>(srect.h * scale)
        };
        
        // copy the texture onto the renderer
        SDL_RenderCopyExF(renderer,m_texture->m_texture,&srcrect,&rect,rotation,NULL,SDL_FLIP_NONE);
    }

private:
    std::vector<SDL_Rect> m_slices;
    res_t<Texture> m_texture{nullptr};
};
