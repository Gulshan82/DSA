class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int n = classroom.size();
        int m = classroom[0].size();

        int sr = 0, sc = 0;
        int litterCount = 0;

        vector<vector<int>> id(n, vector<int>(m, -1));

        // Find S and assign bit to every L
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if (classroom[i][j] == 'L') {
                    id[i][j] = litterCount++;
                }
            }
        }

        int fullMask = (1 << litterCount) - 1;

        if (fullMask == 0)
            return 0;

        // state = {row, col, remainingEnergy, collectedMask}
        queue<array<int, 5>> q;

        // visited[r][c][energy][mask]
        vector<vector<vector<vector<bool>>>> visited(
            n,
            vector<vector<vector<bool>>>(
                m,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << litterCount, false)
                )
            )
        );

        q.push({sr, sc, energy, 0, 0});
        visited[sr][sc][energy][0] = true;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            auto cur = q.front();
            q.pop();

            int r = cur[0];
            int c = cur[1];
            int e = cur[2];
            int mask = cur[3];
            int moves = cur[4];

            if (mask == fullMask)
                return moves;

            // Can't move if no energy remains
            if (e == 0)
                continue;

            for (int d = 0; d < 4; d++) {

                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= n ||
                    nc < 0 || nc >= m)
                    continue;

                if (classroom[nr][nc] == 'X')
                    continue;

                int ne = e - 1;
                int newMask = mask;

                // Collect litter
                if (classroom[nr][nc] == 'L') {
                    newMask |= (1 << id[nr][nc]);
                }

                // Reset energy
                if (classroom[nr][nc] == 'R') {
                    ne = energy;
                }

                if (!visited[nr][nc][ne][newMask]) {

                    visited[nr][nc][ne][newMask] = true;

                    q.push({
                        nr,
                        nc,
                        ne,
                        newMask,
                        moves + 1
                    });
                }
            }
        }

        return -1;
    }
};