#pragma once
#include <TClass.h>
#include <DEF_Message.h>
#include <DigitalSensor.h>

#include <Generics.h>


class TEncoder : public TDigitalSensor {
protected:

    static constexpr uint16_t LONG_PRESS_TIME = 800; //ms

    static constexpr uint8_t BUTTON_BIT   = 0x07;
    static constexpr uint8_t PIN_A_BIT    = 0x01;
    static constexpr uint8_t PIN_B_BIT    = 0x00;

    static constexpr uint8_t key_None   = 0x00;
    static constexpr uint8_t key_Left   = 0x01;
    static constexpr uint8_t key_Right  = 0x02;
    static constexpr uint8_t key_Both   = 0x03;
protected:
    uint8_t FPinA;
    uint8_t FPinB;

    uint8_t     FLastRotary;

    bool        FLongPress = false;
    uint16_t    FButtonPressTime = 0;

    TEncoder() = delete;
    TEncoder(TEncoder&) = delete;
    TEncoder(TEncoder&&) = delete;

    void init(void) override {
        FInitNeed = false;
        pinMode(FPinA, INPUT_PULLUP);
        pinMode(FPinB, INPUT_PULLUP);
        pinMode(FPin,  INPUT_PULLUP);
    }


    uint8_t ReadRotary() {
        uint8_t result = 0;
        
        bool    value = (digitalRead(FPinA) == FActiveLevel);
        bitWrite(result, PIN_A_BIT, value);

        value = (digitalRead(FPinB) == FActiveLevel);
        bitWrite(result, PIN_B_BIT, value);

        return result;
    }

    void onPressButton() {
        if (FButtonPressTime == 0) 
            FButtonPressTime = uint16_t(millis());
        else {
            uint16_t now = uint16_t(millis());
            if (now - FButtonPressTime > LONG_PRESS_TIME) {
                PostMessage(msg_EncoderBtnLong);
                FButtonPressTime = now;
                FLongPress = true;
            }
        }
    }

    void onReleaseButton(void) {
        if (FButtonPressTime == 0) return;
        FButtonPressTime = 0;

        if (!FLongPress) PostMessage(msg_EncoderBtnPress);
            
        FLongPress = false;
    }

    void ReadButton() {
        bool b = ReadDigitalPin(FPin, FActiveLevel);
        (b) ? onPressButton() : onReleaseButton();
    }

    void internalRead() override {
        CheckRotary(ReadRotary());
        ReadButton();
    }

    void CheckRotary(const uint8_t ANewValue) {
        if (ANewValue == key_None) return;
        
        bool enableOut = false;
        uint8_t key = ANewValue;
        uint8_t lastKey = key_None;
        
        while (key != key_None) {
            key = ReadRotary();
            if (key == key_Both) enableOut = true;
            if (enableOut && (key != key_None)) lastKey = key;
        }

        if (enableOut) {
            if (lastKey == key_Left) SendMessage(msg_EncoderLeft);
            if (lastKey == key_Right) SendMessage(msg_EncoderRight);
        }
    }



public:
    TEncoder(const uint8_t PinA, const uint8_t PinB, const uint8_t PinButton)
            :TDigitalSensor::TDigitalSensor(PinButton,LOW) {
        FPinA = PinA;
        FPinB = PinB;

        FInitNeed = true;
        FLastRotary = 0;

        FButtonPressTime = 0;

        SetReadInterval(5);
        classname = F("TEncoder");
    }
};
