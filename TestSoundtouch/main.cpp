/* 
 * File:   main.cpp
 * Author: FITZPATRICK
 *
 * Created on January 6, 2013, 3:42 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "STTypes.h"
#include <SoundTouchDLL.h>
#include "WavFile.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    HANDLE h = soundtouch_createInstance();
    
    FILE * f;
    f = fopen("C:\\Users\\Shawn\\Desktop\\TuftsMastersProject\\howtosavealife.wav", "r");
    WavInFile w = WavInFile(f);
    
    int elems = w.getNumSamples();
    float *buffer = new float[elems];
    int num = w.read(buffer,elems);
    
    
    /*for (int i = 0; i < 10000; i++){
        printf("%d", buffer[i]);
    }*/
    soundtouch_setSampleRate(h, w.getSampleRate());
    soundtouch_setChannels(h, w.getNumChannels());
    soundtouch_setTempoChange(h,100);
    
    int nChannels = (int) w.getNumChannels();
    int nSamples = num/nChannels;
    int buffSizeSamples = elems/nChannels;
    
    soundtouch_putSamples(h,buffer,nSamples);
    soundtouch_receiveSamples(h,buffer,buffSizeSamples);
    
    soundtouch_flush(h);
    
    WavOutFile wOut = WavOutFile("C:\\Users\\Shawn\\Desktop\\TuftsMastersProject\\out.wav",w.getSampleRate(),w.getNumBits(),w.getNumChannels());
    wOut.write(buffer, nSamples*nChannels);
    return 0;
}

