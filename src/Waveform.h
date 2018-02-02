
#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <vector>
#include <HISSTools_VecLib.hpp>
#include "IControl.h"

class Waveform : public IControl
{
    
public:
    
    Waveform(IPlugBaseGraphics& plug, HISSTools_VecLib *vecLib, double x, double y, double w, double h) : IControl(plug, IRECT(x, y, x + w, y + h)), mVecLib(vecLib), mCache(nullptr), mWaveformNeedsRedraw(false)
    {
        mData.resize(w * 2);
        SetSelect(0., 0.);
    }
    
    void OnMouseDown(float x, float y, const IMouseMod& mod) override;
    void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod& mod) override;
    
    void Draw(IGraphics& graphics) override;
    
    void Set(const float *data, int dataSize);
    void SetSelect(double L, double R);
    
private:
    
    double Normalise(float x) { return std::min(1.f, std::max(0.f, (x - mRECT.L) / mRECT.W())); }
    
    HISSTools_VecLib *mVecLib;
    std::vector<float> mData;
    double mSelectL;
    double mSelectR;
    double mClickedX;
    double mClickedY;
    double mEditWidth;
    bool mEditDrag;
    cairo_pattern_t* mCache;
    bool mWaveformNeedsRedraw;
};

#endif
