#pragma once
#include <SDL.h>

class DongHoBamGio {
public:
    DongHoBamGio();

    void batDau();
    void dungLai(); 
    void datLai();

    Uint32 miliGiayDaTroiQua() const;
    double giayDaTroiQua() const;				
													
private:											
    Uint32 mocBatDau;								
    Uint32 mocKetThuc; 
    bool dangChay;
};

class DongHoDemNguoc : public DongHoBamGio {
public:
    DongHoDemNguoc(int soGiayBatDau);
    int giayConLai() const;
private:
    int thoiGianDatTruoc;
};
