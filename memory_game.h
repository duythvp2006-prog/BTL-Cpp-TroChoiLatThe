#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H

#include "memory_board.h"
#include <vector>

class TroChoi {
public:
    TroChoi(BanChoi& ban);
    
    bool kiemTraTrungKhop(int chiSo1, int chiSo2);
    void xoaCap(int chiSo1, int chiSo2);
    bool daBiXoa(int chiSo) const;
    bool daXoaHet() const;

private:
    BanChoi& ban;
    std::vector<bool> danhSachDaXoa;
};

#endif
