#ifndef MEMORY_GAME_APP_H
#define MEMORY_GAME_APP_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <string>
#include <vector>
#include "timer.h"
#include "memory_board.h"
#include "memory_game.h"

enum DoKhoGame {
    DE,
    TRUNG_BINH,
    KHO,
    KHONG
};

struct DiemNguoiChoi {
    std::string ten;
    int diem;
};

class UngDungGame {
public:
    UngDungGame(SDL_Renderer* congCuVe, int chieuRongVe, int chieuCaoVe, int soHang, int soCot, int thoiGianDemNguoc, DoKhoGame doKho);
    ~UngDungGame();

    bool hienThiManHinhBatDau();
    bool chayGame();
    static DoKhoGame hienThiManHinhChonDoKho(SDL_Renderer* congCuVe, TTF_Font* fontChu, int chieuRong, int chieuCao, SDL_Texture* hinhNen);

private:
    SDL_Renderer* congCuVe; 
    int chieuRongVe;
    int chieuCaoVe;
    TTF_Font* fontChu;

    DongHoDemNguoc dongHo; 
    
    BanChoi banChoi; 
    TroChoi troChoi; 
    std::map<int, SDL_Texture*> hinhAnhTheBai;

    int theDaChon1;
    int theDaChon2;
    Uint32 thoiDiemLatThe;
    bool dangChay;

    int soHang;
    int soCot;
    int thoiGianDemNguoc;
    
    SDL_Texture* hinhNen;

    std::string tenNguoiChoi;
    DoKhoGame doKhoHienTai;

    std::vector<DiemNguoiChoi> bangXepHangHienTai;

    void taiBangXepHang();
    void luuBangXepHang();
    void themVaoBangXepHang(int diem);
    void hienThiBangXepHang();

    void taiHinhAnh();
    void giaiPhongHinhAnh();
    void xuLySuKien();
    void capNhat();
    void veManHinh();
};

#endif // MEMORY_GAME_APP_H
