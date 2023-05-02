#include "Log.h"
#include <cmath>
#include "WavetableSynthesizer.h"
#include "OboeAudioPlayer.h"
#include "WavetableOscillator.h"


namespace wavetablesynthesizer {
    WavetableSynthesizer::WavetableSynthesizer()
    : _oscillator{std::make_shared<WavetableOscillator>(
            _wavetableFactory.getWaveTable(_currentWavetable)
            ,sampleRate)},
    _audioplayer(std::make_unique<OboeAudioPlayer>(_oscillator, sampleRate)){}

   WavetableSynthesizer::~WavetableSynthesizer() = default;

    void WavetableSynthesizer::play() {
        std::lock_guard<std::mutex> lock(_mutex);
        const auto result = _audioplayer->play();
        if (result ==0) {
            _isPlaying  = true;
        } else {
            LOGD("Could not start playback.");
        }
        _isPlaying = true;
    }
    void WavetableSynthesizer::stop() {
        std::lock_guard<std::mutex> lock(_mutex);
        _audioplayer->stop();
        _isPlaying = false;
    }
    bool WavetableSynthesizer::isPlaying() const {
        ;
        return _isPlaying;
    }
    void WavetableSynthesizer::setFrequency(float frequencyInHz) {
        _oscillator->setFrequency(frequencyInHz);
    }
    float dBToAmplitude(float dB) {
        return std::pow(10.f, dB/20.f);
    }
    void WavetableSynthesizer::setVolume(float volumeInDb) {
        const auto amplitude = dBToAmplitude(volumeInDb);
        _oscillator->setAmplitude(amplitude);
    }
    void WavetableSynthesizer::setWavetable(Wavetable wavetable) {
      if (_currentWavetable != wavetable) {
          _currentWavetable = wavetable;
          _oscillator->setWavetable(_wavetableFactory.getWaveTable(wavetable));
      }
    }
}
