
/* Copyright (c) 2006-2007, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#ifndef EQ_VOL_CHANNEL_H
#define EQ_VOL_CHANNEL_H

#include "eVolve.h"

#include "rawVolModel.h"

#include <eq/eq.h>


namespace eVolve
{

    class FrameData;
    class InitData;

    class Channel : public eq::Channel
    {
    public:
        Channel();
        bool _perspective; // perspective/ortogonal projection

    protected:
        virtual ~Channel() {}

        virtual bool configInit( const uint32_t initID );
        virtual void frameDraw( const uint32_t frameID );

        virtual void frameAssemble( const uint32_t frameID );
        virtual void setupAssemblyState();
        virtual void frameReadback( const uint32_t frameID );

        void arrangeFrames( std::vector<Range>& ranges );

        void applyFrustum() const;

        void clearViewport( const PixelViewport &pvp );

        void frameClear( const uint32_t frameID );


    private:

        void _clearPixelViewPorts(  const vector<Image*>& vecImages,
                                    const vmml::Vector2i& offset        );

        void _drawLogo();

        void _calcMVandITMV( vmml::Matrix4d& modelviewM, 
                             vmml::Matrix3d& modelviewITM ) const;

        const FrameData& _getFrameData() const;

        //
        struct curFrData
        {
            uint32_t            frameID;
            eq::PixelViewport   pvp; 
            Range               lastRange;
        }
            _curFrData;

        vmml::Vector4f _bgColor;
        
        Image _curFrameImage; //!< buffer for readback in case of DB compositing

        Model*   _model;      //!< equal to RawVolume Model

        GLuint _tex3D;
        GLuint _preintName;
        GLuint _vertexID;     //!< display list for hexagonals or quads
        int    _angle;

        uint32_t _prvNumberOfSlices; //!< N of slices to update display list
    };

}

#endif // EQ_VOL_CHANNEL_H

