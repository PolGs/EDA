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

/* ---------------------------------------PATHFINDING ALGOS-----------------------------------------*/

//---------DIJKSTRA-----------------------//

const double infinit     = numeric_limits<double>::infinity();

typedef pair<double, int> WArc;
typedef vector<vector<WArc>> WGraph;

void dijkstra_eda(const WGraph& G, int s, vector<double>& d, vector<int>& p) {
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
 
 dijkstra_aux
 
 //----VERSIO GITHUB ---- 
 
 
 
 
 
 
 
 
 //-----------END --- DIJKSTRA--------------//
















/* ---------------------------------------AUX ALGOS-----------------------------------------*/

//---Position to Graph vertice--
    int postover(Pos p){
        return p.i*60 + p.j;
    }
    
    Pos vertopos(int ver){
		Pos p;
		p.i = ver/60;
		p.j= ver - i*60;
	}
   

//----Weight of cell p----
    double weight(Pos p){
			CellType t = cell(p).type;
			if(t == Rock){
				if(cell(p).treasure == 1) return -10;
				else return cell(p).turns;
			else if(t == Granite) return infinit;
			else if(t == Outside) return 0;
			else if(t == Cave){
				if(owner != me()) return -1;
				else return 0;
			}
			else if(t == Abyss) return infinit;
	}
}
//--Grid to Graph ----
    WGraph gridtograph(){
        WGraph G;//
        WArc arc;//weight, vertex
        for(int i= 0; i<60; ++i){
            for(int j=0; j<60; ++j){
				Pos p(i,j);
				arc.first()=weight(p);
				arc.second()=postover(p);
				G[i*60 + j][j] = arc;
            }
    }

//-----Move Dwarve towards d-------

void move_dwarve(int id, int s, int d, vector<int>& p){
	int i = 0;
	
	while(p[i] != s){
		i= p[i];
	}
	Pos p = vertopos(i);
	deltax =  p.j - unit(id).pos.j;
	deltay = p.i - unit(id).pos.i;
	
	Dir d;
	if(deltax < 0 and deltay < 0) d = LB;
	else if(deltax < 0 and deltay > 0) d = TL;
	else if(deltax > 0 and deltay < 0) d = BR;
	else if(deltax > 0 and deltay > 0) d = RT;
	
	else if(deltax = 0 and deltay < 0) d = Bottom;
	else if(deltax = 0 and deltay > 0) d = Top;
	else if(deltax > 0 and deltay = 0) d = Right;
	else if(deltax < 0 and deltay = 0) d = Left;
		
	command (id, d);
	
}


//-----Clost tresure----

int cls_treasure(vector<double>& d, int x){
	int min =0;
	for(int i=0; i<d.size();++i){
		if(d[min]>d[i]) min = i;
	}
	return i;
}

/* ---------------------------------------CELL INFO-----------------------------------------*/









  /**
   * Play method, invoked once per each round.
   */
	virtual void play () {
		WGraph G = gridtograph();
		vector<int> d;
		vector<int> p;
		int x, y;
		int x = postover(unit(i).pos);
		vector<int> aux =  dwarves(me());
		int n = aux.size();
		for(int i = 0; i<n;++i){
			dijkstra(G, x, d, p);
			y = cls_tresure(d, x);
			move_dwarve(aux[i],x, y, p);
		}
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
