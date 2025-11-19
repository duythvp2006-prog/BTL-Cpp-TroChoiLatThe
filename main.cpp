#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "memory_game_app.h"
#include "sound_manager.h" 

using namespace std;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) { cout << "SDL_Init Error: " << SDL_GetError() << endl; return 1; }
    if (!QuanLyAmThanh::khoiTao()) { SDL_Quit(); return 1; }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) { cout << "IMG_Init Error: " << IMG_GetError() << endl; QuanLyAmThanh::donDep(); SDL_Quit(); return 1; }
    if (TTF_Init() == -1) { cout << "TTF_Init Error: " << TTF_GetError() << endl; IMG_Quit(); QuanLyAmThanh::donDep(); SDL_Quit(); return 1; }

    QuanLyAmThanh::phatNhac("sound/soundnen.wav");
    
    int chieuRongCuaSo = 800, chieuCaoCuaSo = 600;
    SDL_Window *cuaSo = SDL_CreateWindow("Memory Puzzle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, chieuRongCuaSo, chieuCaoCuaSo, SDL_WINDOW_SHOWN);
    SDL_Renderer *congCuVe = SDL_CreateRenderer(cuaSo, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    int chieuRongVe, chieuCaoVe;
    SDL_GetRendererOutputSize(congCuVe, &chieuRongVe, &chieuCaoVe);
    
    TTF_Font* fontChuChinh = TTF_OpenFont("arial.ttf", 32);
    if (!fontChuChinh) { cout << "Khong the tai font chinh: " << TTF_GetError() << endl; return 1; }
    SDL_Texture* hinhNenChinh = NULL;
    SDL_Surface* beMatNen = IMG_Load("img/background.png");
    if (beMatNen) {
        hinhNenChinh = SDL_CreateTextureFromSurface(congCuVe, beMatNen);
        SDL_FreeSurface(beMatNen);
    }

    bool choiLai = true;
    while (choiLai)
    {
        DoKhoGame doKhoDaChon = UngDungGame::hienThiManHinhChonDoKho(congCuVe, fontChuChinh, chieuRongVe, chieuCaoVe, hinhNenChinh);

        if (doKhoDaChon == KHONG) {
            choiLai = false;
            continue;
        }

        int soHang, soCot, thoiGian;
        switch (doKhoDaChon) {
            case DE:
                soHang = 3; soCot = 2; thoiGian = 90;
                break;
            case TRUNG_BINH:
                soHang = 4; soCot = 3; thoiGian = 60;
                break;
            case KHO:
                soHang = 5; soCot = 4; thoiGian = 45;
                break;
        }

        UngDungGame ungDung(congCuVe, chieuRongVe, chieuCaoVe, soHang, soCot, thoiGian, doKhoDaChon);

        SDL_StartTextInput();
        if (!ungDung.hienThiManHinhBatDau()) {
            choiLai = false;
            SDL_StopTextInput();
            continue;
        }
        SDL_StopTextInput();

        choiLai = ungDung.chayGame();
    }

    TTF_CloseFont(fontChuChinh);
    if(hinhNenChinh) SDL_DestroyTexture(hinhNenChinh);
    
    QuanLyAmThanh::donDep();

    SDL_DestroyRenderer(congCuVe);
    SDL_DestroyWindow(cuaSo);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
