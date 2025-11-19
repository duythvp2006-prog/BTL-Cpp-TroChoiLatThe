#include "memory_board.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

BanChoi::BanChoi(int soHang, int soCot, const string& thuMucAnh)
    : soHang(soHang), soCot(soCot)
{
    int soCap = (soHang * soCot) / 2;
    danhSachMat.clear();

    for (int i = 0; i < soCap; i++) {
        danhSachMat.push_back(i + 2);
        danhSachMat.push_back(i + 2);
    }
    
    trangThaiLat.assign(soHang * soCot, false);
    
    xaoTron();
}

void BanChoi::xaoTron() {
    srand((unsigned)time(NULL));
    int soLuongThe = danhSachMat.size();
    for (int i = 0; i < soLuongThe; ++i) {
        int viTriNgauNhien = rand() % soLuongThe;
        swap(danhSachMat[i], danhSachMat[viTriNgauNhien]);
    }
}

int BanChoi::layMat(int chiSo) const {
    return danhSachMat[chiSo];
}

void BanChoi::latThe(int chiSo) {
    trangThaiLat[chiSo] = true;
}

void BanChoi::upThe(int chiSo) {
    trangThaiLat[chiSo] = false;
}

bool BanChoi::daDuocLat(int chiSo) const {
    return trangThaiLat[chiSo];
}

int BanChoi::kichThuoc() const {
    return static_cast<int>(danhSachMat.size());
}

const vector<int>& BanChoi::layDanhSachMat() const {
    return danhSachMat;
}
