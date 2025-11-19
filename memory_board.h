#ifndef MEMORY_BOARD_H
#define MEMORY_BOARD_H

#include <vector>
#include <SDL.h>
#include <string>

class BanChoi {
public:
    BanChoi(int soHang, int soCot, const std::string& thuMucAnh);
    
    void xaoTron();
    int layMat(int chiSo) const;
    void latThe(int chiSo); //set ("Ðat") trang thai
    void upThe(int chiSo);
    bool daDuocLat(int chiSo) const;
    int kichThuoc() const;
    const std::vector<int>& layDanhSachMat() const;

private:
    std::vector<int> danhSachMat;
    std::vector<bool> trangThaiLat;
    int soHang, soCot;
};

#endif
