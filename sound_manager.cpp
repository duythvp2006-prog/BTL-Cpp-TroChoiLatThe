#include "sound_manager.h"
#include <iostream>

Mix_Music* QuanLyAmThanh::nhacNen = nullptr;

bool QuanLyAmThanh::khoiTao() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer init error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void QuanLyAmThanh::phatNhac(const std::string& duongDan, int soLanLap) {
    if (nhacNen) {
        Mix_FreeMusic(nhacNen);
        nhacNen = nullptr;
    }

    nhacNen = Mix_LoadMUS(duongDan.c_str());
    if (!nhacNen) {
        std::cout << "Không tai duoc nhac nen: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    Mix_PlayMusic(nhacNen, soLanLap);
}

void QuanLyAmThanh::dungNhac() {
    Mix_HaltMusic();
}

void QuanLyAmThanh::donDep() {
    if (nhacNen) {
        Mix_FreeMusic(nhacNen);
        nhacNen = nullptr;
    }
    Mix_CloseAudio();
}
