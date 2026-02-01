#pragma once

#include <QSoundEffect>

#include <QMediaPlayer>

#include <QAudioOutput>

namespace DT {
class Sounds;
}

class DT::Sounds {
private:

    QAudioOutput * _output;

    // sounds indexed by filename
    std::map < std::string,
             QSoundEffect * > _sounds;
    std::map < std::string,
             QMediaPlayer * > _musics;

    Sounds();

public:

    // singleton
    static Sounds * instance();

    // controls
    void play(const std::string & id, bool musicLoop = false);
    void resume(const std::string & id);
    void stop(const std::string & id, bool resumable = false);
    void speedUp();
    void reset();
};
