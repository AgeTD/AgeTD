#ifndef SOMTD_PLAYER_H
#define SOMTD_PLAYER_H

namespace SoMTD {
    class Player {
    public:
        Player();
        ~Player();
        const int gold();
        int m_gold;
        int m_x;
        int m_y;

    };
}

#endif
