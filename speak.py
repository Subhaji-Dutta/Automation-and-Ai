
import pyttsx3

import random
import time

engine = pyttsx3.init()  
voice_id="HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\Tokens\TTS_MS_EN-US_ZIRA_11.0"
engine.setProperty("voice",voice_id)
newVoiceRate = 140
engine.setProperty('rate',newVoiceRate)
engine.setProperty("voice",voice_id)

def speak(audio):
    engine.say(audio)
    print(audio)
    engine.runAndWait()



speak("kindly refer to your letter CI: 266/ID dated 13 Jul 23.")
time.sleep(0.5)
speak("Sir, I retired from service on 30 November 2010 just after completing OA No. 533 of CAT Kolkata in the year 2009 I was busy for my retirement. Sir, at that time due to my retirement I was not interested in other matters and also had no idea/intimation about the Wirt petition   WPCT No. 203/2009 before Hon’ble High Court, Kolkata against OA No. 533.")
time.sleep(0.5)
speak("Sir, after retirement, I have passed twelve and half years and am not in a position to run here and there for my seniority benefits.  ")
time.sleep(0.5)
speak("It is, therefore, requested that you may kindly dispose of WPCT No, 203/2009. Sir, I do not want these benefits because I earned so many things and respect from the Navy during my 42 years of service (approx).")