# Python program to translate
# speech to text and text to speech


from operator import truediv
import speech_recognition as sr
import pyttsx3

# Initialize the recognizer
r = sr.Recognizer()


# Function to convert text to
# speech
def SpeakText(command):
    # Initialize the engine
    engine = pyttsx3.init()
    engine.say(command)
    engine.runAndWait()


# Loop infinitely for user to
# speak


with sr.Microphone() as source2:
    r.adjust_for_ambient_noise(source2, duration=0.2)
    while (1):
        # listens for the user's input
        print("speak")
        audio2 = r.listen(source2)
        print("converting")
        # Using google to recognize audio
        MyText = r.recognize_google(audio2)
        # MyText = MyText.lower()
        SpeakText(MyText)
        print("Did you say " + MyText)

if __name__ == '__main__':
    print('PyCharm')
