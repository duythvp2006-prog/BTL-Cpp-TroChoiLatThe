#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class QuanLyAmThanh {
public:
    static bool khoiTao();
    static void phatNhac(const std::string& duongDan, int soLanLap = -1);
    static void dungNhac();
    static void donDep();

private:
    static Mix_Music* nhacNen;
};

#endif
