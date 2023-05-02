package com.example.synthesizer

import android.util.Log

class LoggingWavetableSynthesizer : WavetableSynthesizer {

    private var isPlaying = false
    private var TAG = "LoggingWawetableSynthesizer"

    override suspend fun play() {
        Log.d(TAG, "play() called.")
        isPlaying = true
    }

    override suspend fun  stop() {
        Log.d(TAG, "stop() called.")
        isPlaying = false
    }

    override suspend fun  isPlaying(): Boolean {
        Log.d(TAG, "isPlaying() called.")
        return isPlaying
    }

    override suspend fun  setFrequency(frequencyInHz: Float) {
        Log.d(TAG, "setFrequency() called with $frequencyInHz.")

    }

    override suspend fun  setVolume(volumeinDb: Float) {
        Log.d(TAG, "setVolume() called with $volumeinDb.")

    }

    override suspend fun  setWavetable(wavetable: Wavetable) {
        Log.d(TAG, "setWavetable() called $wavetable.")

    }
}