#include <QDir>
#include "Sounds.h"

using namespace DT;

Sounds* Sounds::instance()
{
	static Sounds uniqueInstance;
	return &uniqueInstance;
}

Sounds::Sounds()
{
	_output = new QAudioOutput();

	QStringList sound_files = QDir("sounds/").entryList(QStringList() << "*.wav", QDir::Files);
	for (auto& f : sound_files)
	{
		_sounds[QFileInfo(f).baseName().toStdString()] = new QSoundEffect();
		_sounds[QFileInfo(f).baseName().toStdString()]->setSource(QUrl::fromLocalFile(QString("sounds/") + f));
	}

	QStringList music_files = QDir("musics/").entryList(QStringList() << "*.wav", QDir::Files);
	for (auto& f : music_files)
	{
		QMediaPlayer* _player = new QMediaPlayer();
		_player->setAudioOutput(_output);
		_player->setSource(QUrl::fromLocalFile(QDir("musics/").absoluteFilePath(f)));
		_player->connect(_player, &QMediaPlayer::mediaStatusChanged,
			[=](QMediaPlayer::MediaStatus status) 
		{
			printf("%s status %d\n", _player->source().toString().toStdString().c_str(), status);

			if (status == QMediaPlayer::EndOfMedia)
				_player->play();
		});

		_player->connect(_player, &QMediaPlayer::errorOccurred,
			[=](QMediaPlayer::Error error, const QString& errorString)
		{
			printf("%s [error %d]\n", errorString.toStdString().c_str(), error);
		});

		_musics[QFileInfo(f).baseName().toStdString()] = _player;
	}
}

void Sounds::play(const std::string & id, bool musicLoop)
{
	if (!musicLoop && _sounds.find(id) != _sounds.end())
		_sounds[id]->play();
	else if(musicLoop && _musics.find(id) != _musics.end())
		_musics[id]->play();
}

void Sounds::resume(const std::string& id)
{
	if (_musics.find(id) != _musics.end())
		_musics[id]->play();
}

void Sounds::stop(const std::string & id, bool resumable)
{
	if (_musics.find(id) != _musics.end())
	{
		if(resumable)
			_musics[id]->pause();
		else
			_musics[id]->stop();
	}
}

void Sounds::speedUp() 
{
	for (auto player : _musics)
		player.second->setPlaybackRate(1.5);
}

void Sounds::reset()
{
	for (auto player : _musics)
		player.second->setPlaybackRate(1);
}
