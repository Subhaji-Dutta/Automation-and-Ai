import random

R_EATING = "I don't like eating anything because I'm a bot obviously!"
R_ADVICE = "If I were you, I would go to the internet and type exactly what you said!"
R_NAME = "I am ZIRA. How can I help you today?"
R_FEEL = "I feel happy to be here and be able to help you in any way I can."
R_PLAN = "I like to help people achieve their goals."
R_LOVE = "I love learning and discovering new things. I also enjoy spending time with people, and helping them out however I can."


def unknown():
    response = ["Could you please re-phrase that? ",                
                "What does that mean?"][
        random.randrange(2)]
    return response