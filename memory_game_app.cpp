#include "memory_game_app.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

bool soSanhDiem(const DiemNguoiChoi& a, const DiemNguoiChoi& b) {
    return a.diem < b.diem;
}

UngDungGame::UngDungGame(SDL_Renderer* congCuVe, int chieuRongVe, int chieuCaoVe, int soHang, int soCot, int thoiGianDemNguoc, DoKhoGame doKho)
    : congCuVe(congCuVe),
      chieuRongVe(chieuRongVe),
      chieuCaoVe(chieuCaoVe),
      fontChu(NULL),
      soHang(soHang),
      soCot(soCot),
      thoiGianDemNguoc(thoiGianDemNguoc),
      doKhoHienTai(doKho),
      dongHo(thoiGianDemNguoc), 
      banChoi(soHang, soCot, "img"),
      troChoi(banChoi),
      theDaChon1(-1),
      theDaChon2(-1),
      thoiDiemLatThe(0),
      dangChay(true),
      hinhNen(NULL)
{
    fontChu = TTF_OpenFont("arial.ttf", 32);
    if (!fontChu) {
        cout << "TTF_OpenFont Error: " << TTF_GetError() << endl;
        dangChay = false;
    }
    taiHinhAnh();
}

UngDungGame::~UngDungGame() {
    giaiPhongHinhAnh();
    if (fontChu) {
        TTF_CloseFont(fontChu);
    }
}

void UngDungGame::taiHinhAnh() {
    SDL_Surface* beMatNen = IMG_Load("img/background.png");
    if (beMatNen) {
        hinhNen = SDL_CreateTextureFromSurface(congCuVe, beMatNen);
        SDL_FreeSurface(beMatNen);
    } else {
        cout << "Khong tim thay hình nen (img/background.png): " << IMG_GetError() << endl;
    }

    for (int i = 1; i <= 1 + (soHang * soCot) / 2; ++i) {
        char buffer[50];
        sprintf(buffer, "img/%d.png", i);
        string duongDan = buffer;

        SDL_Surface* beMat = IMG_Load(duongDan.c_str());
        if (!beMat) {
            cout << "IMG_Load Error: " << IMG_GetError() << " (" << duongDan << ")" << endl;
            continue;
        }
        hinhAnhTheBai[i] = SDL_CreateTextureFromSurface(congCuVe, beMat);
        SDL_FreeSurface(beMat);
    }

    if (hinhAnhTheBai.find(1) == hinhAnhTheBai.end()) {
        string duongDan = "img/1.png";
        SDL_Surface* beMat = IMG_Load(duongDan.c_str());
        if (beMat) {
            hinhAnhTheBai[1] = SDL_CreateTextureFromSurface(congCuVe, beMat);
            SDL_FreeSurface(beMat);
        }
    }
}

void UngDungGame::giaiPhongHinhAnh() {
    if (hinhNen) {
        SDL_DestroyTexture(hinhNen);
        hinhNen = NULL;
    }

    for (std::map<int, SDL_Texture*>::iterator it = hinhAnhTheBai.begin(); it != hinhAnhTheBai.end(); ++it) {
        SDL_DestroyTexture(it->second);
    }
    hinhAnhTheBai.clear();
}

bool UngDungGame::hienThiManHinhBatDau()
{
    SDL_Event suKien;
    bool dangNhapTen = true;
    tenNguoiChoi = "";

    SDL_StartTextInput();
    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color orange = {255, 165, 0, 255};

    while (dangNhapTen) {
        while (SDL_PollEvent(&suKien)) {
            if (suKien.type == SDL_QUIT) { //nút X
                SDL_StopTextInput();
                return false; // thoát game
            }
            if (suKien.type == SDL_TEXTINPUT) { // có kí tu duoc nhap
                tenNguoiChoi += suKien.text.text;
            }
            if (suKien.type == SDL_KEYDOWN) {
                if (suKien.key.keysym.sym == SDLK_BACKSPACE && !tenNguoiChoi.empty()) {
                    tenNguoiChoi.pop_back();
                } else if (suKien.key.keysym.sym == SDLK_RETURN && !tenNguoiChoi.empty()) { //nhan phim enter
                    dangNhapTen = false; //ket thuc nhap ten
                }
            }
        }

        if (hinhNen)
            SDL_RenderCopy(congCuVe, hinhNen, NULL, NULL);
        else {
            SDL_SetRenderDrawColor(congCuVe, 15, 15, 30, 255);
            SDL_RenderClear(congCuVe);
        }

        std::string thongBao = "Ten nguoi choi: " + tenNguoiChoi + "|";
        SDL_Surface* beMatChu = TTF_RenderText_Solid(fontChu, thongBao.c_str(), black);
        SDL_Texture* hinhAnhChu = SDL_CreateTextureFromSurface(congCuVe, beMatChu);
        SDL_Rect hcnChu = { chieuRongVe / 2 - beMatChu->w / 2, chieuCaoVe / 2 - 20, beMatChu->w, beMatChu->h };
        SDL_RenderCopy(congCuVe, hinhAnhChu, NULL, &hcnChu);
        SDL_FreeSurface(beMatChu);
        SDL_DestroyTexture(hinhAnhChu);

        std::string thongBaoPhu = "Nhan Enter de bat dau";
        SDL_Surface* beMatPhu = TTF_RenderText_Solid(fontChu, thongBaoPhu.c_str(), orange);
        SDL_Texture* hinhAnhPhu = SDL_CreateTextureFromSurface(congCuVe, beMatPhu);
        SDL_Rect hcnPhu = { chieuRongVe / 2 - beMatPhu->w / 2, chieuCaoVe / 2 + 50, beMatPhu->w, beMatPhu->h };
        SDL_RenderCopy(congCuVe, hinhAnhPhu, NULL, &hcnPhu);
        SDL_FreeSurface(beMatPhu);
        SDL_DestroyTexture(hinhAnhPhu);

        SDL_RenderPresent(congCuVe);
        SDL_Delay(16);
    }

    SDL_StopTextInput();
    return true;
}

bool UngDungGame::chayGame() {
    dongHo.batDau(); 
    while (dangChay) {
        xuLySuKien();
        capNhat();
        veManHinh();
        SDL_Delay(16); // giup game chay o 60 FPS
    }
    hienThiBangXepHang();

    SDL_Event suKien;
    while(true) {
        if (SDL_PollEvent(&suKien)) {
            if (suKien.type == SDL_QUIT || (suKien.type == SDL_KEYDOWN && suKien.key.keysym.sym == SDLK_ESCAPE))
                return false;
            if (suKien.type == SDL_KEYDOWN && suKien.key.keysym.sym == SDLK_RETURN)
                return true;
        }
    }
}


void UngDungGame::xuLySuKien() {
    SDL_Event suKien;
    while (SDL_PollEvent(&suKien)) {
        if (suKien.type == SDL_QUIT)
            dangChay = false;

        if (suKien.type == SDL_MOUSEBUTTONDOWN && suKien.button.button == SDL_BUTTON_LEFT && theDaChon2 == -1) {
            const int chieuCaoDongHo = 60, leTren = 20, leBen = 20, khoangCachThe = 10;
            int chieuRongKhaDung = chieuRongVe - 2 * leBen - (soCot - 1) * khoangCachThe;
            int chieuCaoKhaDung = chieuCaoVe - chieuCaoDongHo - leTren - (soHang - 1) * khoangCachThe - leBen;
            const float tyLeThe = 0.75f; //
            int chieuRongThe = chieuRongKhaDung / soCot, chieuCaoThe = chieuCaoKhaDung / soHang;
            if (chieuRongThe / (float)chieuCaoThe > tyLeThe) chieuRongThe = static_cast<int>(chieuCaoThe * tyLeThe);
            else chieuCaoThe = static_cast<int>(chieuRongThe / tyLeThe);
            int chieuRongLuoi = soCot * chieuRongThe + (soCot - 1) * khoangCachThe;
            int chieuCaoLuoi = soHang * chieuCaoThe + (soHang - 1) * khoangCachThe;
            int viTriBatDauX = leBen + (chieuRongKhaDung - chieuRongLuoi) / 2;
            int viTriBatDauY = chieuCaoDongHo + leTren + (chieuCaoKhaDung - chieuCaoLuoi) / 2;

            for (int hang = 0; hang < soHang; ++hang) {
                for (int cot = 0; cot < soCot; ++cot) {
                    int chiSo = hang * soCot + cot;
                    SDL_Rect hcnTheBai = { viTriBatDauX + cot * (chieuRongThe + khoangCachThe), viTriBatDauY + hang * (chieuCaoThe + khoangCachThe), chieuRongThe, chieuCaoThe };
                    SDL_Point diemChuot = { suKien.button.x, suKien.button.y };
                    if (SDL_PointInRect(&diemChuot, &hcnTheBai) && !banChoi.daDuocLat(chiSo)) {
                        if (theDaChon1 == -1) {
                            theDaChon1 = chiSo;
                            banChoi.latThe(chiSo);
                        } else if (theDaChon1 != chiSo) {
                            theDaChon2 = chiSo;
                            banChoi.latThe(chiSo);
                            thoiDiemLatThe = SDL_GetTicks();
                        }
                    }
                }
            }
        }
    }
}

void UngDungGame::capNhat() {
    if (theDaChon1 != -1 && theDaChon2 != -1) {
        if (SDL_GetTicks() - thoiDiemLatThe > 1000) {
            if (troChoi.kiemTraTrungKhop(theDaChon1, theDaChon2)) 
                troChoi.xoaCap(theDaChon1, theDaChon2); 
            else {
                banChoi.upThe(theDaChon1); 
                banChoi.upThe(theDaChon2); 
            }
            theDaChon1 = -1; theDaChon2 = -1;
        }
    }

    if (dongHo.giayConLai() <= 0 && !troChoi.daXoaHet()) {
        dangChay = false;
        return;
    }

    if (troChoi.daXoaHet()) {
        themVaoBangXepHang(static_cast<int>(dongHo.giayDaTroiQua()));
        SDL_Delay(500);
        dangChay = false;
    }
}

void UngDungGame::veManHinh() {
    if (hinhNen) SDL_RenderCopy(congCuVe, hinhNen, NULL, NULL);
    else { SDL_SetRenderDrawColor(congCuVe, 5, 19, 41, 255); SDL_RenderClear(congCuVe); }

    SDL_Color mauTen = {255, 255, 255, 255};
    string chuoiTen = "Nguoi choi: " + tenNguoiChoi;
    SDL_Surface* beMatTen = TTF_RenderText_Solid(fontChu, chuoiTen.c_str(), mauTen);
    SDL_Texture* hinhAnhTen = SDL_CreateTextureFromSurface(congCuVe, beMatTen);
    SDL_Rect hcnTen = {20, 10, beMatTen->w, beMatTen->h};
    SDL_RenderCopy(congCuVe, hinhAnhTen, NULL, &hcnTen);
    SDL_FreeSurface(beMatTen); SDL_DestroyTexture(hinhAnhTen);

    int thoiGianConLai = dongHo.giayConLai();
    
    char chuoiThoiGian[6];
    snprintf(chuoiThoiGian, sizeof(chuoiThoiGian), "%02d:%02d", thoiGianConLai / 60, thoiGianConLai % 60);
    SDL_Color mauThoiGian = {255, 165, 0, 255};
    SDL_Surface* beMatThoiGian = TTF_RenderText_Solid(fontChu, chuoiThoiGian, mauThoiGian);
    SDL_Texture* hinhAnhThoiGian = SDL_CreateTextureFromSurface(congCuVe, beMatThoiGian);
    SDL_Rect hcnThoiGian = {chieuRongVe / 2 - beMatThoiGian->w / 2, 30 - beMatThoiGian->h / 2, beMatThoiGian->w, beMatThoiGian->h};
    SDL_RenderCopy(congCuVe, hinhAnhThoiGian, NULL, &hcnThoiGian);
    SDL_FreeSurface(beMatThoiGian); SDL_DestroyTexture(hinhAnhThoiGian);

    const int chieuCaoDongHo = 60, leTren = 20, leBen = 20, khoangCachThe = 10; //khoangCachThe
    int chieuRongKhaDung = chieuRongVe - 2 * leBen - (soCot - 1) * khoangCachThe;
    int chieuCaoKhaDung = chieuCaoVe - chieuCaoDongHo - leTren - (soHang - 1) * khoangCachThe - leBen;
    const float tyLeThe = 0.75f; //
    int chieuRongThe = chieuRongKhaDung / soCot, chieuCaoThe = chieuCaoKhaDung / soHang;
    if (chieuRongThe / (float)chieuCaoThe > tyLeThe) chieuRongThe = static_cast<int>(chieuCaoThe * tyLeThe);
    else chieuCaoThe = static_cast<int>(chieuRongThe / tyLeThe);
    int chieuRongLuoi = soCot * chieuRongThe + (soCot - 1) * khoangCachThe;
    int chieuCaoLuoi = soHang * chieuCaoThe + (soHang - 1) * khoangCachThe;
    int viTriBatDauX = leBen + (chieuRongKhaDung - chieuRongLuoi) / 2;
    int viTriBatDauY = chieuCaoDongHo + leTren + (chieuCaoKhaDung - chieuCaoLuoi) / 2;

    for (int hang = 0; hang < soHang; ++hang) {
        for (int cot = 0; cot < soCot; ++cot) {
            int chiSo = hang * soCot + cot;
            if (troChoi.daBiXoa(chiSo)) continue;
            SDL_Rect hcnTheBai = { viTriBatDauX + cot * (chieuRongThe + khoangCachThe), viTriBatDauY + hang * (chieuCaoThe + khoangCachThe), chieuRongThe, chieuCaoThe };
            int chiSoAnh = banChoi.daDuocLat(chiSo) ? banChoi.layMat(chiSo) : 1;
            SDL_Texture* hinhAnh = hinhAnhTheBai.count(chiSoAnh) ? hinhAnhTheBai[chiSoAnh] : NULL;
            if (hinhAnh) SDL_RenderCopy(congCuVe, hinhAnh, NULL, &hcnTheBai);
        }
    }
    SDL_RenderPresent(congCuVe);
}

void UngDungGame::taiBangXepHang() {
    string tenFile;
    switch (doKhoHienTai) {
        case DE:   tenFile = "leaderboard_easy.txt";   break;
        case TRUNG_BINH: tenFile = "leaderboard_medium.txt"; break;
        case KHO:   tenFile = "leaderboard_hard.txt";   break;
        default: return;
    }

    ifstream file(tenFile);
    if (!file.is_open()) return;
    bangXepHangHienTai.clear();
    DiemNguoiChoi diemTam;
    while (file >> diemTam.ten >> diemTam.diem) {
        bangXepHangHienTai.push_back(diemTam);
    }
    file.close();
    sort(bangXepHangHienTai.begin(), bangXepHangHienTai.end(), soSanhDiem);
}

void UngDungGame::luuBangXepHang() {
    string tenFile;
    switch (doKhoHienTai) {
        case DE:   tenFile = "leaderboard_easy.txt";   break;
        case TRUNG_BINH: tenFile = "leaderboard_medium.txt"; break;
        case KHO:   tenFile = "leaderboard_hard.txt";   break;
        default: return;
    }

    ofstream file(tenFile);
    if (!file.is_open()) return;
    for (const auto& diem : bangXepHangHienTai) {
        file << diem.ten << " " << diem.diem << endl;
    }
    file.close();
}

void UngDungGame::themVaoBangXepHang(int diem) {
    taiBangXepHang(); 
    bangXepHangHienTai.push_back({tenNguoiChoi, diem});
    sort(bangXepHangHienTai.begin(), bangXepHangHienTai.end(), soSanhDiem);
    if (bangXepHangHienTai.size() > 10) bangXepHangHienTai.resize(10);
    luuBangXepHang();
}

void UngDungGame::hienThiBangXepHang() {
    taiBangXepHang();

    if (hinhNen) SDL_RenderCopy(congCuVe, hinhNen, NULL, NULL);
    else { SDL_SetRenderDrawColor(congCuVe, 5, 19, 41, 255); SDL_RenderClear(congCuVe); }

    SDL_Color orange = {255, 165, 0, 255}, black = {0, 0, 0, 255};
    string chuoiTieuDe;
    switch (doKhoHienTai) {
        case DE:   chuoiTieuDe = "BANG XEP HANG MUC DE";   break;
        case TRUNG_BINH: chuoiTieuDe = "BANG XEP HANG MUC TB"; break;
        case KHO:  chuoiTieuDe = "BANG XEP HANG MUC KHO";  break;
        default:     chuoiTieuDe = "BANG XEP HANG";        break;
    }

    SDL_Surface* beMatTieuDe = TTF_RenderText_Solid(fontChu, chuoiTieuDe.c_str(), orange);
    SDL_Texture* hinhAnhTieuDe = SDL_CreateTextureFromSurface(congCuVe, beMatTieuDe);
    SDL_Rect hcnTieuDe = { chieuRongVe / 2 - beMatTieuDe->w / 2, 50, beMatTieuDe->w, beMatTieuDe->h };
    SDL_RenderCopy(congCuVe, hinhAnhTieuDe, NULL, &hcnTieuDe);
    SDL_FreeSurface(beMatTieuDe); SDL_DestroyTexture(hinhAnhTieuDe);

    int viTriBatDauY = 120;
    for (size_t i = 0; i < bangXepHangHienTai.size(); ++i) {
        string chuoiDiem = bangXepHangHienTai[i].ten + " - " + to_string(bangXepHangHienTai[i].diem) + "s";
        SDL_Surface* beMatDiem = TTF_RenderText_Solid(fontChu, chuoiDiem.c_str(), black);
        SDL_Texture* hinhAnhDiem = SDL_CreateTextureFromSurface(congCuVe, beMatDiem);
        SDL_Rect hcnDiem = { chieuRongVe / 2 - beMatDiem->w / 2, viTriBatDauY + (int)i * 40, beMatDiem->w, beMatDiem->h };
        SDL_RenderCopy(congCuVe, hinhAnhDiem, NULL, &hcnDiem);
        SDL_FreeSurface(beMatDiem); SDL_DestroyTexture(hinhAnhDiem);
    }

    string thongBaoPhu = "Nhan Enter de choi lai hoac ESC de thoat";
    SDL_Surface* beMatPhu = TTF_RenderText_Solid(fontChu, thongBaoPhu.c_str(), orange);
    SDL_Texture* hinhAnhPhu = SDL_CreateTextureFromSurface(congCuVe, beMatPhu);
    SDL_Rect hcnPhu = { chieuRongVe / 2 - beMatPhu->w / 2, chieuCaoVe - 80, beMatPhu->w, beMatPhu->h };
    SDL_RenderCopy(congCuVe, hinhAnhPhu, NULL, &hcnPhu);
    SDL_FreeSurface(beMatPhu); SDL_DestroyTexture(hinhAnhPhu);

    SDL_RenderPresent(congCuVe);
}

DoKhoGame UngDungGame::hienThiManHinhChonDoKho(SDL_Renderer* congCuVe, TTF_Font* fontChu, int chieuRong, int chieuCao, SDL_Texture* hinhNen) {
    SDL_Event suKien;
    SDL_Color orange = {255, 165, 0, 255}, white = {255, 255, 255, 255};
    SDL_Rect nutDe = { chieuRong / 2 - 150, chieuCao / 2 - 100, 300, 50 };
    SDL_Rect nutTrungBinh = { chieuRong / 2 - 150, chieuCao / 2 - 25, 300, 50 };
    SDL_Rect nutKho = { chieuRong / 2 - 150, chieuCao / 2 + 50, 300, 50 };

    while (true) {
        while (SDL_PollEvent(&suKien)) {
            if (suKien.type == SDL_QUIT) return KHONG;
            if (suKien.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point diemChuot = {suKien.button.x, suKien.button.y};
                if (SDL_PointInRect(&diemChuot, &nutDe)) return DE;
                if (SDL_PointInRect(&diemChuot, &nutTrungBinh)) return TRUNG_BINH;
                if (SDL_PointInRect(&diemChuot, &nutKho)) return KHO;
            }
        }

        if (hinhNen) SDL_RenderCopy(congCuVe, hinhNen, NULL, NULL);
        else { SDL_SetRenderDrawColor(congCuVe, 5, 19, 41, 255); SDL_RenderClear(congCuVe); }

        SDL_Surface* beMatTieuDe = TTF_RenderText_Solid(fontChu, "CHON CHE DO CHOI", orange);
        SDL_Texture* hinhAnhTieuDe = SDL_CreateTextureFromSurface(congCuVe, beMatTieuDe);
        SDL_Rect hcnTieuDe = { chieuRong / 2 - beMatTieuDe->w / 2, 100, beMatTieuDe->w, beMatTieuDe->h };
        SDL_RenderCopy(congCuVe, hinhAnhTieuDe, NULL, &hcnTieuDe);
        SDL_FreeSurface(beMatTieuDe); SDL_DestroyTexture(hinhAnhTieuDe);
        
        SDL_SetRenderDrawColor(congCuVe, 1, 26, 56, 255);
        SDL_RenderFillRect(congCuVe, &nutDe);
        SDL_Surface* beMatDe = TTF_RenderText_Solid(fontChu, "DE (3x2)", white);
        SDL_Texture* hinhAnhDe = SDL_CreateTextureFromSurface(congCuVe, beMatDe);
        SDL_Rect hcnDe = { chieuRong / 2 - beMatDe->w / 2, nutDe.y + 5, beMatDe->w, beMatDe->h };
        SDL_RenderCopy(congCuVe, hinhAnhDe, NULL, &hcnDe);
        SDL_FreeSurface(beMatDe); SDL_DestroyTexture(hinhAnhDe);

        SDL_SetRenderDrawColor(congCuVe, 1, 26, 56, 255);
        SDL_RenderFillRect(congCuVe, &nutTrungBinh);
        SDL_Surface* beMatTB = TTF_RenderText_Solid(fontChu, "TRUNG BINH (4x3)", white);
        SDL_Texture* hinhAnhTB = SDL_CreateTextureFromSurface(congCuVe, beMatTB);
        SDL_Rect hcnTB = { chieuRong / 2 - beMatTB->w / 2, nutTrungBinh.y + 5, beMatTB->w, beMatTB->h };
        SDL_RenderCopy(congCuVe, hinhAnhTB, NULL, &hcnTB);
        SDL_FreeSurface(beMatTB); SDL_DestroyTexture(hinhAnhTB);

        SDL_SetRenderDrawColor(congCuVe, 1, 26, 56, 255);
        SDL_RenderFillRect(congCuVe, &nutKho);
        SDL_Surface* beMatKho = TTF_RenderText_Solid(fontChu, "KHO (5x4)", white);
        SDL_Texture* hinhAnhKho = SDL_CreateTextureFromSurface(congCuVe, beMatKho);
        SDL_Rect hcnKho = { chieuRong / 2 - beMatKho->w / 2, nutKho.y + 5, beMatKho->w, beMatKho->h };
        SDL_RenderCopy(congCuVe, hinhAnhKho, NULL, &hcnKho);
        SDL_FreeSurface(beMatKho); SDL_DestroyTexture(hinhAnhKho);

        SDL_RenderPresent(congCuVe);
        SDL_Delay(16);
    }
    return KHONG;
}
