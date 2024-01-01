#include <SFML/Audio.hpp>
#include <iostream>
#include<Windows.h>
#include<conio.h>

int main() {
    // Full path to the sound file on the D drive
    const std::string soundFilePath = "D:\Chaal-Chal-Tu-Apni-Main-Tujhe-Pahchan-Lunga(PaglaSongs).wav";

    // Load the sound file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(soundFilePath)) {
        std::cerr << "Failed to load the sound file." << std::endl;
        return 1;
    }

    // Create a sound instance
    sf::Sound sound(buffer);
    //playing the s
    // Play the sound
    
    sound.play();
    std::cout << "Sound is playing..." << std::endl;

    //char ch=getch();
    // Sleep to allow the sound to play for a while
    sf::sleep(sf::seconds(50000));

    // Pause the sound
    sound.pause();
    std::cout << "Sound paused..." << std::endl;

    // Sleep to simulate a pause
    sf::sleep(sf::seconds(2));

    // Resume the sound
    sound.play();
    std::cout << "Sound resumed..." << std::endl;

    // Sleep to allow the sound to play for a while
    sf::sleep(sf::seconds(5));

    // Stop the sound (optional, as it will stop when the program exits)
    sound.stop();

    return 0;
}
