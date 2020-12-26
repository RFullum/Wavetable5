/*
  ==============================================================================

    FilterSection.h
    Created: 30 Apr 2020 6:33:55pm
    Author:  B150987

  ==============================================================================
*/

#pragma once


/// Creates a -12dB/octave Low Pass Filter by cascading two IIRFilter Low Pass Filters
class TwoPoleLPF
{
public:
    /// Destructor
    virtual ~TwoPoleLPF()
    {
        
    }
    
    /// Sets sampleRate of filters and resets
    virtual void setSampleRate(float SR)
    {
        sampleRate = SR;
        
        lowPass1.reset();
        lowPass2.reset();
    }
    
    /**
     takes current note frequency, cutoff frequency, resonance, input sample value, envelope value, envelop to Cutoff
     amount, and envelope to resonance amount.
     Returns keytracked low pass sample value
     */
    virtual float processFilter(float noteFreq, float cutoff,
                                std::atomic<float>* res, float sampleIn, float envVal,
                                std::atomic<float>* amtToCO, std::atomic<float>* amtToRes,
                                float lfoVal, std::atomic<float>* amtToLFO)
    {
        keyMap(noteFreq, cutoff);
        
        envelopeVal = envVal;
        cutoffSend = amtToCO;
        resSend = amtToRes;
        
        lfoValue = lfoVal;
        lfoSend = amtToLFO;
        
        resonance = *res;
        inputSample = sampleIn;
        
        return process();
    }
    
protected:
    /// Keytracking value mapping
    void keyMap(float frqncy, float CO)
    {
        float cutoffPos = CO;
        cutoffFreq = jmap(cutoffPos, 1.0f, 100.0f, frqncy, maxCutoff);
    }
    
    /**
     Scales the ADSR value by the Envelope Amount to Cutoff, that then scales the filter cutoff frequency.
     The current note frequency is the minimum, and the maxCutoff frequency is the maximum.
     */
    void filterEnvControl(float envVal, std::atomic<float>* amtToCO, std::atomic<float>* amtToRes)
    {
        // Cutoff envelope scaling
        float filterHeadroom = (maxCutoff - cutoffFreq) * *amtToCO;
        cutoffScale = jmap(envVal, 0.0f, 1.0f, cutoffFreq, cutoffFreq + filterHeadroom);
        
        float resHeadroom = (maxResonance - resonance) * *amtToRes;
        resonanceScale = jmap(envVal, 0.0f, 1.0f, resonance, resonance + resHeadroom);
        
        filterLFOControl();
    }
    
    /**
     Scales the LFO range, then scales that to the send amount. Modulates filter cutoff,
     clipped to 20Hz and 18000Hz
     */
    void filterLFOControl()
    {
        float lfoRange = jmap(lfoValue, -1.0f, 1.0f, -10000.0f, 10000.0f);
        float lfoScale = lfoRange * *lfoSend;
        
        float cutoffLFOUnlimited = cutoffScale + lfoScale;
        
        if (cutoffLFOUnlimited < 20.0f)
            cutoffLFOUnlimited = 20.0f;
        
        if (cutoffLFOUnlimited > 18000.0f)
            cutoffLFOUnlimited = 18000.0f;
        
        cutoffLFO = cutoffLFOUnlimited;
    }
    
    // Member Variables
    float sampleRate;
    float maxCutoff = 17000.0f;
    float maxResonance = 3.0f;
    
    float cutoffFreq;
    float resonance;
    float inputSample;
    
    float cutoffScale;
    float resonanceScale;
    
    float envelopeVal;
    float lfoValue;
    float cutoffLFO;
    
    std::atomic<float>* cutoffSend;
    std::atomic<float>* resSend;
    std::atomic<float>* lfoSend;
    
private:
    /// Cascades two IIRFilter lowpasses and returns the output sample value
    float process()
    {
        filterEnvControl(envelopeVal, cutoffSend, resSend);
        
        lowPass1.setCoefficients( IIRCoefficients::makeLowPass(sampleRate, cutoffLFO, resonanceScale) );
        lowPass2.setCoefficients( IIRCoefficients::makeLowPass(sampleRate, cutoffLFO, resonanceScale) );
        
        float stage1 = lowPass1.processSingleSampleRaw(inputSample);
        float stage2 = lowPass2.processSingleSampleRaw(stage1);
        
        return stage2;
    }

    
    // IIRFilter instances
    IIRFilter lowPass1;
    IIRFilter lowPass2;
    
};


//==============================================================================

/// Creates -24dB/octave Lowpass Filter by cascading two TwoPoleLPF class instances
class FourPoleLPF : public TwoPoleLPF
{
public:
    /// Sets sampleRate for filters and resets
    void setSampleRate(float SR) override
    {
        sampleRate = SR;
        
        twoPole1.setSampleRate(sampleRate);
        twoPole2.setSampleRate(sampleRate);
    }
    
    /**
    takes current note frequency, cutoff frequency, resonance, and input sample value.
    Returns keytracked low pass sample value
    */
    float processFilter(float noteFreq, float cutoff,
                        std::atomic<float>* res, float sampleIn, float envVal,
                        std::atomic<float>* amtToCO, std::atomic<float>* amtToRes,
                        float lfoVal, std::atomic<float>* amtToLFO) override
    {
        keyMap(noteFreq, cutoff);
        
        resonance = *res;
        inputSample = sampleIn;
        
        float stage1 = twoPole1.processFilter(noteFreq, cutoff, res, sampleIn, envVal, amtToCO, amtToRes, lfoVal, amtToLFO);
        float stage2 = twoPole2.processFilter(noteFreq, cutoff, res, stage1, envVal, amtToCO, amtToRes, lfoVal, amtToLFO);
        
        return stage2;
    }
    
private:
    // Instances of TwoPoleLPF classes
    TwoPoleLPF twoPole1;
    TwoPoleLPF twoPole2;
};


//==============================================================================


/// Creates -48dB/octave Lowpass Filter by cascading two FourPoleLPF classes
class EightPoleLPF : public FourPoleLPF
{
public:
    /// Sets sampleRate for filters and resets
    void setSampleRate(float SR) override
    {
        sampleRate = SR;
        
        fourPole1.setSampleRate(sampleRate);
        fourPole2.setSampleRate(sampleRate);
    }
    
    /**
    takes current note frequency, cutoff frequency, resonance, and input sample value.
    Returns keytracked low pass sample value
    */
    float processFilter(float noteFreq, float cutoff, std::atomic<float>* res,
                        float sampleIn, float envVal, std::atomic<float>* amtToCO,
                        std::atomic<float>* amtToRes, float lfoVal,
                        std::atomic<float>* amtToLFO) override
    {
        keyMap(noteFreq, cutoff);
        
        resonance = *res;
        inputSample = sampleIn;
        
        float stage1 = fourPole1.processFilter(noteFreq, cutoff, res, sampleIn, envVal, amtToCO, amtToRes, lfoVal, amtToLFO);
        float stage2 = fourPole2.processFilter(noteFreq, cutoff, res, stage1, envVal, amtToCO, amtToRes, lfoVal, amtToLFO);
        
        return stage2;
    }
    
private:
    // Instances of FourPoleLPF classes
    FourPoleLPF fourPole1;
    FourPoleLPF fourPole2;
};




//==============================================================================


class NotchFilter : public TwoPoleLPF
{
public:
    /// Sets sampleRate of filters and resets
    void setSampleRate(float SR) override
    {
        sampleRate = SR;
        
        notchFilter.reset();
    }
    
    /**
     Processes Non-keytracked notch filter from 20Hz to 17KHz wth resonance
     */
    float processFilter(float noteFreq, float cutoff,
                        std::atomic<float>* res, float sampleIn, float envVal,
                        std::atomic<float>* amtToCO, std::atomic<float>* amtToRes,
                        float lfoVal, std::atomic<float>* amtToLFO) override
    {
        envelopeVal = envVal;
        cutoffSend = amtToCO;
        resSend = amtToRes;
        
        lfoValue = lfoVal;
        lfoSend = amtToLFO;
        
        resonance = *res;
        inputSample = sampleIn;
        float cutFreq = cutoff;
        cutoffFreq = jmap(cutFreq, 1.0f, 100.0f, 20.0f, maxCutoff);
        
        return processNotch();
    }
private:
    /*
    void filterEnvControl(float envVal, std::atomic<float>* amtToCO, std::atomic<float>* amtToRes) override
    {
        float filterHeadroom = (maxCutoff - cutoffFreq) * *amtToCO;
        cutoffScale = jmap(envVal, 0.0f, 1.0f, cutoffFreq, cutoffFreq + filterHeadroom);
        
        float resHeadroom = (maxResonance - resonance) * *amtToRes;
        resonanceScale = jmap(envVal, 0.0f, 1.0f, resonance, resonance + resHeadroom);
    }
    */
    /// Sets notch coeffients and processes inputSample
    float processNotch()
    {
        filterEnvControl(envelopeVal, cutoffSend, resSend);
        
        notchFilter.setCoefficients( IIRCoefficients::makeLowPass(sampleRate, cutoffLFO, resonanceScale) );
        
        return notchFilter.processSingleSampleRaw(inputSample);
    }
    
    // Instance of IIRFilter class
    IIRFilter notchFilter;
    
};