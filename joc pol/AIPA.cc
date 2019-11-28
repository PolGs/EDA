#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME PA


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

/* -----PATHFINDING ALGOS-------*/





const double infinit     = numeric_limits<double>::infinity();

typedef pair<double, int> WArc;
typedef vector<vector<WArc>> WGraph;
// weighted arc
// weighted digraf
void dijkstra(const WGraph& G, int s, vector<double>& d, vector<int>& p) {
    int n = G.size();
    d = vector<double>(n, infinit); d[s] = 0;
    p = vector<int>(n, -1);
    vector<bool> S(n, false);
    priority_queue<WArc, vector<WArc>, greater<WArc> > Q;
    Q.push(WArc(0, s));

    while (not Q.empty()) {
        int u = Q.top().second; Q.pop();
        if (not S[u]) {
            S[u] = true;
            for (WArc a : G[u]) {
            int v = a.second;
            double c = a.first;
                if (d[v] > d[u] + c) {
                    d[v] = d[u] + c;
                    p[v] = u;
                    Q.push(WArc(d[v], v));
                }  
            } 
        }
    }
 }


/* ----- AUX ALGOS ---- */


    int postover(Pos p){
        return p.i*60 + p.j;
    }


/* ------CELL INFO------*/

//Cell to Graph








  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
      vector<int> aux =  dwarves(me());
      int n = aux.size();
      for(int i = 0; i<n;++i){
        command(aux[i],Right);
      }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
