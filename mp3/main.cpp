#include <SFML/Graphics.hpp>
#include "Mp3.h"

int main()
{
    sf::RenderWindow application(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);

    sfe::Mp3 musique;                             //필요한 코드
    if (!musique.openFromFile("fly.mp3"))         //
        exit(EXIT_FAILURE);
    musique.play();                               //

        while (application.isOpen())
        {
            sf::Event evenement;
                while (application.pollEvent(evenement))
                {
                    if ((evenement.type == sf::Event::KeyPressed) && (evenement.key.code == sf::Keyboard::Escape))
                        application.close();

                        if ((evenement.type == sf::Event::KeyPressed) && (evenement.key.code == sf::Keyboard::P))
                        {
                            if (musique.getStatus() != sf::SoundStream::Paused)
                                musique.pause();
                            else
                                musique.play();
                        }
                }

            if (musique.getStatus() != sf::SoundStream::Playing && musique.getStatus() != sf::SoundStream::Paused)
                application.close();

            application.clear();

            application.display();
        }

    return EXIT_SUCCESS;
}