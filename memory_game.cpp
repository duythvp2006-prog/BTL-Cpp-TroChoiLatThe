#include "memory_game.h"
using namespace std;

TroChoi::TroChoi(BanChoi& ban)
    : ban(ban), danhSachDaXoa(ban.kichThuoc(), false) {}

bool TroChoi::kiemTraTrungKhop(int chiSo1, int chiSo2) {
    return ban.layMat(chiSo1) == ban.layMat(chiSo2);
}

void TroChoi::xoaCap(int chiSo1, int chiSo2) {
    danhSachDaXoa[chiSo1] = true;
    danhSachDaXoa[chiSo2] = true;
}

bool TroChoi::daBiXoa(int chiSo) const {
    return danhSachDaXoa[chiSo];
}

bool TroChoi::daXoaHet() const {
    for (size_t i = 0; i < danhSachDaXoa.size(); ++i) {
        if (!danhSachDaXoa[i])
            return false;
    }
    return true;
}
