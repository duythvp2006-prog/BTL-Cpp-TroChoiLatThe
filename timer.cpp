#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "timer.h"

DongHoBamGio::DongHoBamGio() : mocBatDau(0), mocKetThuc(0), dangChay(false) {}

void DongHoBamGio::batDau() {
    dangChay = true;
    mocBatDau = SDL_GetTicks();
}

void DongHoBamGio::dungLai() {
    dangChay = false;
    mocKetThuc = SDL_GetTicks();
}

void DongHoBamGio::datLai() {
    dangChay = false;
    mocBatDau = 0;
    mocKetThuc = 0; 
}

Uint32 DongHoBamGio::miliGiayDaTroiQua() const {
    if (dangChay) {
        return SDL_GetTicks() - mocBatDau;
    }
    else {
        return mocKetThuc - mocBatDau;
    }
}

double DongHoBamGio::giayDaTroiQua() const {
    return miliGiayDaTroiQua() / 1000.0;
}

DongHoDemNguoc::DongHoDemNguoc(int soGiayBatDau) 
    : thoiGianDatTruoc(soGiayBatDau) {
}

int DongHoDemNguoc::giayConLai() const {
    int soGiayDaQua = static_cast<int>(giayDaTroiQua());
    
    int soGiayConLai = thoiGianDatTruoc - soGiayDaQua;
    
    if (soGiayConLai < 0) {
        return 0;
    }
    return soGiayConLai;
}
