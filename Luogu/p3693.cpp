#include <bits/stdc++.h>

namespace hellolin {
#define rep(x, a, b) for (auto x = a, x##END = b; x <= x##END; ++x)
#define per(x, a, b) for (auto x = a, x##END = b; x >= x##END; --x)
#define fi first
#define se second
#define pb emplace_back

int n, m, q;
std::pair<int, int> hp, hc;
#define check_pos(l, r, x) (x >= l && x <= r)
class vector final {
public:
    int x, y, z;
    explicit vector(int _x = 0, int _y = 0, int _z = 0)
        : x(_x)
        , y(_y)
        , z(_z) {}
    vector operator+(const vector &t) const {
        return vector(x + t.x, y + t.y, z + t.z);
    }
    vector &operator+=(const vector &t) {
        return *this = *this + t;
    }
    std::weak_ordering operator<=>(const vector &t) const {
        if (x == t.x) {
            if (y == t.y)
                return z <=> t.z;
            else
                return y <=> t.y;
        }
        return x <=> t.x;
    }
    bool operator==(const vector &t) const {
        return x == t.x && y == t.y && z == t.z;
    }
    bool is_valid() const {
        return check_pos(0, n - 1, x) && check_pos(0, n - 1, y) && check_pos(0, m, z);
    }
    bool is_inside_the_house() {
        return x >= hp.fi + 1 && x <= hp.fi + hc.fi - 2 && y >= hp.se + 1 && y <= hp.se + hc.se - 2;
    }
    bool is_outside_the_house() {
        return x < hp.fi || x > hp.fi + hc.fi - 1 || y < hp.se || y > hp.se + hc.se - 1;
    }
};
short vis_err_t = -1;
class ground final {
private:
    int sz;
    short ***s;

public:
    explicit ground(int _sz = 50)
        : sz(_sz) {
        s = new short **[sz];
        rep(i, 0, sz) {
            s[i] = new short *[sz];
            rep(j, 0, sz)
                s[i][j] = new short[sz];
        }
        rep(i, 0, sz)
            rep(j, 0, sz)
                rep(k, 0, sz)
                    s[i][j][k] = 0;
    }
    ~ground() {
        rep(i, 0, sz) {
            rep(j, 0, sz) delete[] s[i][j];
            delete[] s[i];
        }
        delete[] s;
    }
    short &operator[](const vector &t) {
        if (!t.is_valid()) return vis_err_t;
        return s[t.x][t.y][t.z];
    }
};
ground gr;
class cirnos_ice_house_emulator final {
private:
    class internal_emulator final {
        char msg[500];
        static constexpr char *msg_dict[] = {
            (char *) "CIRNO FREEZED %d BLOCK(S)\n",
            (char *) "CIRNO MADE %d ICE BLOCK(S),NOW SHE HAS %d ICE BLOCK(S)\n",
            (char *) "CIRNO HAS NO ICE_BLOCK\n",
            (char *) "BAKA CIRNO,CAN'T PUT HERE\n",
            (char *) "CIRNO MISSED THE PLACE\n",
            (char *) "CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE\n",
            (char *) "CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS %d ICE_BLOCK(S)\n",
            (char *) "BAKA CIRNO,THERE IS NO ICE_BLOCK\n",
            (char *) "CIRNO REMOVED AN ICE_BLOCK,AND %d BLOCK(S) ARE BROKEN\n",
            (char *) "CIRNO REMOVED AN ICE_BLOCK\n",
            (char *) "SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF\n",
            (char *) "SORRY CIRNO,HOUSE IS TOO SMALL\n",
            (char *) "%d ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED\n",
            (char *) "%d ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED\n",
            (char *) "SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS\n",
            (char *) "SORRY CIRNO,NOT ENOUGH ICE_BLOCKS TO FIX THE WALL\n",
            (char *) "GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE\n",
            (char *) "HOUSE HAS NO DOOR\n",
            (char *) "DOOR IS OK\n",
            (char *) "WALL NEED TO BE FIXED\n",
            (char *) "WALL IS OK\n",
            (char *) "CORNER NEED TO BE FIXED\n",
            (char *) "CORNER IS OK\n",
            (char *) "CIRNO FINALLY HAS %d ICE_BLOCK(S)\n",
            (char *) "CIRNO IS PERFECT!\n"};
        std::vector<vector>
            directions{vector(-1, 0), vector(-1, -1),
                       vector(0, -1), vector(1, -1),
                       vector(1, 0), vector(1, 1),
                       vector(0, 1), vector(-1, 1)},
            directions_3d{vector(-1, 0, 0), vector(1, 0, 0),
                          vector(0, -1, 0), vector(0, 1, 0),
                          vector(0, 0, 1), vector(0, 0, -1)},
            directions_2d{vector(-1, 0), vector(1, 0),
                          vector(0, -1), vector(0, 1)};
        int ice_block_cnt = 0;
        bool can_put_here(vector t) {
            if (!t.z) return 1;
            for (auto i : directions_3d)
                if (gr[i + t] == 5) return 1;
            return 0;
        }
        class door final {
        public:
            std::pair<int, int> pos{0, 0};
            int pf{}, cs{}, sz{};
            bool operator<(const door &t) const {
                if (cs != t.cs)
                    return cs < t.cs;
                else if (sz != t.sz)
                    return sz > t.sz;
                else if (pf != t.pf)
                    return pf < t.pf;
                else {
                    if (pos.fi == t.pos.fi)
                        return pos.se < t.pos.se;
                    else
                        return pos.fi < t.pos.fi;
                }
            }
        };
        class remove_utility final {
        private:
            std::vector<vector>
                directions_3d{vector(-1, 0), vector(1, 0),
                              vector(0, -1), vector(0, 1),
                              vector(0, 0, 1), vector(0, 0, -1)};
            int sz;
            bool ***vis, tmp;
            std::vector<vector> path;

            void remove_dfs(vector t) {
                vis[t.x][t.y][t.z] = 1;
                path.pb(t);
                if (!t.z) tmp = 0;
                for (auto i : directions_3d) {
                    auto nxt = t + i;
                    if (gr[nxt] == 5)
                        if (!vis[nxt.x][nxt.y][nxt.z]) {
                            remove_dfs(nxt);
                        }
                }
            }
            void clear_after_dfs() {
                for (auto i : path)
                    vis[i.x][i.y][i.z] = 0;
            }

        public:
            explicit remove_utility(int _sz = 50)
                : sz(_sz) {
                vis = new bool **[sz];
                rep(i, 0, sz) {
                    vis[i] = new bool *[sz];
                    rep(j, 0, sz)
                        vis[i][j] = new bool[sz];
                }
                rep(i, 0, sz)
                    rep(j, 0, sz)
                        rep(k, 0, sz)
                            vis[i][j][k] = 0;
            }
            ~remove_utility() {
                rep(i, 0, sz) {
                    rep(j, 0, sz) delete[] vis[i][j];
                    delete[] vis[i];
                }
                delete[] vis;
            }
            bool is_floating(vector t) {
                if (gr[t] != 5) return 0;
                tmp = 1;
                remove_dfs(t);
                clear_after_dfs();
                path.clear();
                return tmp;
            }
            int remove_floating(vector t) {
                if (gr[t] != 5) return 0;
                tmp = 1;
                remove_dfs(t);
                clear_after_dfs();
                if (tmp) {
                    for (auto i : path)
                        gr[i] = 0;
                    int res = path.size();
                    path.clear();
                    return res;
                }
                path.clear();
                return 0;
            }
        } rm_util;
        int hei;
        std::pair<int, int> pr1, pr2;

    public:
        explicit internal_emulator(int _cnt = 0)
            : ice_block_cnt(_cnt) {}
        const char *get_last_msg() {
            return msg;
        }
        const char *put_ice_barrage(int r, int c, int d, int s) {
            auto dir = directions[d];
            auto now = vector(r, c, 0);
            int ok = 0;
            do {
                if (now.is_valid() && gr[now] != 5) {
                    if (gr[now] != 4) ++ok;
                    ++gr[now];
                    if (gr[now] > 4) gr[now] = 4;
                    now = now + dir;
                } else
                    break;
            } while (s--);
            sprintf(msg, msg_dict[0], ok);
            return msg;
        }
        const char *make_ice_block() {
            int ok = 0;
            rep(i, 0, n - 1)
                rep(j, 0, n - 1) {
                if (gr[vector(i, j, 0)] == 4) {
                    ++ok;
                    gr[vector(i, j, 0)] = 0;
                }
            }
            ice_block_cnt += ok;
            sprintf(msg, msg_dict[1], ok, ice_block_cnt);
            return msg;
        }
        const char *put_ice_block(int r, int c, int h) {
            if (!ice_block_cnt) {
                sprintf(msg, "%s", msg_dict[2]);
                return msg;
            }
            auto now = vector(r, c, h);
            if (gr[now] == 5 || !can_put_here(now)) {
                sprintf(msg, "%s", msg_dict[3]);
                return msg;
            }
            --ice_block_cnt;
            gr[now] = 5;
            if (now.is_inside_the_house()) {
                sprintf(msg, "%s", msg_dict[5]);
            } else if (now.is_outside_the_house()) {
                sprintf(msg, "%s", msg_dict[4]);
            } else {
                sprintf(msg, msg_dict[6], ice_block_cnt);
            }
            return msg;
        }
        const char *remove_ice_block(int r, int c, int h) {
            auto now = vector(r, c, h);
            if (gr[now] != 5) {
                sprintf(msg, "%s", msg_dict[7]);
                return msg;
            }
            gr[now] = 0;
            int res = 0;
            for (auto i : directions_3d) {
                res += rm_util.remove_floating(now + i);
            }
            if (res)
                sprintf(msg, msg_dict[8], res);
            else
                sprintf(msg, "%s", msg_dict[9]);
            ++ice_block_cnt;
            return msg;
        }
        const char *make_roof() {
            pr1 = {hp.fi + hc.fi / 2, hp.se + hc.se / 2};
            pr2 = {hp.fi + (hc.fi - 1) / 2, hp.se + (hc.se - 1) / 2};
            std::vector<vector> od{}, rf{}, odn{};
            char buf[500];
            int inul = 0, ouul = 0;
            bool rm = 0, wall = 0;
            auto is_wall = [&](vector t) {
                return t.x == hp.fi || t.y == hp.se || t.x == hp.fi + hc.fi - 1 || t.y == hp.se + hc.se - 1;
            };
            auto is_corner = [&](vector t) {
                return (t.x == hp.fi || t.x == hp.fi + hc.fi - 1) && (t.y == hp.se || t.y == hp.se + hc.se - 1);
            };
            auto is_ins_block = [&](vector t) {
                return check_pos(hp.fi + 1, hp.fi + hc.fi - 2, t.x) && check_pos(hp.se + 1, hp.se + hc.se - 2, t.y) && check_pos(0, hei - 1, t.z);
            };
            auto is_ous_block = [&](vector t) {
                return !(check_pos(hp.fi, hp.fi + hc.fi - 1, t.x) && check_pos(hp.se, hp.se + hc.se - 1, t.y) && check_pos(0, hei, t.z));
            };
            auto is_perfect_pos = [&](vector t) {
                return t.x == pr1.fi || t.y == pr1.se || t.x == pr2.fi || t.y == pr2.se;
            };
            auto is_od = [&](vector t) {
                return check_pos(hp.fi, hp.fi + hc.fi - 1, t.x) && check_pos(hp.se, hp.se + hc.se - 1, t.y) && (!check_pos(hp.fi + 1, hp.fi + hc.fi - 2, t.x) || !check_pos(hp.se + 1, hp.se + hc.se - 2, t.y));
            };
            auto is_rf = [&](vector t) {
                return t.x >= hp.fi && t.x <= hp.fi + hc.fi - 1 && t.y >= hp.se && t.y <= hp.se + hc.se - 1;
            };
            sprintf(msg, "");
            rep(i, 0, n - 1) {
                rep(j, 0, n - 1) {
                    if (is_od(vector(i, j))) {
                        od.pb(i, j);
                    }
                    if (is_rf(vector(i, j))) {
                        rf.pb(i, j);
                    }
                }
            }
            for (auto i : od)
                rep(j, 0, m) if (gr[i + vector(0, 0, j)] == 5)
                    hei = std::max(hei, j + 1);
            int res = 0;
            for (auto i : rf) {
                // std::cerr << "Roof: " << i.x << ' ' << i.y << ' ' << i.z << '\n';
                if (gr[i + vector(0, 0, hei)] != 5)
                    ++res;
            }
            if (res > ice_block_cnt) {
                sprintf(msg, "%s", msg_dict[10]);
                return msg;
            }
            ice_block_cnt -= res;
            if ((hei == 1 && hc.fi <= 3 && hc.se <= 3) || hei < 1 || hc.fi == 2 || hc.se == 2) {
                sprintf(msg, "%s", msg_dict[11]);
                return msg;
            }
            for (auto i : rf)
                gr[i + vector(0, 0, hei)] = 5;
            rep(i, 0, n - 1) {
                rep(j, 0, n - 1) {
                    rep(k, 0, m) {
                        auto now = vector(i, j, k);
                        if (gr[now] == 5) {
                            if (is_ins_block(now))
                                ++inul;
                            else if (is_ous_block(now))
                                ++ouul;
                            else
                                continue;
                            gr[now] = 0;
                            rm = 1;
                            ++ice_block_cnt;
                            for (auto l : directions_3d) {
                                auto nxt = now + l;
                                if (is_wall(nxt) && rm_util.is_floating(nxt)) {
                                    gr[nxt] = 0;
                                    ++ice_block_cnt;
                                    // ++br;
                                }
                            }
                        }
                    }
                }
            }
            sprintf(buf, msg_dict[12], inul);
            strcat(msg, buf);
            sprintf(buf, msg_dict[13], ouul);
            strcat(msg, buf);
            if (rm_util.is_floating(vector(hp.fi + 1, hp.se + 1, hei))) {
                sprintf(buf, "%s", msg_dict[14]);
                strcat(msg, buf);
                return msg;
            }
            for (auto i : od)
                if (!is_corner(i)) odn.pb(i);
            for (auto i : odn) {
                rep(j, 2, hei - 1) {
                    if (gr[i + vector(0, 0, j)] != 5) {
                        if (!ice_block_cnt) {
                            sprintf(buf, "%s", msg_dict[15]);
                            strcat(msg, buf);
                            return msg;
                        }
                        --ice_block_cnt;
                        gr[i + vector(0, 0, j)] = 5;
                        wall = 1;
                    }
                }
            }
            res = 0;
            for (auto i : odn) {
                rep(j, 0, 1)
                    res += gr[i + vector(0, 0, j)] != 5;
            }
            std::vector<door> dr{};
            for (auto i : odn) {
                int hs = gr[i] != 5;
                hs += gr[i + vector(0, 0, 1)] != 5;
                if (hs) {
                    auto now = door{{i.x, i.y}, is_perfect_pos(i), res - hs, hs};
                    for (auto j : directions_2d) {
                        auto nxt = i + j;
                        if (is_corner(nxt)) {
                            rep(k, 0, 1) {
                                if (gr[i + vector(0, 0, k)] != 5) {
                                    now.cs += gr[nxt + vector(0, 0, k)] != 5;
                                }
                            }
                        }
                    }
                    dr.pb(now);
                }
            }
            std::sort(dr.begin(), dr.end());
            door rdr;
            if (dr.empty() || (rdr = *dr.begin()).cs > ice_block_cnt) {
                sprintf(buf, "%s", msg_dict[15]);
                strcat(msg, buf);
                return msg;
            }

            if (ice_block_cnt > rdr.cs && rdr.sz == 1) {
                for (auto i : dr)
                    if (i.sz == 2) {
                        rdr = i;
                        break;
                    }
            }

            vector drpos(rdr.pos.fi, rdr.pos.se);
            for (auto i : directions_2d) {
                if (is_corner(drpos + i))
                    rep(k, 0, hei - 1) {
                        if (gr[drpos + i + vector(0, 0, k)] != 5) {
                            if (gr[drpos + vector(0, 0, k)] != 5) {
                                wall = 1;
                                --ice_block_cnt;
                                gr[drpos + i + vector(0, 0, k)] = 5;
                            }
                        }
                    }
            }
            for (auto i : odn) {
                if (i == drpos) continue;
                rep(k, 0, 1) {
                    if (gr[i + vector(0, 0, k)] != 5) {
                        gr[i + vector(0, 0, k)] = 5;
                        --ice_block_cnt;
                        wall = 1;
                    }
                }
            }
            sprintf(buf, "%s", msg_dict[16]);
            strcat(msg, buf);
            bool perf = 1;
            if (rdr.sz != 2) {
                perf = 0;
                sprintf(buf, "%s", msg_dict[17]);
            } else {
                sprintf(buf, "%s", msg_dict[18]);
            }
            strcat(msg, buf);
            if (gr[drpos] == 5) {
                gr[drpos] = 0;
                ++ice_block_cnt;
            }
            if (gr[drpos + vector(0, 0, 1)] == 5) {
                gr[drpos + vector(0, 0, 1)] = 0;
                ++ice_block_cnt;
            }
            if (wall) {
                perf = 0;
                sprintf(buf, "%s", msg_dict[19]);
            } else {
                sprintf(buf, "%s", msg_dict[20]);
            }
            strcat(msg, buf);
            res = 0;
            for (auto i : od) {
                if (!is_corner(i)) continue;
                rep(j, 0, hei - 1) {
                    if (gr[i + vector(0, 0, j)] != 5) {
                        ++res;
                        gr[i + vector(0, 0, j)] = 5;
                    }
                }
            }
            ice_block_cnt -= res;
            ice_block_cnt = std::max(ice_block_cnt, 0);
            if (res) {
                perf = 0;
                sprintf(buf, "%s", msg_dict[21]);
            } else {
                sprintf(buf, "%s", msg_dict[22]);
            }
            strcat(msg, buf);
            sprintf(buf, msg_dict[23], ice_block_cnt);
            strcat(msg, buf);
            if (rm) perf = 0;
            if (!rdr.pf) perf = 0;
            if (perf) {
                sprintf(buf, "%s", msg_dict[24]);
                strcat(msg, buf);
            }
            return msg;
        }
    };
    static constexpr char *cmd_dict[] = {
        (char *) "ICE_BARRAGE",
        (char *) "MAKE_ICE_BLOCK",
        (char *) "PUT_ICE_BLOCK",
        (char *) "REMOVE_ICE_BLOCK",
        (char *) "MAKE_ROOF"};
    static constexpr char *emu_info[] = {
        (char *) "Hellolin's \"Cirno's Ice House\" solution emulator\n",
        (char *) "Version 0.0.1\n"};
    static constexpr char *log_info[] = {
        (char *) "[WARN] Starting...\n",
        (char *) "[WARN] Enter the initialization parameters:",
        (char *) "[INFO] Ready. You can type commands now.\n",
        (char *) "EM> ",
        (char *) "[ERR]  Unknown error, ending now.\n",
        (char *) "[WARN] Success, ending now.\n"};

public:
    internal_emulator *ie;
    void start_emulator(FILE *inf, FILE *ouf, FILE *erf) {
        fprintf(erf, "%s", log_info[0]);
        if (ie != nullptr) delete ie;
        ie = new internal_emulator;
        rep(i, 0, 1)
            fprintf(erf, "%s", emu_info[i]);
        fprintf(erf, "%s", log_info[1]);
        if (fscanf(inf, "%d %d %d %d %d %d %d", &n, &m, &hp.fi, &hp.se, &hc.fi, &hc.se, &q) == EOF) {
            fprintf(erf, "%s", log_info[4]);
            return;
        }
        fprintf(erf, "%s", log_info[2]);
        char tmp[500];
        int a, b, c, d;
        while (q--) {
            fprintf(erf, "%s", log_info[3]);
            if (fscanf(inf, "%s", tmp) == EOF) {
                fprintf(erf, "%s", log_info[4]);
                return;
            }
            if (strcmp(tmp, cmd_dict[0]) == 0) {
                if (fscanf(inf, "%d %d %d %d", &a, &b, &c, &d) == EOF) {
                    fprintf(erf, "%s", log_info[4]);
                    return;
                }
                ie->put_ice_barrage(a, b, c, d);
            } else if (strcmp(tmp, cmd_dict[1]) == 0) {
                ie->make_ice_block();
            } else if (strcmp(tmp, cmd_dict[2]) == 0) {
                if (fscanf(inf, "%d %d %d", &a, &b, &c) == EOF) {
                    fprintf(erf, "%s", log_info[4]);
                    return;
                }
                ie->put_ice_block(a, b, c);
            } else if (strcmp(tmp, cmd_dict[3]) == 0) {
                if (fscanf(inf, "%d %d %d", &a, &b, &c) == EOF) {
                    fprintf(erf, "%s", log_info[4]);
                    return;
                }
                ie->remove_ice_block(a, b, c);
            } else if (strcmp(tmp, cmd_dict[4]) == 0) {
                ie->make_roof();
            } else {
                fprintf(erf, "%s", log_info[4]);
                return;
            }
            fprintf(ouf, "%s", ie->get_last_msg());
        }
        fprintf(erf, "%s", log_info[5]);
    }
};
#undef check_pos
} // namespace hellolin
hellolin::cirnos_ice_house_emulator emu;
int main() {
    emu.start_emulator(stdin, stdout, stderr);
    return 0;
}