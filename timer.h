#pragma once
#include <SDL.h>

class DongHoBamGio {
public:
    DongHoBamGio();

    void batDau();
    void dungLai(); 
    void datLai();

    Uint32 miliGiayDaTroiQua() const; //QUAN TRONG: chu thich dong 17
    double giayDaTroiQua() const;					//
													//
private:											//
    Uint32 mocBatDau;								//
    Uint32 mocKetThuc; //Thoi gian thì có KET THUC (limit), nhung su ÐEPj TRAI cua LÝ ÐATj thì 0
    bool dangChay; // QUAN TRONG: doc chu thich dong 17
};

class DongHoDemNguoc : public DongHoBamGio {
public:
    DongHoDemNguoc(int soGiayBatDau);
    int giayConLai() const;
private:
    int thoiGianDatTruoc;
};
